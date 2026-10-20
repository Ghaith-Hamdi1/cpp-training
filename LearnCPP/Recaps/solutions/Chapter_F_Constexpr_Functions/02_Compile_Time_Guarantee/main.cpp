// ============================================================================
// Project 02 - Compile-Time Guarantee
// Chapter F: Constexpr Functions
// ============================================================================
//
// KEY CONCEPT:
//   Compile-time evaluation of a constexpr function is GUARANTEED only when
//   the call appears in a context that REQUIRES a constant expression:
//
//     1. Initializing a constexpr variable
//     2. A template non-type argument
//     3. A static_assert expression
//     4. Array size (in a constexpr context)
//     5. Case label in a switch
//
//   Outside these contexts the compiler MAY still optimize the call to
//   compile-time, but there is NO guarantee.
// ============================================================================

#include <iostream>

constexpr int factorial(int n)
{
    int result{1};
    for (int i{2}; i <= n; ++i)
        result *= i;
    return result;
}

// A template that uses a non-type parameter - requires a constant expression.
template <int N>
void printValue()
{
    std::cout << "Template non-type parameter N = " << N << '\n';
}

int main()
{
    // -----------------------------------------------------------------------
    // GUARANTEED compile-time: constexpr variable initialization
    // -----------------------------------------------------------------------
    constexpr int f5{factorial(5)}; // MUST be compile-time
    std::cout << "factorial(5)  = " << f5 << "  [guaranteed compile-time]\n";

    // -----------------------------------------------------------------------
    // GUARANTEED compile-time: template non-type argument
    // -----------------------------------------------------------------------
    printValue<factorial(6)>(); // MUST be compile-time

    // -----------------------------------------------------------------------
    // GUARANTEED compile-time: static_assert
    // -----------------------------------------------------------------------
    static_assert(factorial(4) == 24); // MUST be compile-time

    // -----------------------------------------------------------------------
    // GUARANTEED compile-time: constexpr array size
    // -----------------------------------------------------------------------
    constexpr int size{factorial(3)}; // 6
    int arr[size]{};                  // array of 6 elements
    std::cout << "Array size   = " << size << "  [guaranteed compile-time]\n";

    // -----------------------------------------------------------------------
    // NOT guaranteed: initializing a plain (non-constexpr) variable
    // The compiler may or may not evaluate at compile-time.
    // -----------------------------------------------------------------------
    int runtimeResult{factorial(7)}; // may be compile-time, may not
    std::cout << "factorial(7)  = " << runtimeResult
              << "  [NOT guaranteed compile-time]\n";

    // -----------------------------------------------------------------------
    // NOT guaranteed: constexpr function called with a non-const argument
    // The function degrades to a normal runtime call.
    // -----------------------------------------------------------------------
    int n{};
    std::cout << "\nEnter a number (1-10): ";
    std::cin >> n;
    int userFact{factorial(n)}; // definitely runtime
    std::cout << "factorial(" << n << ") = " << userFact << "  [runtime]\n";

    return 0;
}
