// Chapter 8 - Project 12: Halts (Exiting Your Program Early)
// Demonstrates std::exit(), std::atexit(), and std::abort().
// Compile: g++ -std=c++20 -o main main.cpp

#include <cstdlib> // std::exit, std::abort, std::atexit
#include <iostream>

// -------------------------------------------------------
// Cleanup function registered with std::atexit()
// -------------------------------------------------------
void cleanup()
{
    std::cout << "[atexit] Cleanup function called.\n";
}

void anotherCleanup()
{
    std::cout << "[atexit] Another cleanup function called.\n";
}

int main()
{
    // -------------------------------------------------------
    // 1. std::atexit() - register cleanup functions
    // -------------------------------------------------------
    // Functions are called in REVERSE order of registration
    // when the program exits normally (via return or std::exit).
    std::atexit(cleanup);
    std::atexit(anotherCleanup);

    std::cout << "=== Halts Demo ===\n\n";

    // -------------------------------------------------------
    // 2. Normal exit via return (preferred)
    // -------------------------------------------------------
    // return 0 from main is the best way to end a program.
    // It destroys local variables, calls atexit functions,
    // and flushes I/O.

    // -------------------------------------------------------
    // 3. std::exit() - normal termination, but skips local cleanup
    // -------------------------------------------------------
    // std::exit() does NOT destroy local variables in the current
    // function. It DOES call atexit-registered functions and
    // flushes static storage / file buffers.
    //
    // Uncomment to test (will skip code after this point):
    // std::cout << "Calling std::exit(0)...\n";
    // std::exit(0);   // Program ends here, atexit functions run
    // std::cout << "This will NOT print.\n";

    // -------------------------------------------------------
    // 4. std::abort() - abnormal termination, NO cleanup
    // -------------------------------------------------------
    // std::abort() terminates immediately:
    //   - Does NOT call atexit functions
    //   - Does NOT flush buffers
    //   - Does NOT destroy objects
    //   - May produce a core dump
    //
    // Uncomment to test (no cleanup runs):
    // std::cout << "Calling std::abort()...\n";
    // std::abort();   // Immediate termination, atexit NOT called

    // -------------------------------------------------------
    // 5. Summary comparison
    // -------------------------------------------------------
    std::cout << "Halt method comparison:\n";
    std::cout << "+-----------------+----------+--------+---------+\n";
    std::cout << "| Method          | Destroys | atexit | Flushes |\n";
    std::cout << "|                 | locals   | called | I/O     |\n";
    std::cout << "+-----------------+----------+--------+---------+\n";
    std::cout << "| return from main| Yes      | Yes    | Yes     |\n";
    std::cout << "| std::exit()     | NO       | Yes    | Yes     |\n";
    std::cout << "| std::abort()    | NO       | NO     | NO      |\n";
    std::cout << "+-----------------+----------+--------+---------+\n";

    std::cout << "\nBest practice: Use 'return' from main.\n";
    std::cout << "Avoid std::exit() and std::abort() - prefer exceptions.\n";

    // -------------------------------------------------------
    // Key points:
    // - return from main is the cleanest way to end a program
    // - std::exit() calls atexit functions but skips local destructors
    // - std::abort() does NO cleanup at all
    // - std::atexit() registers functions called on normal exit (LIFO)
    // - Prefer exceptions over halts for error handling
    // -------------------------------------------------------

    return 0;
    // After this return, atexit functions run in reverse order:
    //   1. anotherCleanup()
    //   2. cleanup()
}
