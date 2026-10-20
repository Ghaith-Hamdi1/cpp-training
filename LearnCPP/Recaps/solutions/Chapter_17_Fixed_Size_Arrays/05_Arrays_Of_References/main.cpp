// Chapter 17 - Project 05: Arrays of References via std::reference_wrapper
// Topics: std::reference_wrapper, std::ref(), std::cref(), .get()
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <functional> // std::reference_wrapper, std::ref, std::cref
#include <iostream>

int main()
{
    // -----------------------------------------------------------------------
    // Problem: You CANNOT create an array of references directly.
    //   std::array<int&, 3> bad;  // ERROR - references are not objects
    //
    // Solution: Use std::reference_wrapper<T> from <functional>.
    //   It acts like a reference but is an object that can be stored in arrays.
    // -----------------------------------------------------------------------

    int a{10};
    int b{20};
    int c{30};

    // -----------------------------------------------------------------------
    // 1. Creating an array of reference_wrappers manually
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Manual reference_wrapper ---\n";

    std::array<std::reference_wrapper<int>, 3> refs{
        std::reference_wrapper<int>{a},
        std::reference_wrapper<int>{b},
        std::reference_wrapper<int>{c}};

    for (const auto &r : refs)
        std::cout << r.get() << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 2. Using std::ref() - convenience function (less verbose)
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. std::ref() shorthand ---\n";

    auto refs2 = std::array{std::ref(a), std::ref(b), std::ref(c)};
    // CTAD deduces std::array<std::reference_wrapper<int>, 3>

    for (const auto &r : refs2)
        std::cout << r.get() << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 3. Modifying the original variable through the wrapper
    //    Use .get() to access and modify the referenced value.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. Modify through wrapper ---\n";

    refs2[0].get() = 999; // changes 'a' to 999
    std::cout << "a is now: " << a << '\n';

    // -----------------------------------------------------------------------
    // 4. std::cref() - creates a const reference wrapper (read-only)
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. std::cref() (read-only) ---\n";

    auto constRefs = std::array{std::cref(a), std::cref(b), std::cref(c)};
    // constRefs[0].get() = 42;  // ERROR - const reference, cannot modify

    for (const auto &r : constRefs)
        std::cout << r.get() << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 5. Practical use: iterating over a set of named variables
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Doubling named variables via ref array ---\n";

    int x{1}, y{2}, z{3};
    for (auto r : std::array{std::ref(x), std::ref(y), std::ref(z)})
        r.get() *= 2;

    std::cout << "x=" << x << " y=" << y << " z=" << z << '\n';
    // Output: x=2 y=4 z=6

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   Use std::reference_wrapper (or std::ref/std::cref) to create
    //   arrays that refer to existing variables without copies.
    //   Use .get() to access or modify the referenced value.
    // -----------------------------------------------------------------------

    return 0;
}
