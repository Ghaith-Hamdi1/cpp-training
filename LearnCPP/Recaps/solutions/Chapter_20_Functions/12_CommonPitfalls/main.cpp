// Chapter 20 - Project 12: Common Pitfalls
// ==========================================
// Demonstrates: frequent mistakes with function pointers, recursion,
// command-line arguments, ellipsis, and lambdas - and how to avoid them.
//
// Each section shows the WRONG way (commented out or explained)
// and the CORRECT way.

#include <functional>
#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------
// Helper functions used across examples
// -------------------------------------------------------
int square(int n) { return n * n; }
int cube(int n) { return n * n * n; }

int main()
{
    std::cout << "=== PITFALL 1: Forgetting parentheses ===\n";
    // WRONG:   auto result = square;   // This captures the function's ADDRESS, not the result
    // RIGHT:   auto result = square(5);
    auto result = square(5);
    std::cout << "square(5) = " << result << '\n';
    // 'square' without () is a function pointer, not an invocation.

    std::cout << "\n=== PITFALL 2: Mismatching function pointer types ===\n";
    // The pointer type must EXACTLY match the target function's signature.
    int (*goodPtr)(int) = &square; // OK: int(int) matches int(int)
    // double (*badPtr)(int) = &square;  // ERROR: return type mismatch
    std::cout << "goodPtr(4) = " << goodPtr(4) << '\n';

    std::cout << "\n=== PITFALL 3: Null function pointer ===\n";
    int (*nullPtr)(int) = nullptr;
    // WRONG:   nullPtr(5);  // Crash! Undefined behavior
    // RIGHT:   check before calling
    if (nullPtr)
        std::cout << "nullPtr(5) = " << nullPtr(5) << '\n';
    else
        std::cout << "nullPtr is null - safe check prevented a crash\n";

    std::cout << "\n=== PITFALL 4: --n vs n-1 in recursion ===\n";
    // WRONG recursive call (potential UB):
    //   return n * factorial(--n);   // --n modifies n AND n is used elsewhere
    // RIGHT:
    //   return n * factorial(n - 1); // no side effects on n
    // Demonstration of correct approach:
    auto factorial = [](auto self, int n) -> int
    {
        if (n <= 1)
            return 1;
        return n * self(self, n - 1); // CORRECT: n - 1, no --n
    };
    std::cout << "5! = " << factorial(factorial, 5) << '\n';

    std::cout << "\n=== PITFALL 5: Missing base case in recursion ===\n";
    // WRONG:
    //   int countDown(int n) { return countDown(n - 1); }  // no base case → stack overflow
    // RIGHT: always have a termination condition
    auto countDown = [](auto self, int n) -> void
    {
        if (n <= 0) // BASE CASE
        {
            std::cout << "Done!\n";
            return;
        }
        std::cout << n << ' ';
        self(self, n - 1);
    };
    countDown(countDown, 5);

    std::cout << "\n=== PITFALL 6: Expecting lambda capture-by-value to modify outer variable ===\n";
    int counter{0};
    auto inc = [counter]() mutable
    {
        ++counter; // modifies the lambda's COPY, NOT the original
        return counter;
    };
    inc();
    inc();
    inc();
    std::cout << "Lambda's counter after 3 calls: " << inc() << '\n'; // 4
    std::cout << "Original counter: " << counter << " (still 0!)\n";

    std::cout << "\n=== PITFALL 7: Dangling reference capture ===\n";
    // WRONG (lambda outlives the variable):
    //   std::function<int()> bad;
    //   {
    //       int local{ 42 };
    //       bad = [&local]() { return local; };  // dangling!
    //   }
    //   bad();  // UB: local is already destroyed

    // RIGHT: capture by value if the lambda may outlive the variable
    std::function<int()> good;
    {
        int local{42};
        good = [local]()
        { return local; }; // safe: own copy
    }
    std::cout << "Safe captured value: " << good() << '\n';

    std::cout << "\n=== PITFALL 8: Copies of mutable lambdas have independent state ===\n";
    int n{0};
    auto gen = [n]() mutable
    { return ++n; };
    auto genCopy = gen; // copy has its OWN counter starting from 0

    std::cout << "gen():     " << gen() << '\n';     // 1
    std::cout << "gen():     " << gen() << '\n';     // 2
    std::cout << "genCopy(): " << genCopy() << '\n'; // 1 (independent!)
    std::cout << "genCopy(): " << genCopy() << '\n'; // 2

    // Use std::ref to share state:
    std::function<int()> shared{std::ref(gen)};
    std::cout << "gen():     " << gen() << '\n';    // 3
    std::cout << "shared():  " << shared() << '\n'; // 4 (same object via std::ref)

    std::cout << "\n=== PITFALL 9: Forgetting to convert argv strings to numbers ===\n";
    // argv entries are ALWAYS C-style strings.
    // WRONG:   int num = argv[1];        // type mismatch
    // RIGHT:   use std::stringstream, std::stoi, etc.
    // (See Project 06 for a full working example.)
    std::cout << "Always use std::stoi / std::stringstream to convert argv values.\n";

    std::cout << "\nAll pitfalls demonstrated safely. Review the comments for details.\n";

    return 0;
}
