// Chapter 18 - Project 6: std::find, std::find_if, std::count, std::count_if
// =============================================================================
// The <algorithm> header provides search and counting functions:
//
//   std::find(begin, end, value)      - returns iterator to first match, or end()
//   std::find_if(begin, end, pred)    - returns iterator to first element where pred is true
//   std::count(begin, end, value)     - returns number of elements equal to value
//   std::count_if(begin, end, pred)   - returns number of elements where pred is true
//
// All of these are "inspectors" - they don't modify the container.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// A simple struct to demonstrate find_if with objects
struct Student
{
    std::string name{};
    int grade{};
};

int main()
{
    // --- 1) std::find - search by value ---
    std::cout << "=== std::find ===\n";

    std::vector<int> nums{10, 20, 30, 40, 50};

    auto result{std::find(nums.begin(), nums.end(), 30)};
    if (result != nums.end())
        std::cout << "Found 30 at index " << (result - nums.begin()) << '\n';
    else
        std::cout << "30 not found\n";

    // Search for a value that doesn't exist
    result = std::find(nums.begin(), nums.end(), 99);
    if (result != nums.end())
        std::cout << "Found 99\n";
    else
        std::cout << "99 not found (returns end())\n";

    // --- 2) std::find_if - search by predicate ---
    std::cout << "\n=== std::find_if ===\n";

    // Find the first even number
    auto even{std::find_if(nums.begin(), nums.end(),
                           [](int n)
                           { return n % 2 == 0; })};

    if (even != nums.end())
        std::cout << "First even number: " << *even << '\n';

    // Find first number greater than 35
    auto gt35{std::find_if(nums.begin(), nums.end(),
                           [](int n)
                           { return n > 35; })};

    if (gt35 != nums.end())
        std::cout << "First number > 35: " << *gt35 << '\n';

    // --- 3) std::find_if with custom objects ---
    std::cout << "\n=== std::find_if with structs ===\n";

    std::vector<Student> students{
        {"Alice", 92},
        {"Bob", 85},
        {"Charlie", 97},
        {"Diana", 88},
    };

    auto honor{std::find_if(students.begin(), students.end(),
                            [](const Student &s)
                            { return s.grade >= 95; })};

    if (honor != students.end())
        std::cout << "First honor student: " << honor->name
                  << " (grade " << honor->grade << ")\n";

    // --- 4) std::count - count matching values ---
    std::cout << "\n=== std::count ===\n";

    std::vector<int> data{1, 2, 3, 2, 4, 2, 5, 2, 6};

    auto twos{std::count(data.begin(), data.end(), 2)};
    std::cout << "Number of 2s: " << twos << '\n';

    auto sevens{std::count(data.begin(), data.end(), 7)};
    std::cout << "Number of 7s: " << sevens << '\n';

    // --- 5) std::count_if - count by predicate ---
    std::cout << "\n=== std::count_if ===\n";

    auto evenCount{std::count_if(data.begin(), data.end(),
                                 [](int n)
                                 { return n % 2 == 0; })};
    std::cout << "Even numbers: " << evenCount << '\n';

    auto aboveAvg{std::count_if(students.begin(), students.end(),
                                [](const Student &s)
                                { return s.grade > 90; })};
    std::cout << "Students with grade > 90: " << aboveAvg << '\n';

    return 0;
}
