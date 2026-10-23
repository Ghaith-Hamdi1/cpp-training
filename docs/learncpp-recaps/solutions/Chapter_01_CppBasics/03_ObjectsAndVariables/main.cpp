// Chapter 1 - Project 03: Objects and Variables
// ================================================
//
// KEY CONCEPTS:
//   - **Data** is any information a computer can process (numbers, text, etc.).
//   - An **object** is a region of storage (in RAM or a register) that holds a value.
//   - A **variable** is a named object - you access the storage via the name.
//   - A **definition statement** creates a variable:  type name;
//   - The **data type** (e.g., int, double, char) tells the compiler:
//       * How much memory to allocate
//       * How to interpret the bits stored there
//   - The type must be known at compile time.

#include <iostream>

int main()
{
    // --- Defining variables ---
    // Syntax: type identifier;
    // This defines a variable named 'age' of type int.
    int age{30};
    std::cout << "age = " << age << '\n';

    // A double stores floating-point (decimal) numbers.
    double temperature{36.6};
    std::cout << "temperature = " << temperature << '\n';

    // A char stores a single character.
    char grade{'A'};
    std::cout << "grade = " << grade << '\n';

    // A bool stores true or false.
    bool isStudent{true};
    std::cout << "isStudent = " << isStudent << '\n'; // Prints 1 (true) or 0 (false)

    // --- Multiple variables of the same type ---
    // You CAN define multiple variables on one line (but it's not recommended):
    int a{1}, b{2}, c{3};
    std::cout << "a=" << a << " b=" << b << " c=" << c << '\n';

    // BEST PRACTICE: Define each variable on its own line for clarity:
    int width{10};
    int height{20};
    int area{width * height};
    std::cout << "Area = " << width << " x " << height << " = " << area << '\n';

    // --- Objects vs. Variables ---
    // Every variable is an object, but not every object is a variable.
    // Temporary objects (like the result of an expression) are objects without names.
    // Example: in the expression (width * height), the intermediate result is
    // an unnamed temporary object.

    // --- Data types determine interpretation ---
    // The same bits in memory can mean different things depending on the type.
    // int interprets bits as a whole number; double interprets bits as a decimal.
    int wholeNumber{7};
    double decimalNumber{7.0};
    std::cout << "int 7:    " << wholeNumber << '\n';
    std::cout << "double 7: " << decimalNumber << '\n';

    return 0;
}
