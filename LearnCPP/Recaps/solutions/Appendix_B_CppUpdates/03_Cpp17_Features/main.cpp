// Appendix B - C++ Updates: Project 03 - C++17 Features
// C++17 was a major release that brought practical, everyday improvements.
// Many features reduce boilerplate and make code safer and more expressive.

#include <iostream>
#include <string>
#include <string_view> // C++17: lightweight, non-owning string reference
#include <optional>    // C++17: represents "a value or nothing"
#include <vector>
#include <map>
#include <tuple>
#include <type_traits>

// ============================================================================
// 1. INLINE VARIABLES
// ============================================================================
// Before C++17: Constants in headers had to be declared extern in the header
// and defined in exactly one .cpp file, or use ugly workarounds.
// Now: 'inline' variables can be defined in headers without ODR violations.
// The linker deduplicates them automatically.

// In a real project, this would be in a header file:
inline constexpr int MAX_PLAYERS = 4;             // No need for a .cpp definition
inline const std::string DEFAULT_NAME = "Player"; // Works for non-literal types too

// ============================================================================
// 2. CONSTEXPR IF
// ============================================================================
// Before C++17: Generic code that needed different behavior for different types
// required template specialization or SFINAE - complex and verbose.
// Now: 'if constexpr' evaluates conditions at compile-time. The false branch
// is discarded entirely (not even type-checked for the given type).

template <typename T>
std::string describeType(const T &value)
{
    if constexpr (std::is_integral_v<T>)
    {
        return "integer with value " + std::to_string(value);
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        return "floating-point with value " + std::to_string(value);
    }
    else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view>)
    {
        return "string: \"" + std::string(value) + "\"";
    }
    else
    {
        return "(unknown type)";
    }
}

// ============================================================================
// 3. std::optional
// ============================================================================
// Before C++17: Representing "no value" meant returning sentinel values (-1, ""),
// using output parameters, or throwing exceptions. All had downsides.
// Now: std::optional<T> explicitly represents "a T or nothing."

std::optional<int> findIndex(const std::vector<std::string> &vec, const std::string &target)
{
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == target)
            return static_cast<int>(i); // Found: return the index wrapped in optional
    }
    return std::nullopt; // Not found: explicitly "no value"
}

// ============================================================================
// 4. CLASS TEMPLATE ARGUMENT DEDUCTION (CTAD)
// ============================================================================
// Before C++17: You always had to specify template arguments:
//   std::pair<int, std::string> p(1, "hello");
//   std::vector<int> v{1, 2, 3};
// Now: The compiler can often deduce them:
//   std::pair p(1, "hello");   // deduced as pair<int, string>

// Simple wrapper to demonstrate CTAD with user-defined types
template <typename T>
struct Wrapper
{
    T value;
    Wrapper(T v) : value{v} {} // Deduction guide is implicit for this case
};

int main()
{
    std::cout << "=== Appendix B: C++17 Features ===\n\n";

    // ========================================================================
    // 1. std::string_view
    // ========================================================================
    // Before C++17: Functions taking strings had to choose between:
    //   const std::string&  (forces callers to create a std::string)
    //   const char*         (loses size info, can't use std::string methods)
    // Now: string_view is a non-owning, lightweight view into any contiguous
    // char sequence. No allocation, no copying.
    std::cout << "--- 1. std::string_view ---\n";

    auto printView = [](std::string_view sv)
    {
        std::cout << "  View: \"" << sv << "\" (length: " << sv.length() << ")\n";
    };

    // Works with string literals, std::string, substrings - all zero-copy
    printView("Hello from a literal"); // No std::string created
    std::string str = "Hello from std::string";
    printView(str);                                // No copy
    printView(std::string_view{str}.substr(0, 5)); // Substring, still no copy

    // string_view supports familiar operations
    std::string_view greeting = "Hello, C++17 World!";
    std::cout << "  Starts with 'Hello': " << std::boolalpha
              << (greeting.substr(0, 5) == "Hello") << '\n';
    std::cout << "  Find 'C++': position " << greeting.find("C++") << '\n';
    std::cout << '\n';

    // ========================================================================
    // 2. std::optional
    // ========================================================================
    std::cout << "--- 2. std::optional ---\n";

    std::vector<std::string> names{"Alice", "Bob", "Charlie", "Diana"};

    auto result1 = findIndex(names, "Charlie");
    auto result2 = findIndex(names, "Zara");

    // Check with has_value() or implicit bool conversion
    if (result1.has_value())
    {
        std::cout << "  Found 'Charlie' at index " << result1.value() << '\n';
    }

    // Use value_or() for a default when the optional is empty
    std::cout << "  'Zara' index: " << result2.value_or(-1) << " (not found)\n";

    // Optional with in-place construction
    std::optional<std::string> optStr{std::in_place, "Constructed in-place"};
    std::cout << "  Optional string: " << *optStr << '\n';

    optStr.reset(); // Clear the value
    std::cout << "  After reset, has_value: " << optStr.has_value() << '\n';
    std::cout << '\n';

    // ========================================================================
    // 3. STRUCTURED BINDINGS
    // ========================================================================
    // Before C++17: Accessing tuple/pair/struct members required .first/.second
    // or std::get<0>(), which was unreadable.
    // Now: auto [a, b, c] = ... unpacks into named variables.
    std::cout << "--- 3. Structured bindings ---\n";

    // With std::pair
    std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};

    // Old way: for (const auto& p : scores) { p.first ... p.second ... }
    // New way: direct destructuring into named variables
    std::cout << "  Scores:\n";
    for (const auto &[name, score] : scores)
    {
        std::cout << "    " << name << ": " << score << '\n';
    }

    // With std::tuple
    auto getStudentInfo = []() -> std::tuple<std::string, int, double>
    {
        return {"Diana", 20, 3.85};
    };
    auto [name, age, gpa] = getStudentInfo();
    std::cout << "  Student: " << name << ", age " << age << ", GPA " << gpa << '\n';

    // With arrays
    int arr[3] = {10, 20, 30};
    auto [x, y, z] = arr;
    std::cout << "  Array unpacked: " << x << ", " << y << ", " << z << '\n';
    std::cout << '\n';

    // ========================================================================
    // 4. CONSTEXPR IF
    // ========================================================================
    std::cout << "--- 4. constexpr if ---\n";

    std::cout << "  42:       " << describeType(42) << '\n';
    std::cout << "  3.14:     " << describeType(3.14) << '\n';
    std::cout << "  \"hello\":  " << describeType(std::string{"hello"}) << '\n';
    std::cout << '\n';

    // ========================================================================
    // 5. CLASS TEMPLATE ARGUMENT DEDUCTION (CTAD)
    // ========================================================================
    std::cout << "--- 5. Class Template Argument Deduction (CTAD) ---\n";

    // Before: std::pair<int, double> p{1, 3.14};
    // Now: compiler deduces <int, double>
    std::pair p{1, 3.14};
    std::cout << "  pair: {" << p.first << ", " << p.second << "}\n";

    std::tuple t{42, "hello", 3.14};
    std::cout << "  tuple: {" << std::get<0>(t) << ", " << std::get<1>(t)
              << ", " << std::get<2>(t) << "}\n";

    std::vector v{1, 2, 3, 4, 5}; // Deduced as vector<int>
    std::cout << "  vector (CTAD): ";
    for (auto val : v)
        std::cout << val << ' ';
    std::cout << '\n';

    Wrapper w{42}; // Deduced as Wrapper<int>
    std::cout << "  Wrapper value: " << w.value << " (Wrapper<int>)\n";
    std::cout << '\n';

    // ========================================================================
    // 6. INLINE VARIABLES
    // ========================================================================
    std::cout << "--- 6. Inline variables ---\n";
    std::cout << "  MAX_PLAYERS  = " << MAX_PLAYERS << " (inline constexpr)\n";
    std::cout << "  DEFAULT_NAME = \"" << DEFAULT_NAME << "\" (inline const)\n";
    std::cout << "  These can be defined in headers without ODR violations.\n";
    std::cout << '\n';

    // ========================================================================
    // 7. IF/SWITCH WITH INITIALIZER
    // ========================================================================
    // Before C++17: Variables used only in an if-condition leaked into the
    // surrounding scope, or you needed extra braces.
    // Now: if (init; condition) keeps the variable scoped to the if/else.
    std::cout << "--- 7. if/switch with initializer ---\n";

    // Old way:
    // auto it = scores.find("Alice");
    // if (it != scores.end()) { ... }
    // // 'it' is still in scope here - undesirable

    // New way: 'it' is scoped to the if/else block only
    if (auto it = scores.find("Bob"); it != scores.end())
    {
        std::cout << "  Found " << it->first << " with score " << it->second << '\n';
    }
    else
    {
        std::cout << "  Not found\n";
    }
    // 'it' no longer exists here - cleaner scope

    if (auto val = findIndex(names, "Alice"); val)
    {
        std::cout << "  Alice found at index " << *val << '\n';
    }
    std::cout << '\n';

    // ========================================================================
    // 8. NESTED NAMESPACES (syntax sugar)
    // ========================================================================
    std::cout << "--- 8. Nested namespace shorthand ---\n";
    std::cout << "  Before: namespace A { namespace B { namespace C { ... } } }\n";
    std::cout << "  Now:    namespace A::B::C { ... }\n";
    std::cout << "  (Demonstrated at namespace level, not inside main)\n";

    std::cout << "\n=== C++17 demo complete ===\n";

    return 0;
}
