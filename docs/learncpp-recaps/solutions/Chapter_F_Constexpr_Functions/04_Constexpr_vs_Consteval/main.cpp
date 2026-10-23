// ============================================================================
// Project 04 - constexpr vs consteval - Side-by-Side Comparison
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT:
//   constexpr  →  "CAN be evaluated at compile-time."
//                  Also callable at runtime with non-constant arguments.
//
//   consteval  →  "MUST be evaluated at compile-time."  (C++20)
//                  Calling with non-constant arguments is a compile error.
//
//   Both are implicitly inline.
//   Both require their body to be visible at the point of call for
//   compile-time evaluation.
//
//   Rule of thumb:
//     • Use constexpr when the function should work at both compile-time
//       and runtime.
//     • Use consteval when a runtime call is always a mistake.
// ============================================================================

#include <iostream>

// ---------------------------------------------------------------------------
// constexpr version: may run at compile-time or runtime.
// ---------------------------------------------------------------------------
constexpr int add_constexpr(int a, int b)
{
    return a + b;
}

// ---------------------------------------------------------------------------
// consteval version: must run at compile-time.
// ---------------------------------------------------------------------------
consteval int add_consteval(int a, int b)
{
    return a + b;
}

// ---------------------------------------------------------------------------
// A consteval helper that *forces* compile-time evaluation of any
// constexpr function.  This is the "consteval wrapper" idiom.
// ---------------------------------------------------------------------------
consteval int forceCompileTime(int value)
{
    return value; // value must already be a constant expression
}

int main()
{
    // =======================================================================
    // 1) Both work with constant arguments
    // =======================================================================
    constexpr int r1{add_constexpr(2, 3)}; // compile-time ✓
    constexpr int r2{add_consteval(2, 3)}; // compile-time ✓
    std::cout << "add_constexpr(2,3) = " << r1 << '\n';
    std::cout << "add_consteval(2,3) = " << r2 << '\n';

    // =======================================================================
    // 2) Only constexpr can be called with runtime arguments
    // =======================================================================
    int a{};
    std::cout << "\nEnter first number:  ";
    std::cin >> a;
    int b{};
    std::cout << "Enter second number: ";
    std::cin >> b;

    int runtimeSum{add_constexpr(a, b)}; // OK - runtime call
    std::cout << "add_constexpr(" << a << ',' << b << ") = "
              << runtimeSum << "  [runtime]\n";

    // int bad{ add_consteval(a, b) };           // ERROR - won't compile!
    // Uncomment the line above to see the error.

    // =======================================================================
    // 3) Forcing compile-time evaluation with the consteval wrapper
    // =======================================================================
    // add_constexpr(10, 20) is not guaranteed compile-time when assigned
    // to a plain int.  Wrapping it in forceCompileTime() guarantees it.
    int forced{forceCompileTime(add_constexpr(10, 20))};
    std::cout << "\nforceCompileTime(add_constexpr(10,20)) = " << forced
              << "  [forced compile-time]\n";

    // =======================================================================
    // Summary table
    // =======================================================================
    std::cout << "\n--- Summary ---\n"
              << "                    constexpr    consteval\n"
              << "Compile-time args:    YES           YES\n"
              << "Runtime args:         YES           NO (error)\n"
              << "Implicitly inline:    YES           YES\n"
              << "Guaranteed CT:     only in req'd   ALWAYS\n";

    return 0;
}
