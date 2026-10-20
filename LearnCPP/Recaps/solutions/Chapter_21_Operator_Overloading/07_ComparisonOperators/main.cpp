// Project 07: Overloading Comparison Operators
// ===============================================
// All six comparison operators (==, !=, <, >, <=, >=) can be overloaded.
// To minimize redundancy: implement only operator== and operator<, then
// define the other four in terms of those two.
// C++20 introduces operator<=> (spaceship operator) to further reduce boilerplate.

#include <iostream>
#include <compare> // For std::strong_ordering (C++20)
#include <string>

// -- Approach 1: Traditional (pre-C++20) --
// Implement == and <, derive the rest from those two.

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents) : m_cents{cents} {}
    int getCents() const { return m_cents; }

    // Only these two are "real" implementations
    friend bool operator==(const Cents &c1, const Cents &c2);
    friend bool operator<(const Cents &c1, const Cents &c2);
};

bool operator==(const Cents &c1, const Cents &c2) { return c1.m_cents == c2.m_cents; }
bool operator<(const Cents &c1, const Cents &c2) { return c1.m_cents < c2.m_cents; }

// Derived operators - written in terms of == and <
bool operator!=(const Cents &c1, const Cents &c2) { return !(c1 == c2); }
bool operator>(const Cents &c1, const Cents &c2) { return c2 < c1; }
bool operator<=(const Cents &c1, const Cents &c2) { return !(c2 < c1); }
bool operator>=(const Cents &c1, const Cents &c2) { return !(c1 < c2); }

// -- Approach 2: C++20 with operator<=> (spaceship operator) --
// One operator generates all six comparison operators automatically!

class Score
{
private:
    int m_value{};
    std::string m_name{};

public:
    Score(std::string name, int value) : m_value{value}, m_name{std::move(name)} {}

    int getValue() const { return m_value; }
    const std::string &getName() const { return m_name; }

    // C++20: Defaulted spaceship operator compares all members in declaration order.
    // This generates ==, !=, <, >, <=, >= automatically.
    auto operator<=>(const Score &) const = default;
};

int main()
{
    // --- Traditional approach (Cents) ---
    Cents dime{10};
    Cents quarter{25};
    Cents anotherDime{10};

    std::cout << "=== Traditional Comparison (Cents) ===\n";
    std::cout << "10 == 25? " << std::boolalpha << (dime == quarter) << '\n';
    std::cout << "10 != 25? " << (dime != quarter) << '\n';
    std::cout << "10 <  25? " << (dime < quarter) << '\n';
    std::cout << "10 >  25? " << (dime > quarter) << '\n';
    std::cout << "10 <= 10? " << (dime <= anotherDime) << '\n';
    std::cout << "25 >= 10? " << (quarter >= dime) << '\n';

    // --- C++20 spaceship operator (Score) ---
    Score alice{"Alice", 95};
    Score bob{"Bob", 87};
    Score alice2{"Alice", 95};

    std::cout << "\n=== C++20 Spaceship Operator (Score) ===\n";
    std::cout << "Alice(95) == Bob(87)?   " << (alice == bob) << '\n';
    std::cout << "Alice(95) == Alice(95)? " << (alice == alice2) << '\n';
    std::cout << "Alice(95) >  Bob(87)?   " << (alice > bob) << '\n';
    std::cout << "Bob(87)   <  Alice(95)? " << (bob < alice) << '\n';
    std::cout << "Alice(95) != Bob(87)?   " << (alice != bob) << '\n';

    // Key points:
    // 1. Traditional: implement == and <, derive !=, >, <=, >= from them.
    // 2. C++20: use operator<=> = default to auto-generate all six.
    // 3. Comparison operators are best as friend/normal functions (binary, don't modify).

    return 0;
}
