// Chapter 7 - Project 12: Using Declarations and Using Directives
// =================================================================
// Two mechanisms for accessing namespaced names without full qualification:
//
//   using std::cout;           // using DECLARATION - aliases ONE name
//   using namespace std;       // using DIRECTIVE - imports ALL names
//
// Best practices:
//   - Prefer explicit Namespace::name qualification
//   - If you must, prefer 'using declarations' over 'using directives'
//   - NEVER put using-statements in header files
//   - NEVER put using-statements before #include directives

#include <iostream>
#include <string>
#include <string_view>

// -------------------------------------------------
// Example namespaces with potential collisions
// -------------------------------------------------
namespace LibraryA
{
    void print(std::string_view msg)
    {
        std::cout << "[LibA] " << msg << '\n';
    }

    int getValue() { return 42; }
}

namespace LibraryB
{
    void print(std::string_view msg)
    {
        std::cout << "[LibB] " << msg << '\n';
    }

    int getValue() { return 99; }
}

int main()
{
    // -------------------------------------------------
    // 1. Explicit qualification (BEST practice)
    // -------------------------------------------------
    std::cout << "1. Explicit qualification (preferred):\n";
    LibraryA::print("Hello from A");
    LibraryB::print("Hello from B");
    std::cout << "   A::getValue() = " << LibraryA::getValue() << '\n';
    std::cout << "   B::getValue() = " << LibraryB::getValue() << '\n';

    // -------------------------------------------------
    // 2. Using DECLARATION - aliases a single name
    // -------------------------------------------------
    std::cout << "\n2. Using declaration (acceptable in limited scope):\n";
    {
        using LibraryA::print; // Only LibraryA::print is aliased
        print("This calls LibraryA::print");
        // print from LibraryB still requires qualification:
        LibraryB::print("This calls LibraryB::print");

        // using LibraryB::print; // ERROR if uncommented: ambiguous 'print'
    }
    // 'print' alias is no longer active outside the block

    // -------------------------------------------------
    // 3. Using DIRECTIVE - imports everything (DANGEROUS)
    // -------------------------------------------------
    std::cout << "\n3. Using directive (avoid in production code):\n";
    {
        // This would cause ambiguity if both are imported:
        // using namespace LibraryA;
        // using namespace LibraryB;
        // print("Hello");  // ERROR: ambiguous - which print?

        // Even with one, you lose clarity:
        using namespace LibraryA;
        print("Using directive - but which namespace? Less clear.");
        std::cout << "   getValue() = " << getValue() << '\n'; // LibraryA
    }

    // -------------------------------------------------
    // 4. Why 'using namespace std;' is bad
    // -------------------------------------------------
    std::cout << "\n4. Why 'using namespace std;' is dangerous:\n";
    std::cout << "   - std has THOUSANDS of names (count, size, distance, move...)\n";
    std::cout << "   - Your own names can silently collide with std names\n";
    std::cout << "   - Future C++ standards add more names → code may break\n";

    // Example of a potential collision:
    // using namespace std;
    // int count{ 5 };     // Conflicts with std::count!
    // int distance{ 10 }; // Conflicts with std::distance!

    // -------------------------------------------------
    // 5. NEVER put using-statements in headers
    // -------------------------------------------------
    std::cout << "\n5. NEVER do this in a header file:\n";
    std::cout << "   // myheader.h\n";
    std::cout << "   using namespace std;  // POLLUTES every file that includes it!\n";
    std::cout << "   Every .cpp that #includes this header gets ALL of std imported.\n";

    // -------------------------------------------------
    // 6. Safe patterns
    // -------------------------------------------------
    std::cout << "\n6. Safe using-declaration patterns:\n";
    {
        // OK: using declarations inside a function body, for specific names
        using std::cout;
        using std::string;

        string name{"Copilot"};
        cout << "   Hello, " << name << "!\n";
        // Limited scope, specific names - acceptable
    }

    // -------------------------------------------------
    // Summary
    // -------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "  1st choice: Namespace::name (explicit, clear)\n";
    std::cout << "  2nd choice: using Namespace::name; (declaration, limited scope)\n";
    std::cout << "  AVOID:      using namespace X; (directive, risky)\n";
    std::cout << "  NEVER:      using-statements in headers or before #includes\n";

    return 0;
}
