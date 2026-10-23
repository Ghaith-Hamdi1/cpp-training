// Chapter 5 - Project 11: String View Dangling
// ===============================================
// Topics:
//   - std::string is an owner; std::string_view is a viewer
//   - Dangling string_view: viewing a destroyed/modified string
//   - When it's safe to return a string_view
//   - When it's NOT safe to return a string_view
//   - Why initializing string_view with a std::string temporary is dangerous
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string>
#include <string_view>

// -------------------------------------------------------
// SAFE: Returning string_view of a string_view parameter
// -------------------------------------------------------
// The caller owns the underlying string, so the returned
// view is valid as long as the caller's string exists.
std::string_view firstWord(std::string_view sentence)
{
    auto spacePos = sentence.find(' ');
    if (spacePos != std::string_view::npos)
        return sentence.substr(0, spacePos);
    return sentence;
}

// -------------------------------------------------------
// SAFE: Returning string_view of a C-style string literal
// -------------------------------------------------------
// C-style string literals exist for the entire program lifetime,
// so a view into them never dangles.
std::string_view getGreeting()
{
    return "Hello, World!"; // OK: literal lives for the entire program
}

// -------------------------------------------------------
// DANGEROUS: Returning string_view of a local std::string
// -------------------------------------------------------
// The local string is destroyed when the function returns,
// leaving the view dangling. DO NOT DO THIS!
/*
std::string_view getDanglingView()
{
    std::string local{ "I will be destroyed" };
    return local;  // DANGER: local is destroyed, view is dangling!
}
*/

int main()
{
    // -------------------------------------------------------
    // 1. Owner vs Viewer
    // -------------------------------------------------------
    std::cout << "=== Owner vs Viewer ===\n";

    std::string owner{"Hello, C++!"}; // Owner: manages its own memory
    std::string_view viewer{owner};   // Viewer: just points to owner's data

    std::cout << "owner:  \"" << owner << "\"\n";
    std::cout << "viewer: \"" << viewer << "\"\n";

    // -------------------------------------------------------
    // 2. Dangling when the owner is destroyed
    // -------------------------------------------------------
    std::cout << "\n=== Dangling After Owner Destruction ===\n";
    std::cout << "(Demonstrated with comments - actual UB would crash or corrupt)\n";

    // Simulated scenario:
    // {
    //     std::string temp{ "Temporary string" };
    //     std::string_view view{ temp };
    // }  // temp is destroyed here
    // std::cout << view;  // UNDEFINED BEHAVIOR: view is dangling!

    std::cout << "If the owned string is destroyed, any string_view into it\n";
    std::cout << "becomes a dangling view. Using it is undefined behavior.\n";

    // -------------------------------------------------------
    // 3. Dangling when the owner is modified
    // -------------------------------------------------------
    std::cout << "\n=== Invalidation When Owner is Modified ===\n";

    std::string str{"Short"};
    std::string_view sv{str};

    std::cout << "Before modification: sv = \"" << sv << "\"\n";

    // Modifying the std::string may reallocate its internal buffer,
    // invalidating all views.
    str = "This is a much longer string that may cause reallocation";
    // sv is now potentially dangling! The internal buffer may have moved.
    // Using sv here is undefined behavior.

    std::cout << "After modifying str, sv may be dangling.\n";
    std::cout << "NEVER use a string_view after modifying the viewed string.\n";

    // -------------------------------------------------------
    // 4. Safe returns
    // -------------------------------------------------------
    std::cout << "\n=== Safe Returns ===\n";

    // Safe: C-style string literal
    std::string_view greeting = getGreeting();
    std::cout << "getGreeting():  \"" << greeting << "\" (safe - literal lives forever)\n";

    // Safe: string_view of caller-owned string
    std::string sentence{"The quick brown fox"};
    std::string_view word = firstWord(sentence);
    std::cout << "firstWord():    \"" << word << "\" (safe - caller owns the string)\n";

    // -------------------------------------------------------
    // 5. PITFALL: string_view from temporary std::string
    // -------------------------------------------------------
    std::cout << "\n=== PITFALL: Temporary std::string ===\n";

    // using namespace std::string_literals;
    // std::string_view sv2{ "hello"s };  // DANGER!
    // "hello"s creates a temporary std::string that is destroyed at the
    // end of the expression, leaving sv2 dangling immediately.

    // SAFE alternative:
    std::string_view sv2{"hello"}; // C-style literal - lives forever
    std::cout << "sv2 = \"" << sv2 << "\" (safe - C-style literal)\n";
    std::cout << "NEVER initialize string_view with a temporary std::string.\n";

    // -------------------------------------------------------
    // 6. Safe to return local std::string by value
    // -------------------------------------------------------
    std::cout << "\n=== Returning std::string by Value is Safe ===\n";
    std::cout << "It's fine to return a local std::string by value.\n";
    std::cout << "Move semantics avoids the copy. Example:\n";
    std::cout << "  std::string getName() { return \"Alice\"; }  // OK!\n";
    std::cout << "But do NOT return a std::string_view of a local std::string.\n";

    return 0;
}
