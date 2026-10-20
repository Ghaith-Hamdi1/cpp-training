// Project 03: Using Directive Pitfalls
// =====================================
// Appendix A.4 - Why `using namespace std;` is harmful
//
// `using namespace std;` pulls ALL names from namespace std into the
// current scope.  This is dangerous because:
//
//   1. The standard library contains thousands of names (count, min, max,
//      size, data, distance, swap, move, find, remove, etc.).
//   2. Future C++ standards add more names - your working code could
//      break with a compiler update.
//   3. Name collisions produce cryptic, hard-to-debug errors.
//
// Best practice:
//   - Always use the `std::` prefix explicitly.
//   - If a specific name is used frequently in a small scope, use a
//     `using` *declaration* (e.g. `using std::cout;`) instead.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// -----------------------------------------------------------------------
// Demonstration: how `using namespace std;` can cause a name collision.
// -----------------------------------------------------------------------

// Imagine you wrote your own utility function called "count":
namespace MyProject
{
    int count(const std::vector<int> &v)
    {
        // Custom logic: count only positive values
        int total{0};
        for (int n : v)
        {
            if (n > 0)
                ++total;
        }
        return total;
    }
}

// If someone writes `using namespace std;` AND `using namespace MyProject;`
// at file scope, then a bare call to `count(...)` becomes ambiguous -
// the compiler can't tell if you mean std::count or MyProject::count.
//
// Even without MyProject, names like `size`, `data`, `distance`, `min`,
// `max`, `swap`, `move`, `find`, `remove` are all in std and are common
// variable/function names in user code.

int main()
{
    std::cout << "=== Using Directive Pitfalls ===\n\n";

    std::vector<int> data{-2, 5, 0, 3, -1, 7, 4};

    // --- GOOD: Fully qualified names - always unambiguous -----------------
    std::cout << "--- Using std:: prefix (recommended) ---\n";

    auto stdCount = std::count_if(data.begin(), data.end(),
                                  [](int n)
                                  { return n > 0; });
    std::cout << "std::count_if (positive): " << stdCount << '\n';

    int myCount = MyProject::count(data);
    std::cout << "MyProject::count:         " << myCount << '\n';

    // --- ACCEPTABLE: using-declarations in a limited scope ----------------
    std::cout << "\n--- Using declaration in a limited scope ---\n";
    {
        using std::cout; // Only pulls in std::cout, nothing else
        using std::endl;
        cout << "This uses a using-declaration for cout and endl." << endl;
        cout << "Safe because the scope is small and specific." << endl;
    }

    // --- BAD: using namespace std; (simulated) ----------------------------
    // We won't actually write `using namespace std;` here, but here's
    // what would go wrong:
    //
    //   using namespace std;
    //   using namespace MyProject;
    //
    //   count(data);  // ERROR: ambiguous - std::count vs MyProject::count
    //
    // The compiler error might look like:
    //   "call to 'count' is ambiguous"

    // --- Summary ----------------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "1. Never use `using namespace std;` at file scope.\n";
    std::cout << "2. Use the std:: prefix - it's clear and safe.\n";
    std::cout << "3. If needed, use `using std::cout;` in a limited scope.\n";
    std::cout << "4. Namespace collisions cause cryptic compiler errors.\n";

    return 0;
}
