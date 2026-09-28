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

    std::getline(ifile, str);
    std::cout << "Line read from file: " << str << std::endl;

    ifile.seekg(0, std::ios_base::beg);
    std::getline(ifile, str);
    std::cout << "Line read from file: " << str << std::endl;
    ifile.seekg(0, std::ios_base::beg); // back to starting of file

    std::vector<char> str2(10);
    ifile.read(str2.data(), 10);
    std::cout << "Read() called " << std::string(str2.begin(), str2.end()) << std::endl;
    return 0;
}