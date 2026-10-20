// Chapter 12 - Project 04: Pass by Lvalue Reference
// ====================================================
// Passing by reference avoids copying the argument.
// A non-const reference parameter lets the function modify the caller's object.
// Non-const reference parameters only accept modifiable lvalues.

#include <iostream>
#include <string>

// Pass by non-const reference - can modify the original
void doubleValue(int &value)
{
    value *= 2; // modifies the caller's variable directly
}

// Swap two integers using references - classic example
void swapInts(int &a, int &b)
{
    int temp{a};
    a = b;
    b = temp;
}

// Pass a string by reference to modify it
void toUpper(std::string &str)
{
    for (char &ch : str)
    {
        if (ch >= 'a' && ch <= 'z')
            ch -= 32; // convert to uppercase (ASCII)
    }
}

int main()
{
    // ----- doubleValue -----
    int x{7};
    std::cout << "Before doubleValue: x = " << x << '\n'; // 7
    doubleValue(x);
    std::cout << "After  doubleValue: x = " << x << '\n'; // 14

    // ----- swapInts -----
    int a{10}, b{20};
    std::cout << "\nBefore swap: a = " << a << ", b = " << b << '\n';
    swapInts(a, b);
    std::cout << "After  swap: a = " << a << ", b = " << b << '\n';

    // ----- toUpper -----
    std::string name{"copilot"};
    std::cout << "\nBefore toUpper: " << name << '\n';
    toUpper(name);
    std::cout << "After  toUpper: " << name << '\n';

    // ----- Cannot pass rvalues or const to non-const reference -----
    // doubleValue(5);           // ERROR: 5 is an rvalue
    // const int c{ 3 };
    // doubleValue(c);           // ERROR: c is non-modifiable

    return 0;
}
