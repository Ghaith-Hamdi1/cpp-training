// Chapter 12 - Project 05: Pass by Const Lvalue Reference
// =========================================================
// Pass by const& avoids copies AND accepts:
//   • modifiable lvalues
//   • const lvalues
//   • rvalues (temporaries)
//
// Rules of thumb:
//   • Pass fundamental types (int, double, etc.) by value - they're cheap to copy
//   • Pass class/struct types (std::string, etc.) by const& - avoids expensive copies
//   • Prefer std::string_view over const std::string& for read-only string parameters

#include <iostream>
#include <string>
#include <string_view>

// Pass by const reference - cannot modify the original, but avoids copying
void printValue(const int &value)
{
    std::cout << "Value: " << value << '\n';
    // value = 99;  // ERROR: can't modify through const reference
}

// For class types, const& avoids expensive copies
void printString(const std::string &str)
{
    std::cout << "String: " << str << '\n';
}

// Even better for strings: use std::string_view (cheap to copy, works with literals)
void printStringView(std::string_view sv)
{
    std::cout << "StringView: " << sv << '\n';
}

// const& lets us accept rvalues too
void printSum(const int &result)
{
    std::cout << "Sum: " << result << '\n';
}

int main()
{
    // ----- const& accepts modifiable lvalues -----
    int x{42};
    printValue(x); // OK

    // ----- const& accepts const lvalues -----
    const int y{100};
    printValue(y); // OK (non-const ref would fail here)

    // ----- const& accepts rvalues -----
    printValue(5);   // OK - temporary created and bound
    printSum(x + y); // OK - x + y is an rvalue

    // ----- Class types: prefer const& to avoid copies -----
    std::string greeting{"Hello, World!"};
    printString(greeting);     // no copy - passed by reference
    printString("Temporary!"); // rvalue accepted via const&

    // ----- std::string_view is often even better -----
    printStringView(greeting);
    printStringView("Literal");
    printStringView(std::string_view{greeting}.substr(0, 5));

    return 0;
}
