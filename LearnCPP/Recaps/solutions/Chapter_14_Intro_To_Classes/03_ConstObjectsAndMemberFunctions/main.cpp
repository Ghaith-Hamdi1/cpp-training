// Chapter 14 - Project 03: Const Objects and Const Member Functions
// ===================================================================
// Key concepts:
//   - A const object cannot have its members modified.
//   - Non-const member functions CANNOT be called on const objects.
//   - Appending 'const' after the parameter list makes a member function
//     promise not to modify the object.
//   - Best practice: make every member function that doesn't modify
//     state 'const'. This lets it work with both const and non-const objects.
//
// Common pitfall:
//   Forgetting to make a member function 'const' - then it can't be
//   called on a const object, causing a compilation error.

#include <iostream>
#include <string>

class Temperature
{
    double m_celsius{};

public:
    Temperature(double celsius)
        : m_celsius{celsius}
    {
    }

    // ----- CONST member functions - safe to call on const objects -----

    double getCelsius() const // <-- 'const' after parameter list
    {
        return m_celsius;
    }

    double getFahrenheit() const // <-- also const
    {
        return m_celsius * 9.0 / 5.0 + 32.0;
    }

    void print() const // <-- also const
    {
        std::cout << m_celsius << " C  /  " << getFahrenheit() << " F\n";
    }

    // ----- NON-CONST member function - modifies the object -----

    void setCelsius(double celsius) // NOT const - it modifies m_celsius
    {
        m_celsius = celsius;
    }
};

// A function that takes a const reference - can only call const member functions
void displayTemperature(const Temperature &temp)
{
    std::cout << "Display: ";
    temp.print(); // OK - print() is const

    // temp.setCelsius(0);  // ERROR - setCelsius() is NOT const,
    //         and 'temp' is a const reference.
}

int main()
{
    // Non-const object - all member functions are callable
    Temperature today{22.5};
    today.print();
    today.setCelsius(25.0); // OK - non-const object
    today.print();

    // Const object - only const member functions are callable
    const Temperature boilingPoint{100.0};
    boilingPoint.print();                                                // OK - print() is const
    std::cout << "Fahrenheit: " << boilingPoint.getFahrenheit() << '\n'; // OK

    // boilingPoint.setCelsius(0);  // ERROR - would not compile!
    //   ^^^^^^^^^^^^^^^^^^^^^^
    //   Non-const member function cannot be called on a const object.

    // Passing to a function that takes a const reference
    displayTemperature(today);

    std::cout << "\n-- Takeaway --\n"
              << "Always mark member functions 'const' if they don't modify the object.\n"
              << "This is the #1 most-forgotten best practice in this chapter.\n";

    return 0;
}
