// Chapter 16 - Project 05: Passing std::vector to Functions
// ==========================================================
// Demonstrates:
//   - Pass by const reference (avoid expensive copies)
//   - Function templates accepting vectors of any element type
//   - C++20 abbreviated function templates with const auto&
//
// Key rule: ALWAYS pass std::vector by const reference
// unless you intentionally need a copy.
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <string>

// --- 1. Pass by const reference - the correct way ---
// The vector is NOT copied; the function gets a read-only reference.
void printScores(const std::vector<int> &scores)
{
    std::cout << "Scores: ";
    for (const auto &s : scores)
        std::cout << s << ' ';
    std::cout << '\n';
}

// --- 2. Pass by value - BAD! Makes an expensive copy ---
// Shown here only to illustrate the pitfall. DO NOT do this in real code.
void printScoresBadCopy(std::vector<int> scores) // copies the entire vector!
{
    std::cout << "Scores (copied): ";
    for (const auto &s : scores)
        std::cout << s << ' ';
    std::cout << '\n';
}

// --- 3. Function template - accepts vector of any element type ---
template <typename T>
void printVector(const std::vector<T> &v)
{
    std::cout << "[ ";
    for (const auto &elem : v)
        std::cout << elem << ' ';
    std::cout << "]\n";
}

// --- 4. C++20 abbreviated function template using const auto& ---
// This accepts ANY type, not just vectors. Use when flexibility is desired.
void printAnything(const auto &container)
{
    std::cout << "{ ";
    for (const auto &elem : container)
        std::cout << elem << ' ';
    std::cout << "}\n";
}

// --- 5. Non-const reference when modification is needed ---
void doubleAllElements(std::vector<int> &v)
{
    for (auto &elem : v)
        elem *= 2;
}

int main()
{
    std::vector<int> grades{85, 92, 78, 95};
    std::vector<std::string> names{"Alice", "Bob", "Charlie"};

    // Using the const reference version (correct)
    std::cout << "=== Pass by const reference ===\n";
    printScores(grades);

    // Using the template version (works with any element type)
    std::cout << "\n=== Function template ===\n";
    std::cout << "Ints:    ";
    printVector(grades);
    std::cout << "Strings: ";
    printVector(names);

    // Using the C++20 abbreviated template
    std::cout << "\n=== C++20 auto& (abbreviated template) ===\n";
    std::cout << "Grades:  ";
    printAnything(grades);
    std::cout << "Names:   ";
    printAnything(names);

    // Modification through non-const reference
    std::cout << "\n=== Modifying via non-const reference ===\n";
    std::cout << "Before:  ";
    printVector(grades);
    doubleAllElements(grades);
    std::cout << "After:   ";
    printVector(grades);

    return 0;
}
