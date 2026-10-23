// Project 02: Transitive Includes
// ================================
// Appendix A.4 - Why you should never rely on transitive includes
//
// A "transitive include" happens when a header you #include itself
// #includes another header, making that second header's contents
// available to you *indirectly*.
//
// Problems:
//   - Different compilers / standard library implementations include
//     different internal headers.  Your code may compile with GCC but
//     fail with MSVC (or vice versa).
//   - A library update might reorganise its internal includes, breaking
//     your build with no warning.
//
// Best practice:
//   ALWAYS explicitly #include every header whose names you use.
//
// This program demonstrates the concept and shows how to do it right.

#include <iostream>  // for std::cout, std::endl
#include <string>    // for std::string          - EXPLICITLY included
#include <vector>    // for std::vector           - EXPLICITLY included
#include <algorithm> // for std::sort, std::find  - EXPLICITLY included
#include <numeric>   // for std::accumulate       - EXPLICITLY included

// -----------------------------------------------------------------------
// BAD EXAMPLE (commented out to prevent actual breakage)
//
// Some compilers' <iostream> transitively includes <string>.
// If you wrote this:
//
//   #include <iostream>
//   // no #include <string>  ← relying on transitive include!
//
//   int main() {
//       std::string name = "Alice";   // may compile on GCC, fail on MSVC
//   }
//
// It might compile today but break tomorrow with a compiler update.
// -----------------------------------------------------------------------

int main()
{
    std::cout << "=== Transitive Includes Demo ===\n\n";

    // --- Using std::string (we explicitly #included <string>) -------------
    std::string greeting{"Hello, learner!"};
    std::cout << "greeting: " << greeting << '\n';

    // --- Using std::vector (we explicitly #included <vector>) -------------
    std::vector<int> numbers{5, 3, 1, 4, 2};

    std::cout << "numbers (unsorted): ";
    for (int n : numbers)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- Using std::sort (we explicitly #included <algorithm>) ------------
    std::sort(numbers.begin(), numbers.end());

    std::cout << "numbers (sorted):   ";
    for (int n : numbers)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- Using std::accumulate (we explicitly #included <numeric>) --------
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "sum = " << sum << '\n';

    // --- Using std::find (also from <algorithm>) --------------------------
    auto it = std::find(numbers.begin(), numbers.end(), 3);
    if (it != numbers.end())
        std::cout << "Found 3 at index " << (it - numbers.begin()) << '\n';

    // --- Lesson summary ---------------------------------------------------
    std::cout << "\n--- Lesson ---\n";
    std::cout << "NEVER rely on transitive includes.\n";
    std::cout << "Always #include every header whose names you actually use.\n";
    std::cout << "This makes your code portable across compilers and future-proof.\n";

    return 0;
}
