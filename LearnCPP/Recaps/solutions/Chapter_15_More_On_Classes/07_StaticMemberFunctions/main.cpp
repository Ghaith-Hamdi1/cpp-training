// Chapter 15 - Project 07: Static Member Functions
// ==================================================
//
// Static member functions:
//   - Belong to the class, NOT to any object.
//   - Have NO `this` pointer.
//   - Can only access other static members (variables and functions).
//   - Called via ClassName::func() - no object required.
//
// A "pure static class" (only static members) behaves like a namespace
// with access controls, but you lose the ability to have multiple
// independent instances.
//
// C++ has NO static constructors. If you need complex initialization of
// static data, use a static helper function.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// -------------------------------------------------------
// Example 1: ID generator - static function with static state
// -------------------------------------------------------
class IDGenerator
{
private:
    static inline int s_nextId{1};

public:
    // Static member function - no object needed to call it
    static int generate()
    {
        return s_nextId++;
    }

    static void reset()
    {
        s_nextId = 1;
    }
};

// -------------------------------------------------------
// Example 2: Pure static class (math utilities)
// -------------------------------------------------------
class MathUtils
{
public:
    // Delete the constructor to prevent instantiation
    MathUtils() = delete;

    static constexpr double pi{3.14159265358979};

    static double circleArea(double radius)
    {
        return pi * radius * radius;
    }

    static double circleCircumference(double radius)
    {
        return 2.0 * pi * radius;
    }

    static int factorial(int n)
    {
        // Cannot access any non-static member - there is no `this`!
        int result{1};
        for (int i{2}; i <= n; ++i)
            result *= i;
        return result;
    }
};

// -------------------------------------------------------
// Example 3: Static function to initialize complex static data
// (Workaround for the lack of static constructors)
// -------------------------------------------------------
class WordList
{
private:
    static inline std::vector<std::string> s_words{};

    // "Static constructor" workaround - a helper that initialises data
    static std::vector<std::string> initWords()
    {
        return {"alpha", "bravo", "charlie", "delta", "echo"};
    }

    // Initialize s_words using the helper
    static inline bool s_initialized{(s_words = initWords(), true)};

public:
    WordList() = delete; // prevent instantiation

    static void print()
    {
        std::cout << "WordList:";
        for (const auto &w : s_words)
            std::cout << ' ' << w;
        std::cout << '\n';
    }

    static bool contains(const std::string &word)
    {
        return std::find(s_words.begin(), s_words.end(), word) != s_words.end();
    }
};

int main()
{
    // --- Example 1: ID generator ---
    std::cout << "--- IDGenerator ---\n";
    std::cout << "ID: " << IDGenerator::generate() << '\n'; // 1
    std::cout << "ID: " << IDGenerator::generate() << '\n'; // 2
    std::cout << "ID: " << IDGenerator::generate() << '\n'; // 3
    IDGenerator::reset();
    std::cout << "After reset: " << IDGenerator::generate() << '\n'; // 1

    // --- Example 2: Pure static class ---
    std::cout << "\n--- MathUtils ---\n";
    // Called without creating an object:
    std::cout << "Area of circle (r=5):          " << MathUtils::circleArea(5.0) << '\n';
    std::cout << "Circumference of circle (r=5): " << MathUtils::circleCircumference(5.0) << '\n';
    std::cout << "5! = " << MathUtils::factorial(5) << '\n';

    // This would NOT compile:
    // MathUtils mu;  // Constructor is deleted

    // --- Example 3: Complex static initialization ---
    std::cout << "\n--- WordList ---\n";
    WordList::print();
    std::cout << "Contains 'bravo'?  " << std::boolalpha << WordList::contains("bravo") << '\n';
    std::cout << "Contains 'foxtrot'? " << WordList::contains("foxtrot") << '\n';

    return 0;
}
