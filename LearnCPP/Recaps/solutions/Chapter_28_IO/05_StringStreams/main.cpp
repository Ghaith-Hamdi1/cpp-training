// Chapter 28 - Project 05: String Streams
// -------------------------------------------
// Key concepts:
//   - std::ostringstream - build strings using << (like cout but to a string)
//   - std::istringstream - parse strings using >> (like cin but from a string)
//   - std::stringstream  - both input and output on one string
//   - str()    - get the internal string
//   - str("")  - set/reset the internal string
//   - clear()  - reset error flags (needed when reusing a stringstream)
//
// Best practice: to reuse a stringstream, call BOTH str("") AND clear().

#include <iostream>
#include <sstream> // istringstream, ostringstream, stringstream
#include <string>

int main()
{
    // ========================================================
    // 1. ostringstream - building a formatted string
    // ========================================================
    std::cout << "=== 1. ostringstream ===\n";

    std::ostringstream oss{};
    oss << "There are " << 12 << " items, each costing $" << 4.99;
    // Retrieve the built string with str()
    std::string result{oss.str()};
    std::cout << result << '\n';

    // ========================================================
    // 2. istringstream - parsing data from a string
    // ========================================================
    std::cout << "\n=== 2. istringstream ===\n";

    std::string data{"Alice 95 Bob 87 Carol 91"};
    std::istringstream iss{data};

    std::string name{};
    int score{};
    while (iss >> name >> score) // extracts pairs until stream exhausted
    {
        std::cout << name << " scored " << score << '\n';
    }

    // ========================================================
    // 3. stringstream - bidirectional use
    // ========================================================
    std::cout << "\n=== 3. stringstream (bidirectional) ===\n";

    std::stringstream ss{};

    // Insert data
    ss << "100 200 300";

    // Extract data
    int a{};
    int b{};
    int c{};
    ss >> a >> b >> c;
    std::cout << "Sum = " << (a + b + c) << '\n';

    // ========================================================
    // 4. Converting between strings and numbers
    // ========================================================
    std::cout << "\n=== 4. String ↔ Number conversion ===\n";

    // Number → String
    std::ostringstream numToStr{};
    numToStr << 3.14159;
    std::string piStr{numToStr.str()};
    std::cout << "Number as string: \"" << piStr << "\"\n";

    // String → Number
    std::istringstream strToNum{"42"};
    int num{};
    strToNum >> num;
    std::cout << "String as number: " << num << '\n';

    // ========================================================
    // 5. Reusing a stringstream - must call str("") AND clear()
    // ========================================================
    std::cout << "\n=== 5. Reusing a stringstream ===\n";

    std::stringstream reuse{};

    // First use
    reuse << "first";
    std::cout << "First:  " << reuse.str() << '\n';

    // WRONG way to reuse - forgetting clear() or str("")
    // reuse.str("");  // clears buffer but NOT error flags
    // reuse.clear();  // clears flags but NOT the buffer

    // CORRECT way: do both
    reuse.str(""); // clear the string buffer
    reuse.clear(); // clear any error flags (eofbit, failbit, etc.)

    // Second use
    reuse << "second";
    std::cout << "Second: " << reuse.str() << '\n';

    // ========================================================
    // 6. Practical example - CSV line parser
    // ========================================================
    std::cout << "\n=== 6. CSV line parser ===\n";

    std::string csvLine{"John,25,New York"};
    std::istringstream csvStream{csvLine};
    std::string field{};

    while (std::getline(csvStream, field, ',')) // ',' as delimiter
    {
        std::cout << "  Field: \"" << field << "\"\n";
    }

    std::cout << "\nDone!\n";
    return 0;
}
