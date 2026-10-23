// Chapter 3 - Project 10: Prevention and Best Practices
// =======================================================
//
// KEY CONCEPT:
//   The best debugging is the debugging you never have to do.
//   Prevent bugs by following these practices:
//
//   1. KEEP FUNCTIONS SHORT - ideally under ~10 lines. Short functions
//      are easier to understand, test, and debug. If a function is too
//      long, refactor it into smaller helper functions.
//
//   2. REFACTOR - restructure code without changing behavior to improve
//      readability. Make structural changes separately from behavioral
//      changes, and retest after each.
//
//   3. PREFER THE STANDARD LIBRARY - std::sort, std::find, etc. are
//      well-tested. Don't reinvent the wheel.
//
//   4. DEFENSIVE PROGRAMMING - anticipate how your code might be misused
//      and handle those cases explicitly.
//
//   5. USE STATIC ANALYSIS - tools like clang-tidy and cppcheck analyze
//      your code without running it, catching bugs the compiler misses.
//
//   6. DON'T CODE WHILE FATIGUED - tired programmers write more bugs.
//
// This program demonstrates refactoring a long function into short,
// focused helpers, plus basic defensive programming.

#include <iostream>
#include <string>
#include <limits>

// ========== BAD: One long function doing everything ==========
// This is hard to debug because a bug could be anywhere in 30+ lines.
void processStudentGradeBad()
{
    std::string name{};
    int score{};
    // Imagine 50 more lines: prompt, validate, compute grade, print report,
    // save to file, send email... all in one giant function.
    // If something goes wrong, good luck finding the bug!
    std::cout << "(This bad version is not called - see the refactored one below)\n";
}

// ========== GOOD: Short, focused functions ==========

// Each function does ONE thing and is easy to understand and test.

std::string getStudentName()
{
    std::cout << "Enter student name: ";
    std::string name{};
    std::getline(std::cin, name);
    return name;
}

int getScore()
{
    std::cout << "Enter score (0-100): ";
    int score{};
    std::cin >> score;

    // DEFENSIVE PROGRAMMING: validate input at system boundaries.
    // Clamp the score to a valid range instead of allowing garbage values.
    if (score < 0)
    {
        std::cerr << "[WARNING] Negative score clamped to 0\n";
        score = 0;
    }
    else if (score > 100)
    {
        std::cerr << "[WARNING] Score > 100 clamped to 100\n";
        score = 100;
    }

    // Clear the input buffer after reading an int
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return score;
}

char computeGrade(int score)
{
    // Short and obvious - easy to verify correctness.
    if (score >= 90)
        return 'A';
    if (score >= 80)
        return 'B';
    if (score >= 70)
        return 'C';
    if (score >= 60)
        return 'D';
    return 'F';
}

void printReport(const std::string &name, int score, char grade)
{
    std::cout << "\n=== Student Report ===\n";
    std::cout << "Name:  " << name << '\n';
    std::cout << "Score: " << score << '\n';
    std::cout << "Grade: " << grade << '\n';
}

int main()
{
    std::cout << "=== Prevention and Best Practices Demo ===\n\n";

    // Each step is a separate, testable function.
    // If the grade is wrong, you test computeGrade() in isolation.
    // If the name is missing, you test getStudentName() in isolation.
    std::string name{getStudentName()};
    int score{getScore()};
    char grade{computeGrade(score)};
    printReport(name, score, grade);

    // STATIC ANALYSIS TIPS:
    // Run these tools on your code to catch issues early:
    //   clang-tidy main.cpp -- -std=c++20
    //   cppcheck --std=c++20 main.cpp
    //
    // They can catch: uninitialized variables, dead code, potential
    // null dereferences, integer overflow risks, and more.

    // REFACTORING RULE:
    // Make structural changes (splitting functions, renaming variables)
    // SEPARATELY from behavioral changes (fixing bugs, adding features).
    // Test after each type of change. This way, if a test breaks, you
    // know exactly which change caused it.

    return 0;
}
