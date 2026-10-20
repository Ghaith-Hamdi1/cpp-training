// Chapter 14 - Project 12: Copy Elision
// ========================================
// Key concepts:
//   - Copy elision is a compiler optimization that REMOVES unnecessary
//     copy constructor calls, even if the copy constructor has side effects.
//   - Mandatory since C++17 in certain cases (e.g., returning a prvalue).
//   - This means you should NOT rely on copy constructor side effects
//     (like printing), because the compiler may skip them.
//   - All six initialization forms work with classes.

#include <iostream>

class Widget
{
public:
    Widget(int id) : m_id{id}
    {
        std::cout << "  [Widget " << m_id << " constructed]\n";
    }

    Widget(const Widget &other) : m_id{other.m_id}
    {
        std::cout << "  [Widget " << m_id << " COPIED]\n";
    }

    int getId() const { return m_id; }

    void print() const
    {
        std::cout << "Widget { id=" << m_id << " }\n";
    }

private:
    int m_id{};
};

// Returns a Widget by value - in C++17, mandatory copy elision means
// the object is constructed directly in the caller's memory.
Widget createWidget(int id)
{
    return Widget{id}; // prvalue - guaranteed no copy in C++17
}

// Takes a Widget by value - may or may not trigger a copy
void processWidget(Widget w)
{
    std::cout << "Processing: ";
    w.print();
}

int main()
{
    // --- Different initialization forms ---
    std::cout << "=== Initialization forms ===\n";

    std::cout << "1. Direct list init:\n";
    Widget w1{1}; // direct list initialization

    std::cout << "2. Copy init:\n";
    Widget w2 = Widget{2}; // copy elision: no copy in C++17

    std::cout << "3. Direct init:\n";
    Widget w3(3); // direct initialization

    std::cout << "4. Copy init from named:\n";
    Widget w4 = w1; // genuine copy - no elision possible

    // --- Copy elision with function return ---
    std::cout << "\n=== Return value optimization (copy elision) ===\n";

    std::cout << "Creating via factory:\n";
    Widget w5 = createWidget(5); // mandatory elision in C++17
    w5.print();
    // Note: you should see only ONE "constructed" message, NO "COPIED".
    // The Widget is built directly into w5's memory.

    // --- Passing a prvalue to a function taking by value ---
    std::cout << "\n=== Passing prvalue by value ===\n";
    std::cout << "Passing temporary:\n";
    processWidget(Widget{6}); // mandatory elision for the argument

    std::cout << "\nPassing named object:\n";
    processWidget(w1); // this IS a copy - w1 is an lvalue

    std::cout << "\n-- Takeaway --\n"
              << "Copy elision can skip copy constructor calls entirely.\n"
              << "Don't rely on side effects in copy constructors.\n"
              << "Mandatory for prvalues since C++17.\n";

    return 0;
}
