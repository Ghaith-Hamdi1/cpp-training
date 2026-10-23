// Project 08: Common Mistakes and Best Practices
// ================================================
// Appendix A.4 - Miscellaneous FAQ items:
//   - Always include your paired header
//   - Never #include .cpp files
//   - Don't make by-value parameters/return types const
//   - Set the correct language standard
//   - Use constexpr proactively (covered in project 06, brief recap)
//
// This program demonstrates each issue with correct and incorrect
// approaches (incorrect code is shown in comments).

#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::move

// -----------------------------------------------------------------------
// 1. Paired Headers - Always #include your own header in the .cpp
// -----------------------------------------------------------------------
// In a multi-file project, you'd have:
//
//   // math_utils.h
//   #ifndef MATH_UTILS_H
//   #define MATH_UTILS_H
//   int add(int a, int b);       // declaration
//   #endif
//
//   // math_utils.cpp
//   #include "math_utils.h"      // ← PAIRED HEADER (must be first!)
//   int add(int a, int b) {      // definition
//       return a + b;
//   }
//
// Why? If the declaration in .h and definition in .cpp don't match,
// including the paired header will produce a compile error immediately.
// Without it, you'd get a linker error - much harder to debug.
//
// Since this is a single-file demo, we simulate it:

// "Header" declaration
namespace MathUtils
{
    int add(int a, int b);
    double average(const std::vector<int> &v);
}

// "Implementation" - matches the declarations above
namespace MathUtils
{
    int add(int a, int b)
    {
        return a + b;
    }

    double average(const std::vector<int> &v)
    {
        if (v.empty())
            return 0.0;
        int sum = 0;
        for (int n : v)
            sum += n;
        return static_cast<double>(sum) / static_cast<double>(v.size());
    }
}

// -----------------------------------------------------------------------
// 2. const by-value parameters - DON'T DO IT
// -----------------------------------------------------------------------

// BAD: const on a by-value parameter
//   void printValue(const int x) { ... }
// The const provides no benefit to the caller (they can still pass
// anything), and for class types it INHIBITS move semantics.

// GOOD: by-value without const (for fundamental types)
void printValue(int x)
{
    std::cout << "Value: " << x << '\n';
}

// GOOD: pass by const reference for class types you don't modify
void printString(const std::string &s)
{
    std::cout << "String: " << s << '\n';
}

// -----------------------------------------------------------------------
// 3. const return by value - DON'T DO IT
// -----------------------------------------------------------------------

// BAD: const return by value
//   const std::string createGreeting(const std::string& name) { ... }
// This inhibits move semantics for the returned string!

// GOOD: return by value without const
std::string createGreeting(const std::string &name)
{
    return "Hello, " + name + "!";
}

// -----------------------------------------------------------------------
// 4. Move semantics interaction with const
// -----------------------------------------------------------------------
class Resource
{
    std::string m_name;
    std::vector<int> m_data;

public:
    Resource(std::string name, std::vector<int> data)
        : m_name{std::move(name)} // move: efficient
          ,
          m_data{std::move(data)} // move: efficient
    {
    }

    void print() const
    {
        std::cout << "Resource '" << m_name << "' with "
                  << m_data.size() << " elements\n";
    }
};

int main()
{
    std::cout << "=== Common Mistakes and Best Practices ===\n\n";

    // --- 1. Paired Headers -----------------------------------------------
    std::cout << "--- 1. Paired Headers ---\n";
    std::cout << "MathUtils::add(3, 4)     = " << MathUtils::add(3, 4) << '\n';
    std::vector<int> vals{10, 20, 30, 40, 50};
    std::cout << "MathUtils::average(vals) = " << MathUtils::average(vals) << '\n';
    std::cout << "Best practice: #include the paired header FIRST in your .cpp.\n";
    std::cout << "This catches declaration/definition mismatches early.\n";

    // --- 2. Never #include .cpp files ------------------------------------
    std::cout << "\n--- 2. Never #include .cpp Files ---\n";
    std::cout << "BAD:  #include \"math_utils.cpp\"  -- causes ODR violations!\n";
    std::cout << "GOOD: #include \"math_utils.h\"   and add .cpp to the project.\n";
    std::cout << "If you #include a .cpp, the definitions appear in multiple\n";
    std::cout << "translation units, violating the One Definition Rule (ODR).\n";
    std::cout << "Instead, add all .cpp files to your project/build system.\n";

    // --- 3. Don't const by-value parameters ------------------------------
    std::cout << "\n--- 3. const By-Value Parameters ---\n";
    printValue(42);
    printString("This is passed by const ref (correct).");
    std::cout << "Don't add const to by-value parameters:\n";
    std::cout << "  - For fundamental types: no benefit, just clutter.\n";
    std::cout << "  - For class types: inhibits move semantics!\n";

    // --- 4. Don't const return by value ----------------------------------
    std::cout << "\n--- 4. const Return By Value ---\n";
    std::string greeting = createGreeting("Learner"); // move can happen
    std::cout << greeting << '\n';
    std::cout << "Don't make return types const:\n";
    std::cout << "  - Prevents move semantics (forces a copy instead).\n";
    std::cout << "  - The caller's variable is their own copy anyway.\n";

    // --- 5. Move semantics with non-const parameters ---------------------
    std::cout << "\n--- 5. Move Semantics Work With Non-const ---\n";
    Resource r{"demo", {1, 2, 3, 4, 5}};
    r.print();
    std::cout << "Constructor used std::move on non-const parameters.\n";
    std::cout << "If parameters were const, move would silently fall back to copy.\n";

    // --- 6. Set the correct language standard ----------------------------
    std::cout << "\n--- 6. Language Standard ---\n";
    std::cout << "Current standard: C++" << (__cplusplus / 100 % 100) << '\n';
    std::cout << "Common values of __cplusplus:\n";
    std::cout << "  199711 = C++98/03\n";
    std::cout << "  201103 = C++11\n";
    std::cout << "  201402 = C++14\n";
    std::cout << "  201703 = C++17\n";
    std::cout << "  202002 = C++20\n";
    std::cout << "Always compile with at least -std=c++17 (or /std:c++17).\n";
    std::cout << "Many modern features (CTAD, structured bindings, etc.)\n";
    std::cout << "require C++17 or later.\n";

    // --- Summary ---------------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "1. Include your paired header first in every .cpp file.\n";
    std::cout << "2. Never #include .cpp files - add them to the build.\n";
    std::cout << "3. Don't const by-value params (inhibits move semantics).\n";
    std::cout << "4. Don't const return-by-value (inhibits move semantics).\n";
    std::cout << "5. Set your compiler to at least C++17.\n";
    std::cout << "6. Use constexpr on eligible functions proactively.\n";

    return 0;
}
