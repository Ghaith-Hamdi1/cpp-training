// Project 06: constexpr Best Practices
// ======================================
// Appendix A.4 - Using constexpr proactively
//
// `constexpr` tells the compiler that a function/variable CAN be
// evaluated at compile time.  Benefits:
//   - Smaller, faster code (values computed during compilation)
//   - Errors caught at compile time (e.g. static_assert on results)
//   - No runtime cost for eligible computations
//
// Best practice: mark functions constexpr even if they're only called
// at runtime today.  It's low-cost and future-proofs your code.  If
// someone later uses the function in a compile-time context, it will
// just work.
//
// In C++20, consteval forces compile-time-only evaluation, and
// constinit ensures a variable is initialised at compile time.

#include <iostream>
#include <array>
#include <cstddef> // std::size_t

// -----------------------------------------------------------------------
// constexpr function: can be evaluated at compile time OR runtime
// -----------------------------------------------------------------------
constexpr int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

// -----------------------------------------------------------------------
// constexpr function with more complex logic
// -----------------------------------------------------------------------
constexpr int fibonacci(int n)
{
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;

    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i)
    {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// -----------------------------------------------------------------------
// constexpr function returning a bool - useful for static_assert
// -----------------------------------------------------------------------
constexpr bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

// -----------------------------------------------------------------------
// consteval (C++20): MUST be evaluated at compile time
// -----------------------------------------------------------------------
consteval int compileTimeSquare(int n)
{
    return n * n;
}

// -----------------------------------------------------------------------
// Compile-time validation with static_assert
// -----------------------------------------------------------------------
static_assert(factorial(5) == 120, "5! should be 120");
static_assert(fibonacci(10) == 55, "fib(10) should be 55");
static_assert(isPrime(17), "17 should be prime");
static_assert(!isPrime(15), "15 should not be prime");

int main()
{
    std::cout << "=== constexpr Best Practices ===\n\n";

    // --- Compile-time usage -----------------------------------------------
    std::cout << "--- Compile-Time Evaluation ---\n";

    // constexpr variable: value computed at compile time
    constexpr int fact5 = factorial(5);
    std::cout << "factorial(5)  = " << fact5 << "  (computed at compile time)\n";

    constexpr int fib10 = fibonacci(10);
    std::cout << "fibonacci(10) = " << fib10 << "  (computed at compile time)\n";

    // consteval: always compile time
    constexpr int sq7 = compileTimeSquare(7);
    std::cout << "square(7)     = " << sq7 << "  (consteval - always compile time)\n";

    // --- Using constexpr to size an array at compile time -----------------
    constexpr std::size_t arraySize = factorial(4); // 24
    std::array<int, arraySize> bigArray{};
    std::cout << "Array sized by factorial(4) = " << bigArray.size() << " elements\n";

    // --- Runtime usage (constexpr functions work at runtime too) -----------
    std::cout << "\n--- Runtime Evaluation ---\n";

    int n{};
    std::cout << "Enter a number (1-12) for factorial: ";
    std::cin >> n;

    if (n >= 1 && n <= 12)
    {
        // Called at runtime - same function, no problem
        std::cout << "factorial(" << n << ") = " << factorial(n) << '\n';
    }
    else
    {
        std::cout << "Out of range for int factorial.\n";
    }

    // --- constexpr with conditions ----------------------------------------
    std::cout << "\n--- Prime Check (constexpr) ---\n";
    constexpr int testPrimes[] = {2, 3, 4, 7, 10, 13, 17, 20, 23};
    for (int p : testPrimes)
    {
        std::cout << p << " is " << (isPrime(p) ? "prime" : "not prime") << '\n';
    }

    // --- Summary ----------------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "constexpr:  function CAN be evaluated at compile time.\n";
    std::cout << "consteval:  function MUST be evaluated at compile time (C++20).\n";
    std::cout << "constinit:  variable MUST be initialised at compile time (C++20).\n";
    std::cout << "Best practice: use constexpr on eligible functions proactively.\n";
    std::cout << "It's low-cost and future-proofs your code.\n";

    return 0;
}
