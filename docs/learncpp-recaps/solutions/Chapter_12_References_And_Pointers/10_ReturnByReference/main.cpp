// Chapter 12 - Project 10: Return by Reference and Return by Address
// ====================================================================
// Returning by reference avoids copying, but the object MUST outlive the function.
//
// SAFE to return by reference:
//   • A reference parameter that was passed in
//   • A static local variable (but error-prone - avoid non-const static refs)
//   • A member of an object that outlives the function
//
// NEVER return a local variable by reference - it creates a DANGLING reference (UB).
//
// Lifetime extension does NOT work across function boundaries.

#include <iostream>
#include <string>

// SAFE: returning a reference parameter by reference
// The caller's object outlives the function, so this is fine.
const std::string &longerString(const std::string &a, const std::string &b)
{
    return (a.length() >= b.length()) ? a : b;
}

// SAFE: returning a reference to a static local
// But be careful - non-const static refs can cause subtle bugs.
const int &getCounter()
{
    static int count{0};
    ++count;
    return count; // OK: static local lives until program exit
}

// *** DANGEROUS - DO NOT DO THIS ***
// Returning a reference to a local variable - creates a dangling reference.
// Commented out to prevent undefined behavior.
/*
const int& getDangling()
{
    int local{ 42 };
    return local;   // DANGLING: local is destroyed when function returns
}
*/

// Return by address - similar to return by reference, but returns a pointer.
// Useful when you need to return "no object" (nullptr).
int *findValue(int *arr, int size, int target)
{
    for (int i{0}; i < size; ++i)
    {
        if (arr[i] == target)
            return &arr[i]; // SAFE: array outlives this function call
    }
    return nullptr; // not found
}

int main()
{
    // ----- Return by reference: returning a passed-in reference -----
    std::string a{"short"};
    std::string b{"much longer string"};

    const std::string &result{longerString(a, b)};
    std::cout << "Longer string: " << result << '\n';

    // No copy was made - result refers directly to b
    std::cout << "Same object as b? " << (&result == &b ? "yes" : "no") << '\n';

    // ----- Return by reference: static local -----
    std::cout << "\nCounter: " << getCounter() << '\n'; // 1
    std::cout << "Counter: " << getCounter() << '\n';   // 2
    std::cout << "Counter: " << getCounter() << '\n';   // 3

    // ----- Return by address -----
    int arr[]{10, 20, 30, 40, 50};
    int *found{findValue(arr, 5, 30)};

    if (found)
        std::cout << "\nFound 30 at address " << found << ", value = " << *found << '\n';
    else
        std::cout << "\n30 not found.\n";

    int *notFound{findValue(arr, 5, 99)};
    if (notFound)
        std::cout << "Found 99.\n";
    else
        std::cout << "99 not found (nullptr returned).\n";

    // ----- Lifetime extension does NOT work across function calls -----
    // const int& bad{ getDangling() };  // UB! The temporary/local is already gone
    // std::cout << bad;                 // Accessing a dangling reference

    return 0;
}
