# Files Management

(Slide 82)

- In the standard library, files are considered as input, output or io streams:
  - `std::ifstream` (input file stream) derived from `std::istream`
  - `std::ofstream` (output file stream) derived from `std::ostream`
  - `std::fstream` (file stream) derived from `std::iostream`
- This means that files in this case are to be managed with stream operators `<<` and `>>`
- Defined in file `<fstream>`
- See examples provided for more details

```cpp
// Trimmed excerpt — full runnable example: examples/course/03-cpp-standard-library/13-files-management/58_file_management.cpp
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ofstream ofile("test.txt", std::ios_base::out);
    ofile << "Hello from main" << std::endl;
    ofile.close(); // close can be called explicitly or automatically in ofile destructor

    std::ifstream ifile("test.txt", std::ios_base::in);
    std::string str;

    ifile >> str;
    std::cout << "String read from file: " << str << std::endl;

    ifile.seekg(0, std::ios_base::beg); // back to start of file
    std::getline(ifile, str);
    std::cout << "Line read from file: " << str << std::endl;
    ifile.seekg(0, std::ios_base::beg);

    std::vector<char> str2(10);
    ifile.read(str2.data(), 10);
    std::cout << "Read() called " << std::string(str2.begin(), str2.end()) << std::endl;
    return 0;
}
```

---

