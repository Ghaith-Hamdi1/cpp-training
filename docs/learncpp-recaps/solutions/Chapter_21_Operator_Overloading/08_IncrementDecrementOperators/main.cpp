// Project 08: Overloading Increment and Decrement Operators
// ===========================================================
// Prefix (++x) and postfix (x++) are distinguished by a dummy int parameter
// on the postfix version. Prefix modifies and returns *this by reference.
// Postfix saves a copy, increments via prefix, returns the saved copy by value.
// Prefix is more efficient than postfix (no copy needed).

#include <iostream>

class Counter
{
private:
    int m_value{};

public:
    Counter(int value = 0) : m_value{value} {}

    int getValue() const { return m_value; }

    // --- Prefix increment (++counter) ---
    // Modifies *this and returns it by reference.
    // This is the more efficient version - no copy is made.
    Counter &operator++()
    {
        ++m_value;
        return *this; // Return modified object by reference
    }

    // --- Postfix increment (counter++) ---
    // The dummy 'int' parameter distinguishes this from prefix.
    // Must save a copy BEFORE incrementing, then return the copy by VALUE.
    Counter operator++(int) // 'int' is the dummy parameter
    {
        Counter old{*this}; // Save current state
        ++(*this);          // Use prefix increment (avoid code duplication!)
        return old;         // Return the saved (pre-increment) copy by value
    }

    // --- Prefix decrement (--counter) ---
    Counter &operator--()
    {
        --m_value;
        return *this;
    }

    // --- Postfix decrement (counter--) ---
    Counter operator--(int)
    {
        Counter old{*this};
        --(*this);
        return old;
    }

    friend std::ostream &operator<<(std::ostream &out, const Counter &c);
};

std::ostream &operator<<(std::ostream &out, const Counter &c)
{
    out << c.m_value;
    return out;
}

int main()
{
    Counter c{5};
    std::cout << "Initial value: " << c << '\n';

    // --- Prefix increment: increments THEN returns the new value ---
    std::cout << "\n--- Prefix ++ ---\n";
    std::cout << "++c = " << ++c << '\n'; // c becomes 6, returns 6
    std::cout << "c   = " << c << '\n';   // c is 6

    // --- Postfix increment: returns old value THEN increments ---
    std::cout << "\n--- Postfix ++ ---\n";
    std::cout << "c++ = " << c++ << '\n'; // Returns 6 (old value), c becomes 7
    std::cout << "c   = " << c << '\n';   // c is 7

    // --- Prefix decrement ---
    std::cout << "\n--- Prefix -- ---\n";
    std::cout << "--c = " << --c << '\n'; // c becomes 6, returns 6
    std::cout << "c   = " << c << '\n';   // c is 6

    // --- Postfix decrement ---
    std::cout << "\n--- Postfix -- ---\n";
    std::cout << "c-- = " << c-- << '\n'; // Returns 6 (old value), c becomes 5
    std::cout << "c   = " << c << '\n';   // c is 5

    // Key takeaways:
    // 1. Prefix: modify *this, return *this by reference - efficient, no copy
    // 2. Postfix: save copy, use prefix to increment, return copy by value - extra copy!
    // 3. Distinguish them: prefix has no parameter, postfix has dummy 'int'
    // 4. Implement postfix in terms of prefix to avoid code duplication
    // 5. Prefer prefix when you don't need the old value (it's faster)

    return 0;
}
