// Appendix B - C++ Updates: Project 01 - C++11 Key Features
// Demonstrates the most impactful features introduced in C++11,
// the standard that modernized C++ and changed how we write code.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>     // std::unique_ptr, std::shared_ptr
#include <functional> // std::function

// ============================================================================
// 1. SCOPED ENUMERATIONS (enum class)
// ============================================================================
// Before C++11: Enumerators leaked into the enclosing scope and implicitly
// converted to int. This caused name collisions and type-safety issues.
// Now: enum class creates a strongly-typed, scoped enumeration.

enum class Color
{
    Red,
    Green,
    Blue
}; // Values are Color::Red, etc.
enum class TrafficLight
{
    Red,
    Yellow,
    Green
}; // No collision with Color::Red!

// ============================================================================
// 2. NULLPTR
// ============================================================================
// Before C++11: We used NULL (which is just 0) or literal 0 for null pointers.
// This caused ambiguity: foo(0) - is that an int or a null pointer?
// Now: nullptr is a keyword with type std::nullptr_t, no ambiguity.

void overloadDemo(int x) { std::cout << "  Called overloadDemo(int): " << x << '\n'; }
void overloadDemo(int *ptr) { std::cout << "  Called overloadDemo(int*): " << (ptr ? "non-null" : "null") << '\n'; }

// ============================================================================
// 3. MOVE SEMANTICS (basics)
// ============================================================================
// Before C++11: Returning large objects from functions meant expensive copies.
// Now: Move constructors/assignment "steal" resources from temporaries, making
// returns and container operations much faster.

class SimpleBuffer
{
    std::string m_name;
    int *m_data;
    std::size_t m_size;

public:
    // Regular constructor
    SimpleBuffer(const std::string &name, std::size_t size)
        : m_name{name}, m_data{new int[size]{}}, m_size{size}
    {
        std::cout << "  Constructed: " << m_name << " (size " << m_size << ")\n";
    }

    // Move constructor - steals the guts of 'other' instead of copying
    SimpleBuffer(SimpleBuffer &&other) noexcept
        : m_name{std::move(other.m_name)}, m_data{other.m_data}, m_size{other.m_size}
    {
        other.m_data = nullptr; // Leave 'other' in a valid but empty state
        other.m_size = 0;
        std::cout << "  Moved: " << m_name << '\n';
    }

    // Destructor
    ~SimpleBuffer()
    {
        delete[] m_data;
    }

    // Delete copy to keep the example simple
    SimpleBuffer(const SimpleBuffer &) = delete;
    SimpleBuffer &operator=(const SimpleBuffer &) = delete;

    const std::string &name() const { return m_name; }
    std::size_t size() const { return m_size; }
};

// Factory function - return by value triggers move (not copy)
SimpleBuffer createBuffer(const std::string &name, std::size_t size)
{
    return SimpleBuffer{name, size};
}

int main()
{
    std::cout << "=== Appendix B: C++11 Key Features ===\n\n";

    // ========================================================================
    // 1. AUTO TYPE DEDUCTION
    // ========================================================================
    // Before C++11: You had to spell out the full type, even for obvious cases
    //   std::vector<int>::iterator it = vec.begin(); // verbose!
    // Now: 'auto' lets the compiler deduce the type from the initializer.
    std::cout << "--- 1. auto keyword ---\n";

    auto intVal = 42;                        // deduced as int
    auto pi = 3.14159;                       // deduced as double
    auto msg = std::string{"Hello, C++11!"}; // deduced as std::string

    std::cout << "  intVal = " << intVal << " (int)\n";
    std::cout << "  pi     = " << pi << " (double)\n";
    std::cout << "  msg    = " << msg << " (std::string)\n\n";

    // ========================================================================
    // 2. RANGE-BASED FOR LOOPS
    // ========================================================================
    // Before C++11: Iterating required manual iterators or index-based loops.
    //   for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    // Now: for (auto& elem : container) is concise and less error-prone.
    std::cout << "--- 2. Range-based for loop ---\n";

    std::vector<int> numbers{10, 20, 30, 40, 50};
    std::cout << "  Numbers: ";
    for (const auto &n : numbers)
    { // 'const auto&' avoids copies
        std::cout << n << ' ';
    }
    std::cout << "\n\n";

    // ========================================================================
    // 3. NULLPTR
    // ========================================================================
    std::cout << "--- 3. nullptr ---\n";
    // overloadDemo(NULL);    // Ambiguous in many compilers! Is it int or int*?
    overloadDemo(0);       // Calls the int overload
    overloadDemo(nullptr); // Unambiguously calls the int* overload
    std::cout << '\n';

    // ========================================================================
    // 4. SCOPED ENUMS (enum class)
    // ========================================================================
    std::cout << "--- 4. Scoped enums (enum class) ---\n";

    Color c = Color::Blue;
    TrafficLight tl = TrafficLight::Green;

    // Color::Red and TrafficLight::Red are separate - no collision
    // Also, no implicit conversion to int:
    // int x = c;  // ERROR: won't compile, must use static_cast
    int colorInt = static_cast<int>(c);
    std::cout << "  Color::Blue as int = " << colorInt << '\n';
    std::cout << "  (Color::Red and TrafficLight::Red coexist without conflict)\n\n";

    // ========================================================================
    // 5. UNIFORM (BRACE) INITIALIZATION
    // ========================================================================
    // Before C++11: Multiple initialization syntaxes - int x = 5; int x(5);
    //   and no way to initialize aggregates uniformly.
    // Now: Braces {} work everywhere and prevent narrowing conversions.
    std::cout << "--- 5. Uniform initialization ---\n";

    int a{7};                       // Direct initialization
    double b{3.14};                 // Works for all types
    std::vector<int> v{1, 2, 3, 4}; // Initializer list
    // int narrow{ 3.14 };               // ERROR: narrowing conversion prevented!

    std::cout << "  a = " << a << ", b = " << b << '\n';
    std::cout << "  v = { ";
    for (const auto &elem : v)
        std::cout << elem << ' ';
    std::cout << "}\n\n";

    // ========================================================================
    // 6. LAMBDA EXPRESSIONS
    // ========================================================================
    // Before C++11: To pass custom behavior to algorithms, you needed to write
    //   a separate functor class. Extremely verbose for simple operations.
    // Now: Lambdas let you write inline, anonymous functions.
    std::cout << "--- 6. Lambda expressions ---\n";

    // Basic lambda:  [captures](params) -> return_type { body }
    auto greet = [](const std::string &name)
    {
        std::cout << "  Hello, " << name << "!\n";
    };
    greet("World");

    // Lambda with capture - captures 'multiplier' from the enclosing scope
    int multiplier = 3;
    auto multiply = [multiplier](int x)
    { return x * multiplier; };
    std::cout << "  5 * " << multiplier << " = " << multiply(5) << '\n';

    // Lambda with algorithms - count elements greater than 25
    auto count = std::count_if(numbers.begin(), numbers.end(),
                               [](int n)
                               { return n > 25; });
    std::cout << "  Numbers > 25: " << count << " out of " << numbers.size() << '\n';

    // Mutable lambda - captures by value but allows modification of the copy
    int counter = 0;
    auto increment = [counter]() mutable
    {
        return ++counter; // modifies the lambda's internal copy
    };
    std::cout << "  Increment calls: " << increment() << ", " << increment() << ", " << increment() << '\n';
    std::cout << "  Original counter still = " << counter << '\n';
    std::cout << '\n';

    // ========================================================================
    // 7. MOVE SEMANTICS
    // ========================================================================
    std::cout << "--- 7. Move semantics ---\n";

    // The factory function returns by value, but the move constructor is used
    // instead of a copy - the resources are "stolen" efficiently.
    auto buf = createBuffer("DataBlock", 1000);
    std::cout << "  Buffer '" << buf.name() << "' has size " << buf.size() << '\n';

    // std::move casts an lvalue to an rvalue reference, enabling the move
    auto buf2 = std::move(buf);
    std::cout << "  After std::move, buf2 name: '" << buf2.name() << "'\n";
    std::cout << "  Original buf name is now: '" << buf.name() << "' (moved-from)\n\n";

    // ========================================================================
    // 8. SMART POINTERS (bonus C++11 highlight)
    // ========================================================================
    std::cout << "--- 8. Smart pointers (unique_ptr, shared_ptr) ---\n";

    // Before C++11: Manual new/delete was error-prone (leaks, double-free).
    // Now: Smart pointers manage lifetime automatically.

    // unique_ptr: sole ownership, zero overhead over raw pointer
    auto uptr = std::make_unique<int>(42); // make_unique is C++14, but unique_ptr is C++11
    std::cout << "  unique_ptr value: " << *uptr << '\n';

    // shared_ptr: shared ownership with reference counting
    auto sptr1 = std::make_shared<std::string>("Shared Data");
    auto sptr2 = sptr1; // reference count = 2
    std::cout << "  shared_ptr value: " << *sptr1 << '\n';
    std::cout << "  Reference count: " << sptr1.use_count() << '\n';
    sptr2.reset(); // reference count = 1
    std::cout << "  After reset, count: " << sptr1.use_count() << '\n';

    std::cout << "\n=== C++11 demo complete ===\n";

    return 0;
}
