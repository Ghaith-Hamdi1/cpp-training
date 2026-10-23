// Project 11: Overloading Typecasts and the explicit Keyword
// ============================================================
// User-defined type conversions (e.g., operator int()) let you define how
// your class converts to another type. They have NO explicit parameters
// and NO declared return type. Mark them 'explicit' unless the conversion
// is to a closely synonymous type.
//
// PITFALL: Mixing an overloaded typecast with a converting constructor for
// the same conversion can cause ambiguous overload resolution.
//
// Best practice: Prefer converting constructors over overloaded typecasts.

#include <iostream>
#include <string>

// --- Converting Constructor ---
// A constructor that can be called with a single argument acts as an
// implicit conversion FROM that argument type TO the class type.

class Dollars
{
private:
    double m_amount{};

public:
    // Converting constructor: int -> Dollars (implicit conversion)
    Dollars(double amount) : m_amount{amount} {}

    double getAmount() const { return m_amount; }

    // --- Typecast operator: Dollars -> int ---
    // Allows: int x = static_cast<int>(myDollars);
    // No return type declared - it's implied by the operator name.
    // No parameters - the object itself is the input.
    // Marked 'explicit' to prevent accidental implicit conversions.
    explicit operator int() const
    {
        return static_cast<int>(m_amount);
    }

    // --- Typecast to bool ---
    // Allows: if (myDollars) { ... }
    // 'explicit' still allows contextual conversions (if, while, &&, ||, !)
    explicit operator bool() const
    {
        return m_amount != 0.0;
    }

    friend std::ostream &operator<<(std::ostream &out, const Dollars &d);
};

std::ostream &operator<<(std::ostream &out, const Dollars &d)
{
    out << '$' << d.m_amount;
    return out;
}

// --- Demonstrating explicit keyword on converting constructors ---

class Euros
{
private:
    double m_amount{};

public:
    // 'explicit' on the constructor prevents implicit conversion from double to Euros.
    // You must write Euros{50.0} explicitly - can't pass a bare 50.0 where Euros is expected.
    explicit Euros(double amount) : m_amount{amount} {}

    double getAmount() const { return m_amount; }
};

void acceptEuros(const Euros &e)
{
    std::cout << "Received " << e.getAmount() << " euros\n";
}

int main()
{
    // --- Converting constructor (implicit: double -> Dollars) ---
    std::cout << "=== Converting Constructor ===\n";
    Dollars d1 = 19.99; // Implicit conversion from double to Dollars (allowed, not explicit)
    std::cout << "d1 = " << d1 << '\n';

    // --- Typecast operator (explicit: Dollars -> int) ---
    std::cout << "\n=== Typecast Operator (explicit) ===\n";
    int cents = static_cast<int>(d1); // Must use static_cast because operator int() is explicit
    std::cout << "static_cast<int>(d1) = " << cents << '\n';
    // int bad = d1;  // ERROR: operator int() is explicit - no implicit conversion

    // --- Typecast to bool (explicit, but contextual conversions allowed) ---
    std::cout << "\n=== Typecast to bool ===\n";
    Dollars d2{0.0};
    Dollars d3{5.0};

    // 'explicit operator bool()' still works in boolean contexts:
    if (d3)
        std::cout << d3 << " is non-zero\n";
    if (!d2)
        std::cout << d2 << " is zero\n";

    // bool b = d3;  // ERROR: explicit - can't implicitly convert to bool

    // --- explicit converting constructor ---
    std::cout << "\n=== explicit Converting Constructor (Euros) ===\n";
    // acceptEuros(50.0);           // ERROR: constructor is explicit, no implicit conversion
    acceptEuros(Euros{50.0}); // OK: explicit construction
    std::cout << "Must explicitly construct Euros{50.0}\n";

    // Euros e = 50.0;              // ERROR: explicit constructor
    Euros e{50.0}; // OK: direct initialization

    // --- Summary ---
    // 1. operator T() has no return type and no parameters
    // 2. Mark typecasts 'explicit' unless the conversion is natural
    // 3. explicit operator bool() still works in if/while/&&/||/! (contextual conversion)
    // 4. Prefer converting constructors over typecast overloads
    // 5. Mark converting constructors 'explicit' to prevent accidental implicit conversions

    return 0;
}
