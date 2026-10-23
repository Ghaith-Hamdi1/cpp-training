// Chapter 7 - Project 08: Why Non-Const Global Variables Are Evil
// ================================================================
// Non-const global variables introduce numerous problems:
//   1. Any function can modify them → unpredictable state
//   2. Hard to debug - changes can come from anywhere
//   3. Reduce modularity - functions become coupled to global state
//   4. Static initialization order fiasco (across translation units)
//
// This project demonstrates the problems and better alternatives.

#include <iostream>
#include <string>

// -------------------------------------------------
// BAD EXAMPLE: Non-const global variables
// -------------------------------------------------
// These look convenient, but every function in the program can
// read and modify them, making the program's behavior unpredictable.
int g_errorCount{0};         // Who's changing this? Any function!
std::string g_currentUser{}; // Could be changed anywhere

// ----- Functions that silently modify global state -----

void processFile([[maybe_unused]] const std::string &filename)
{
    // Imagine this function encounters an error
    ++g_errorCount;                  // Silent side effect!
    g_currentUser = "FileProcessor"; // Overwrites without warning
    std::cout << "  processFile: modified g_errorCount and g_currentUser\n";
}

void validateData()
{
    g_errorCount += 2; // Another silent modification
    std::cout << "  validateData: modified g_errorCount\n";
}

void resetState()
{
    g_errorCount = 0; // Yet another modification from somewhere else
    g_currentUser.clear();
    std::cout << "  resetState: cleared everything\n";
}

// -------------------------------------------------
// GOOD ALTERNATIVE: Use local variables + parameters
// -------------------------------------------------
struct ProcessResult
{
    int errorCount{0};
    std::string processedBy{};
};

ProcessResult processFileBetter(const std::string &filename)
{
    ProcessResult result{};
    // Simulate work...
    if (filename.empty())
        result.errorCount = 1;

    result.processedBy = "BetterProcessor";
    return result; // Caller can inspect the result - no hidden side effects
}

// -------------------------------------------------
// GOOD ALTERNATIVE: Encapsulate in a class
// -------------------------------------------------
class ErrorTracker
{
private:
    int m_count{0};

public:
    void record() { ++m_count; }
    void reset() { m_count = 0; }
    int count() const { return m_count; }
};

int main()
{
    // -------------------------------------------------
    // 1. Problem: unpredictable state
    // -------------------------------------------------
    std::cout << "1. PROBLEM - Unpredictable global state:\n";
    std::cout << "   Initial g_errorCount = " << g_errorCount << '\n';

    processFile("data.txt");
    validateData();
    std::cout << "   After two functions: g_errorCount = " << g_errorCount << '\n';
    std::cout << "   g_currentUser = \"" << g_currentUser << "\"\n";
    // Who set errorCount to 3? Which function? Hard to tell without reading all code.

    resetState();
    std::cout << "   After reset: g_errorCount = " << g_errorCount << '\n';

    // -------------------------------------------------
    // 2. Problem: hard to debug
    // -------------------------------------------------
    std::cout << "\n2. PROBLEM - Hard to debug:\n";
    std::cout << "   When g_errorCount is wrong, you must check EVERY function\n";
    std::cout << "   in the entire program to find who modified it.\n";

    // -------------------------------------------------
    // 3. Problem: reduced modularity
    // -------------------------------------------------
    std::cout << "\n3. PROBLEM - Reduced modularity:\n";
    std::cout << "   processFile() depends on g_errorCount and g_currentUser.\n";
    std::cout << "   You can't reuse it in another program without those globals.\n";

    // -------------------------------------------------
    // 4. Problem: static initialization order fiasco
    // -------------------------------------------------
    std::cout << "\n4. PROBLEM - Static initialization order fiasco:\n";
    std::cout << "   If global A (in file1.cpp) depends on global B (in file2.cpp),\n";
    std::cout << "   the initialization order is UNDEFINED across files.\n";
    std::cout << "   A might be initialized before B exists → undefined behavior!\n";

    // -------------------------------------------------
    // 5. Better alternative: return values + parameters
    // -------------------------------------------------
    std::cout << "\n5. BETTER - Use return values and parameters:\n";
    ProcessResult result{processFileBetter("data.txt")};
    std::cout << "   Errors: " << result.errorCount
              << ", Processed by: " << result.processedBy << '\n';

    // -------------------------------------------------
    // 6. Better alternative: encapsulate state
    // -------------------------------------------------
    std::cout << "\n6. BETTER - Encapsulate state in a class:\n";
    ErrorTracker tracker{};
    tracker.record();
    tracker.record();
    tracker.record();
    std::cout << "   Tracked errors: " << tracker.count() << '\n';
    tracker.reset();
    std::cout << "   After reset:    " << tracker.count() << '\n';

    // -------------------------------------------------
    // 7. When globals ARE acceptable
    // -------------------------------------------------
    std::cout << "\n7. Acceptable uses of globals:\n";
    std::cout << "   - const/constexpr globals (they can't be changed)\n";
    std::cout << "   - std::cout, std::cin (well-defined global objects)\n";
    std::cout << "   - Truly program-wide config that never changes after init\n";

    return 0;
}
