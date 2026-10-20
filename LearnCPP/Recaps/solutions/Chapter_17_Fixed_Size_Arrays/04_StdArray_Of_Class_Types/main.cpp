// Chapter 17 - Project 04: std::array of Class Types and Brace Elision
// Topics: double-brace init for structs, brace elision rules
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <iostream>
#include <string_view>

// A simple aggregate (struct with public members, no user-declared constructors)
struct Point
{
    int x{};
    int y{};
};

struct Student
{
    std::string_view name{};
    int grade{};
};

int main()
{
    // -----------------------------------------------------------------------
    // 1. std::array of scalars - single braces work fine
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Scalars (single braces) ---\n";
    std::array<int, 3> nums{1, 2, 3};
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 2. std::array of structs - DOUBLE BRACES are required
    //
    //    std::array internally contains a C-style array member:
    //        T __elems[N];
    //    So when you write  std::array<Point, 2>{ ... }
    //    the outer {} initializes the std::array aggregate,
    //    and you need inner {} for the internal C-style array.
    //
    //    PITFALL: using single braces may compile but initialize incorrectly,
    //    or may fail to compile depending on the struct.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. Structs - double braces ---\n";

    // Correct: double braces
    std::array<Point, 3> points{{{1, 2},
                                 {3, 4},
                                 {5, 6}}};

    for (const auto &p : points)
        std::cout << '(' << p.x << ", " << p.y << ") ";
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 3. Using explicit type per element - single braces work (brace elision)
    //    When each element names its type, the compiler can elide inner braces.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. Named type per element (brace elision) ---\n";

    std::array<Student, 2> students{
        Student{"Alice", 95},
        Student{"Bob", 88}};

    for (const auto &s : students)
        std::cout << s.name << ": " << s.grade << '\n';

    // -----------------------------------------------------------------------
    // 4. CTAD with structs - deduction works with double braces
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. CTAD with structs ---\n";

    // CTAD deduces std::array<Point, 2> from the initializers
    std::array morePoints{
        Point{10, 20},
        Point{30, 40}};

    for (const auto &p : morePoints)
        std::cout << '(' << p.x << ", " << p.y << ") ";
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 5. constexpr array of structs
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. constexpr array of structs ---\n";

    constexpr std::array<Point, 2> cpoints{{{100, 200},
                                            {300, 400}}};

    static_assert(cpoints[0].x == 100);
    static_assert(cpoints[1].y == 400);

    for (const auto &p : cpoints)
        std::cout << '(' << p.x << ", " << p.y << ") ";
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   When initializing std::array of structs/classes without naming
    //   the type for each element, use DOUBLE BRACES {{ ... }}.
    //   Single braces work when each element explicitly names its type,
    //   or when elements are scalars.
    // -----------------------------------------------------------------------

    return 0;
}
