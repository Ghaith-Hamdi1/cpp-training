// Chapter 15 - Project 06: Static Member Variables
// ==================================================
//
// Static member variables are shared by ALL objects of the class.
// They exist even if no objects have been instantiated.
//
// Declaration: `static int s_count;` inside the class.
// Traditional definition (pre-C++17): `int ClassName::s_count{};` outside.
//
// C++17+: `static inline int s_count{};`   - initialize inside the class.
//         `static constexpr int s_max = 5;` - always inline, always OK inside.
//
// Access: `ClassName::s_var` (preferred) or via an object (`obj.s_var`).
//
// Only static members may use `auto` or CTAD for type deduction.

#include <iostream>
#include <string>

// -------------------------------------------------------
// Example 1: Counting instances with a static member
// -------------------------------------------------------
class Widget
{
private:
    int m_id{};

    // Static member variable - shared across all Widget objects.
    // Using `static inline` (C++17) so we can initialize here.
    static inline int s_idGenerator{0};
    static inline int s_count{0};

public:
    Widget()
        : m_id{++s_idGenerator}
    {
        ++s_count;
        std::cout << "Widget #" << m_id << " created (total: " << s_count << ")\n";
    }

    ~Widget()
    {
        --s_count;
        std::cout << "Widget #" << m_id << " destroyed (total: " << s_count << ")\n";
    }

    int getId() const { return m_id; }

    // Static getter - accessible without an object
    static int getCount() { return s_count; }
};

// -------------------------------------------------------
// Example 2: static constexpr - compile-time constant
// -------------------------------------------------------
class Config
{
public:
    // static constexpr is implicitly inline - can be defined inside the class.
    static constexpr int maxPlayers{4};
    static constexpr double gravity{9.81};
    static constexpr const char *gameName{"Astro Blaster"};
};

// -------------------------------------------------------
// Example 3: Traditional out-of-class definition (pre-C++17)
// -------------------------------------------------------
class Counter
{
private:
    // Declaration only (no inline, no constexpr)
    static int s_total;

public:
    static void increment() { ++s_total; }
    static int getTotal() { return s_total; }
};

// Definition outside the class - required for non-inline static members
int Counter::s_total{0};

int main()
{
    // --- Example 1: Instance counting ---
    std::cout << "--- Widget instance counting ---\n";
    std::cout << "Widgets alive: " << Widget::getCount() << '\n'; // 0

    Widget w1;
    Widget w2;
    std::cout << "Widgets alive: " << Widget::getCount() << '\n'; // 2

    {
        Widget w3;
        std::cout << "Widgets alive: " << Widget::getCount() << '\n'; // 3
    } // w3 destroyed

    std::cout << "Widgets alive: " << Widget::getCount() << '\n'; // 2

    // --- Example 2: static constexpr ---
    std::cout << "\n--- Config constants ---\n";
    std::cout << "Game:        " << Config::gameName << '\n';
    std::cout << "Max players: " << Config::maxPlayers << '\n';
    std::cout << "Gravity:     " << Config::gravity << '\n';

    // --- Example 3: Traditional definition ---
    std::cout << "\n--- Counter (traditional static) ---\n";
    Counter::increment();
    Counter::increment();
    Counter::increment();
    std::cout << "Counter total: " << Counter::getTotal() << '\n'; // 3

    return 0;
}
