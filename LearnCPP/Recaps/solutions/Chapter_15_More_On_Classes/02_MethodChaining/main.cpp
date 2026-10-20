// Chapter 15 - Project 02: Method Chaining
// ==========================================
//
// By returning `*this` BY REFERENCE from a member function, we allow
// multiple calls to be chained in a single expression:
//
//     calc.add(5).sub(3).mult(2);
//
// PITFALL: Returning `*this` BY VALUE creates a COPY - all subsequent
// calls in the chain operate on the copy, not on the original object.
// Always return by reference for chaining!

#include <iostream>

class Calculator
{
private:
    double m_value{0.0};

public:
    // Reset to a starting value (also chainable).
    Calculator &setValue(double v)
    {
        m_value = v;
        return *this; // Return current object by reference
    }

    Calculator &add(double x)
    {
        m_value += x;
        return *this; // Enables chaining
    }

    Calculator &sub(double x)
    {
        m_value -= x;
        return *this;
    }

    Calculator &mult(double x)
    {
        m_value *= x;
        return *this;
    }

    Calculator &div(double x)
    {
        if (x != 0.0)
            m_value /= x;
        else
            std::cout << "[Error: division by zero ignored]\n";
        return *this;
    }

    // Const - doesn't modify state, no need to chain.
    double getValue() const { return m_value; }

    void print() const
    {
        std::cout << "Calculator value = " << m_value << '\n';
    }
};

int main()
{
    Calculator calc{};

    // --- Method chaining in action ---
    // Compute: ((0 + 10) - 3) * 2 / 7
    calc.setValue(0)
        .add(10)
        .sub(3)
        .mult(2)
        .div(7);

    calc.print(); // Expected: 2

    // --- Another chain ---
    calc.setValue(100).sub(50).div(5);
    std::cout << "Result: " << calc.getValue() << '\n'; // Expected: 10

    // --- Why returning by value would break things ---
    // If add() returned Calculator (by value), calc.add(5).sub(3) would
    // subtract from the COPY, not from `calc`. The original `calc` would
    // only see the +5, not the -3.  Always return *this by reference!

    return 0;
}
