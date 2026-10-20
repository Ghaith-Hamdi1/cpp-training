// Chapter 15 - Project 09: Friend Classes and Friend Member Functions
// ====================================================================
//
// An entire class can be declared a friend:
//     friend class Display;
// This gives ALL of Display's member functions access to the
// befriending class's private members.
//
// Alternatively, a SINGLE member function can be friended:
//     friend void Display::showValue(const Storage&);
// This requires careful ordering or forward declarations.
//
// Critical rules about friendship:
//   - Friendship is NOT reciprocal.   If A friends B, B cannot access A's privates.
//   - Friendship is NOT transitive.   If A friends B and B friends C, C cannot access A.
//   - Friendship is NOT inherited.    A friend of Base is not automatically a friend of Derived.

#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------
// Example 1: Friend class - Display can access Storage's privates
// -------------------------------------------------------
class Storage
{
private:
    int m_value{};
    std::string m_label{};

public:
    Storage(int value, const std::string &label)
        : m_value{value}, m_label{label}
    {
    }

    // Grant ALL members of Display access to Storage's private data
    friend class Display;
};

class Display
{
public:
    // Can access Storage's private members because Display is a friend of Storage.
    static void show(const Storage &s)
    {
        std::cout << "[Display] " << s.m_label << " = " << s.m_value << '\n';
    }
};

// -------------------------------------------------------
// Example 2: Demonstrating that friendship is NOT reciprocal
// -------------------------------------------------------
class Engine
{
private:
    int m_horsepower{200};

public:
    Engine() = default;
    Engine(int hp) : m_horsepower{hp} {}

    // Engine friends Car - Car can access Engine's privates.
    friend class Car;

    int getHorsepower() const { return m_horsepower; }
};

class Car
{
private:
    std::string m_model{"Sedan"};
    Engine m_engine{};

public:
    Car() = default;
    Car(const std::string &model, int hp)
        : m_model{model}, m_engine{hp}
    {
    }

    void describe() const
    {
        // Car CAN access Engine's private m_horsepower (Engine friended Car)
        std::cout << m_model << " with " << m_engine.m_horsepower << " HP\n";
    }

    // But Engine CANNOT access Car's m_model - friendship is NOT reciprocal.
    // If Engine tried `car.m_model`, it would fail to compile.
};

// -------------------------------------------------------
// Example 3: Friend member function (single function, not entire class)
// -------------------------------------------------------

// Forward-declare Inventory so Auditor can reference it
class Inventory;

class Auditor
{
public:
    // Declaration only - defined after Inventory is complete
    void audit(const Inventory &inv) const;
};

class Inventory
{
private:
    std::vector<std::string> m_items{};
    double m_totalValue{0.0};

public:
    void addItem(const std::string &name, double value)
    {
        m_items.push_back(name);
        m_totalValue += value;
    }

    // Friend a SINGLE member function of Auditor (not the entire class)
    friend void Auditor::audit(const Inventory &inv) const;
};

// Now define Auditor::audit - it has access to Inventory's privates
void Auditor::audit(const Inventory &inv) const
{
    std::cout << "--- Audit Report ---\n";
    std::cout << "Items (" << inv.m_items.size() << "):\n";
    for (const auto &item : inv.m_items)
        std::cout << "  - " << item << '\n';
    std::cout << "Total value: $" << inv.m_totalValue << '\n';
}

int main()
{
    // --- Example 1: Friend class ---
    std::cout << "=== Friend Class ===\n";
    Storage s{42, "answer"};
    Display::show(s); // Display accesses Storage's privates

    // --- Example 2: Non-reciprocal ---
    std::cout << "\n=== Non-reciprocal Friendship ===\n";
    Car car{"Mustang", 450};
    car.describe(); // Car accesses Engine's private m_horsepower
    // Engine cannot access Car's m_model - friendship only goes one way!

    // --- Example 3: Friend member function ---
    std::cout << "\n=== Friend Member Function ===\n";
    Inventory inv{};
    inv.addItem("Laptop", 999.99);
    inv.addItem("Mouse", 29.99);
    inv.addItem("Keyboard", 79.99);

    Auditor auditor{};
    auditor.audit(inv); // Only Auditor::audit has access, not all of Auditor

    return 0;
}
