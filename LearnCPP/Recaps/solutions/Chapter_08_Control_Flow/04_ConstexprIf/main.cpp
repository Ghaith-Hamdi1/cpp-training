// Chapter 8 - Project 04: Constexpr If
// Demonstrates compile-time branching with if constexpr (C++17).
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <type_traits> // std::is_integral_v, std::is_floating_point_v
#include <string>

// -------------------------------------------------------
// 1. Basic if constexpr - compile-time constant
// -------------------------------------------------------
// The untaken branch is completely discarded at compile time.
// This differs from a regular if, where both branches must compile.

constexpr int debugLevel{0}; // Change to 1 or 2 to see different output

void showDebugInfo()
{
    if constexpr (debugLevel >= 2)
    {
        std::cout << "[VERBOSE] Full debug diagnostics enabled.\n";
    }
    else if constexpr (debugLevel >= 1)
    {
        std::cout << "[DEBUG] Basic debug info enabled.\n";
    }
    else
    {
        std::cout << "[RELEASE] No debug output.\n";
    }
}

// -------------------------------------------------------
// 2. if constexpr in templates - type-dependent branching
// -------------------------------------------------------
// Without if constexpr, you'd need template specialization
// or SFINAE. if constexpr makes it readable.

template <typename T>
void describeType(T value)
{
    std::cout << "Value: " << value << " - ";

    if constexpr (std::is_integral_v<T>)
    {
        std::cout << "This is an integer type";
        if constexpr (std::is_signed_v<T>)
            std::cout << " (signed)";
        else
            std::cout << " (unsigned)";
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        std::cout << "This is a floating-point type";
    }
    else
    {
        std::cout << "This is some other type";
    }
    std::cout << ".\n";
}

// -------------------------------------------------------
// 3. Platform-specific compile-time branching
// -------------------------------------------------------
void showPlatform()
{
    // Simulated platform constant (in real code from build system)
    constexpr bool isWindows{
#ifdef _WIN32
        true
#else
        false
#endif
    };

    if constexpr (isWindows)
    {
        std::cout << "Running on Windows.\n";
    }
    else
    {
        std::cout << "Running on a non-Windows platform.\n";
    }
}

int main()
{
    std::cout << "=== 1. Debug level branching ===\n";
    showDebugInfo();

    std::cout << "\n=== 2. Template type branching ===\n";
    describeType(42);   // int (signed)
    describeType(3.14); // double (floating-point)
    describeType(7u);   // unsigned int
    describeType('A');  // char (signed integral on most platforms)

    std::cout << "\n=== 3. Platform branching ===\n";
    showPlatform();

    // -------------------------------------------------------
    // Key takeaway:
    // - if constexpr requires a compile-time constant condition
    // - The untaken branch is discarded and does NOT need to compile
    // - Perfect for templates and platform-specific code
    // -------------------------------------------------------

    return 0;
}
