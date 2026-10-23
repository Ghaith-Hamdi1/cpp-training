// Chapter 20 - Project 05: Recursion and Memoization
// ===================================================
// Demonstrates: recursive functions, base cases, and memoization.
//
// Key points:
//   - A recursive function calls itself and MUST have a base case (termination
//     condition) or it will cause infinite recursion → stack overflow.
//   - Recursion solves a problem by reducing it to smaller sub-problems.
//   - Memoization caches previously computed results to avoid redundant work.
//   - Pitfall: using --n instead of n-1 can cause undefined behavior if n
//     is used again in the same expression.
//   - Rule of thumb: prefer iteration unless recursion is significantly simpler.

#include <iostream>
#include <unordered_map>

// -------------------------------------------------------
// 1. Factorial - classic recursion
// -------------------------------------------------------
int factorial(int n)
{
    // Base case
    if (n <= 1)
        return 1;

    // Recursive step: n! = n * (n-1)!
    // Note: we use (n - 1), NOT (--n), to avoid side-effect pitfalls.
    return n * factorial(n - 1);
}

// -------------------------------------------------------
// 2. Fibonacci - naive recursion (exponential time)
// -------------------------------------------------------
long long fibNaive(int n)
{
    if (n <= 1)
        return n;                             // base cases: fib(0)=0, fib(1)=1
    return fibNaive(n - 1) + fibNaive(n - 2); // two recursive calls per invocation
}

// -------------------------------------------------------
// 3. Fibonacci - with memoization (linear time)
// -------------------------------------------------------
long long fibMemo(int n, std::unordered_map<int, long long> &cache)
{
    // Check if already computed
    if (auto it = cache.find(n); it != cache.end())
        return it->second;

    // Base cases
    if (n <= 1)
        return n;

    // Compute, cache, and return
    long long result = fibMemo(n - 1, cache) + fibMemo(n - 2, cache);
    cache[n] = result;
    return result;
}

// Convenience wrapper
long long fibMemo(int n)
{
    std::unordered_map<int, long long> cache;
    return fibMemo(n, cache);
}

// -------------------------------------------------------
// 4. Sum of digits - another recursive example
// -------------------------------------------------------
int sumOfDigits(int n)
{
    n = (n < 0) ? -n : n; // handle negative numbers
    if (n < 10)
        return n; // base case: single digit
    return (n % 10) + sumOfDigits(n / 10);
}

int main()
{
    // Factorial
    std::cout << "=== Factorial ===\n";
    for (int i{0}; i <= 10; ++i)
        std::cout << i << "! = " << factorial(i) << '\n';

    // Fibonacci - naive (only small n - it's very slow for large n)
    std::cout << "\n=== Fibonacci (naive, n=20) ===\n";
    for (int i{0}; i <= 20; ++i)
        std::cout << "fib(" << i << ") = " << fibNaive(i) << '\n';

    // Fibonacci - memoized (handles large n easily)
    std::cout << "\n=== Fibonacci (memoized, n=45) ===\n";
    for (int i : {10, 20, 30, 40, 45})
        std::cout << "fib(" << i << ") = " << fibMemo(i) << '\n';

    // Sum of digits
    std::cout << "\n=== Sum of digits ===\n";
    for (int val : {0, 7, 123, 9999, -456})
        std::cout << "sumOfDigits(" << val << ") = " << sumOfDigits(val) << '\n';

    return 0;
}
