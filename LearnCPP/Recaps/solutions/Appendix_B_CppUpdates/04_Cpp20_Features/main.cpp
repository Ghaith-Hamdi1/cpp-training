// Appendix B - C++ Updates: Project 04 - C++20 Features
// C++20 is the biggest update since C++11. It introduces Concepts, Ranges,
// Coroutines, and Modules - along with many smaller but impactful features.
// This demo focuses on the features most relevant to learners.

#include <iostream>
#include <string>
#include <vector>
#include <span>     // C++20: non-owning view over contiguous memory
#include <compare>  // C++20: spaceship operator <=>
#include <concepts> // C++20: constraints on template parameters
#include <type_traits>
#include <numeric> // std::accumulate
#include <array>
#include <cmath>

// ============================================================================
// 1. CONCEPTS
// ============================================================================
// Before C++20: Template error messages were notoriously cryptic. If you passed
// the wrong type, you'd get pages of errors from deep inside the implementation.
// Also, there was no clean way to express "this function requires a numeric type."
// Now: Concepts let you state requirements on template parameters clearly.
// Bad types get clean error messages at the call site.

// Define a concept: T must support +, -, *, / and be constructible from int
template <typename T>
concept Numeric = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
};

// Use the concept to constrain the template - clean syntax!
template <Numeric T>
T average(const std::vector<T> &values)
{
    T sum{};
    for (const auto &v : values)
        sum = sum + v;
    return sum / static_cast<T>(values.size());
}

// Shorthand concept syntax using auto
void printSortable(std::sortable auto &range)
{
    std::sort(range.begin(), range.end());
    for (const auto &elem : range)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// Using standard library concepts
template <std::integral T>
T doubleValue(T x)
{
    return x * 2;
}

// ============================================================================
// 2. SPACESHIP OPERATOR (<=>)
// ============================================================================
// Before C++20: To make a class fully comparable, you had to write up to 6
// operators: ==, !=, <, <=, >, >=. Tedious and error-prone.
// Now: The spaceship operator <=> generates all six from one declaration.

struct Version
{
    int major;
    int minor;
    int patch;

    // This single line generates ==, !=, <, <=, >, >= automatically!
    auto operator<=>(const Version &) const = default;
};

// Custom spaceship for more control
struct Temperature
{
    double celsius;

    // Custom comparison - only compare the temperature value
    auto operator<=>(const Temperature &other) const
    {
        return celsius <=> other.celsius;
    }
    bool operator==(const Temperature &other) const
    {
        return celsius == other.celsius;
    }
};

// ============================================================================
// 3. CONSTEVAL - guaranteed compile-time evaluation
// ============================================================================
// Before C++20: constexpr functions *could* run at compile time but weren't
// guaranteed to. Sometimes they'd silently evaluate at runtime.
// Now: consteval functions MUST be evaluated at compile time. If they can't be,
// you get a compile error - guaranteeing zero runtime cost.

consteval int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

consteval int triangleNumber(int n)
{
    return n * (n + 1) / 2;
}

// ============================================================================
// 4. DESIGNATED INITIALIZERS
// ============================================================================
// Before C++20 (in C++): Aggregate initialization was positional - you had to
// remember the order of members. Error-prone for structs with many fields.
// Now: You can name the members you're initializing (C has had this for decades).

struct Config
{
    int width = 800;
    int height = 600;
    bool vsync = true;
    int fps_cap = 60;
};

struct Point3D
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

int main()
{
    std::cout << "=== Appendix B: C++20 Features ===\n\n";

    // ========================================================================
    // 1. CONCEPTS
    // ========================================================================
    std::cout << "--- 1. Concepts ---\n";

    std::vector<int> intVals{10, 20, 30, 40, 50};
    std::vector<double> dblVals{1.5, 2.5, 3.5, 4.5};

    std::cout << "  Average of {10,20,30,40,50}: " << average(intVals) << '\n';
    std::cout << "  Average of {1.5,2.5,3.5,4.5}: " << average(dblVals) << '\n';

    // This would NOT compile - std::string doesn't satisfy Numeric:
    // std::vector<std::string> words{"a","b"};
    // average(words);  // Error: 'std::string' does not satisfy 'Numeric'
    // The error message is clear and points to the concept, not template internals.

    std::cout << "  doubleValue(21): " << doubleValue(21) << '\n';
    // doubleValue(3.14); // Error: 'double' does not satisfy 'std::integral'

    std::vector<int> sortMe{5, 3, 1, 4, 2};
    std::cout << "  Sorted: ";
    printSortable(sortMe);
    std::cout << '\n';

    // ========================================================================
    // 2. DESIGNATED INITIALIZERS
    // ========================================================================
    // Name the fields you want to set - others keep their defaults.
    // Order must match the declaration order (C++ requirement, not C).
    std::cout << "--- 2. Designated initializers ---\n";

    Config fullscreen{
        .width = 1920,
        .height = 1080,
        .vsync = true,
        .fps_cap = 144};

    // Only set some fields; others use their defaults
    Config windowed{
        .width = 1280,
        .height = 720
        // vsync defaults to true, fps_cap defaults to 60
    };

    std::cout << "  Fullscreen: " << fullscreen.width << "x" << fullscreen.height
              << ", vsync=" << std::boolalpha << fullscreen.vsync
              << ", fps=" << fullscreen.fps_cap << '\n';
    std::cout << "  Windowed:   " << windowed.width << "x" << windowed.height
              << ", vsync=" << windowed.vsync
              << ", fps=" << windowed.fps_cap << " (defaults)\n";

    Point3D origin{};     // All defaults: 0, 0, 0
    Point3D up{.y = 1.0}; // Only set y
    Point3D corner{.x = 1.0, .y = 2.0, .z = 3.0};

    std::cout << "  Origin: (" << origin.x << ", " << origin.y << ", " << origin.z << ")\n";
    std::cout << "  Up:     (" << up.x << ", " << up.y << ", " << up.z << ")\n";
    std::cout << "  Corner: (" << corner.x << ", " << corner.y << ", " << corner.z << ")\n";
    std::cout << '\n';

    // ========================================================================
    // 3. SPACESHIP OPERATOR (<=>)
    // ========================================================================
    std::cout << "--- 3. Spaceship operator (<=>) ---\n";

    Version v1{2, 1, 0};
    Version v2{2, 3, 1};
    Version v3{2, 1, 0};

    std::cout << "  v1(2.1.0) == v3(2.1.0): " << std::boolalpha << (v1 == v3) << '\n';
    std::cout << "  v1(2.1.0) != v2(2.3.1): " << (v1 != v2) << '\n';
    std::cout << "  v1(2.1.0) <  v2(2.3.1): " << (v1 < v2) << '\n';
    std::cout << "  v2(2.3.1) >= v1(2.1.0): " << (v2 >= v1) << '\n';

    // All 6 comparison operators generated from one defaulted <=>!

    Temperature hot{35.0};
    Temperature cold{10.0};
    std::cout << "  35°C > 10°C:  " << (hot > cold) << '\n';
    std::cout << "  35°C == 35°C: " << (hot == Temperature{35.0}) << '\n';
    std::cout << '\n';

    // ========================================================================
    // 4. CONSTEVAL
    // ========================================================================
    std::cout << "--- 4. consteval (immediate functions) ---\n";

    // These are guaranteed to be computed at compile time
    constexpr int fact5 = factorial(5);       // 120 - computed by compiler
    constexpr int fact10 = factorial(10);     // 3628800 - computed by compiler
    constexpr int tri10 = triangleNumber(10); // 55

    std::cout << "  5!  = " << fact5 << " (compile-time)\n";
    std::cout << "  10! = " << fact10 << " (compile-time)\n";
    std::cout << "  Triangle(10) = " << tri10 << " (compile-time)\n";

    // This would NOT compile - consteval requires compile-time evaluation:
    // int n = 5;
    // int result = factorial(n);  // Error: 'n' is not a constant expression
    std::cout << '\n';

    // ========================================================================
    // 5. std::span - non-owning view over contiguous data
    // ========================================================================
    // Before C++20: Functions taking arrays needed (T* ptr, size_t len) pairs
    // or forced callers to use a specific container type.
    // Now: std::span<T> works with any contiguous memory: arrays, vectors, etc.
    std::cout << "--- 5. std::span ---\n";

    // One function that works with any contiguous container
    auto printSpan = [](std::span<const int> data, const std::string &label)
    {
        std::cout << "  " << label << " [" << data.size() << " elements]: ";
        for (int val : data)
            std::cout << val << ' ';
        std::cout << '\n';
    };

    int cArr[] = {1, 2, 3, 4, 5};
    std::array<int, 4> stdArr{10, 20, 30, 40};
    std::vector<int> vec{100, 200, 300};

    // Same function accepts C array, std::array, and std::vector
    printSpan(cArr, "C array");
    printSpan(stdArr, "std::array");
    printSpan(vec, "std::vector");

    // Span supports subviews
    std::span<int> full{cArr};
    auto firstThree = full.first(3);
    auto lastTwo = full.last(2);
    auto middle = full.subspan(1, 3);

    std::cout << "  first(3):     ";
    for (int v : firstThree)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "  last(2):      ";
    for (int v : lastTwo)
        std::cout << v << ' ';
    std::cout << '\n';
    std::cout << "  subspan(1,3): ";
    for (int v : middle)
        std::cout << v << ' ';
    std::cout << '\n';

    // Span has useful properties
    std::cout << "  Size: " << full.size() << ", Size in bytes: " << full.size_bytes() << '\n';
    std::cout << "  Empty: " << std::boolalpha << full.empty() << '\n';
    std::cout << '\n';

    // ========================================================================
    // 6. ADDITIONAL C++20 HIGHLIGHTS (brief mentions)
    // ========================================================================
    std::cout << "--- 6. Other C++20 highlights ---\n";

    // constinit - ensures a variable is initialized at compile time
    // (useful for avoiding the "static initialization order fiasco")
    std::cout << "  constinit: Ensures static/thread_local vars are compile-time initialized\n";

    // Ranges library (too large to demo fully here)
    std::cout << "  Ranges: Composable algorithms with views (e.g., views::filter | views::transform)\n";

    // Coroutines (too complex for a basic demo)
    std::cout << "  Coroutines: co_await, co_yield, co_return for async/generator patterns\n";

    // Modules (requires special build support)
    std::cout << "  Modules: import std; replaces #include for faster compilation\n";

    // Three-way comparison category types
    std::cout << "  Comparison categories: strong_ordering, weak_ordering, partial_ordering\n";

    std::cout << "\n=== C++20 demo complete ===\n";

    return 0;
}
