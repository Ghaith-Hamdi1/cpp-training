// Chapter 11 - Project 04: Ambiguous Matches
// ================================================================
// An ambiguous match occurs when the compiler finds two or more equally
// valid overloads at the same resolution step and cannot choose.
// This is a compile error.
//
// This file demonstrates ambiguity and three ways to resolve it.

#include <iostream>

// ---------------------------------------------------------------
// Setup: two overloads that can cause ambiguity
// ---------------------------------------------------------------
void print(int x)
{
    std::cout << "print(int): " << x << '\n';
}

void print(double x)
{
    std::cout << "print(double): " << x << '\n';
}

// Calling print(5.0f) would be ambiguous because:
//   float → int   is a numeric conversion
//   float → double is a numeric promotion
// Actually float→double is a promotion (step 2) which beats conversion (step 3),
// so print(5.0f) would call print(double).

// But consider this pair:
void show(unsigned int x)
{
    std::cout << "show(unsigned int): " << x << '\n';
}

void show(float x)
{
    std::cout << "show(float): " << x << '\n';
}

// Calling show(42) is ambiguous:
//   int → unsigned int  is a numeric conversion
//   int → float         is a numeric conversion
// Both are at the same resolution step (step 3), neither is preferred. → AMBIGUOUS

// ---------------------------------------------------------------
// Resolution strategy 1: Add an exact-match overload
// ---------------------------------------------------------------
void show(int x)
{
    std::cout << "show(int) [exact-match overload]: " << x << '\n';
}
// Now show(42) matches show(int) exactly (step 1) - no ambiguity.

// ---------------------------------------------------------------
// Resolution strategy 2: Use static_cast at the call site
// ---------------------------------------------------------------
// We can explicitly cast the argument so one overload becomes an exact match.
// demonstrated in main() below.

// ---------------------------------------------------------------
// Resolution strategy 3: Use literal suffixes
// ---------------------------------------------------------------
// Instead of 5 (int), write 5u (unsigned int) or 5.0f (float)
// to produce an exact match for the desired overload.
// demonstrated in main() below.

int main()
{
    std::cout << "=== Resolved via exact-match overload ===\n";
    show(42); // now calls show(int) - exact match, no ambiguity

    std::cout << "\n=== Resolved via static_cast ===\n";
    // Without the show(int) overload, we'd need this:
    show(static_cast<unsigned int>(42)); // exact match → show(unsigned int)
    show(static_cast<float>(42));        // exact match → show(float)

    std::cout << "\n=== Resolved via literal suffix ===\n";
    show(42u);   // unsigned int literal → show(unsigned int)
    show(42.0f); // float literal → show(float)

    // ---------------------------------------------------------------
    // Another classic ambiguity: char literal with int/double overloads
    // ---------------------------------------------------------------
    // print('a');
    // char → int  is a numeric promotion (step 2)
    // char → double is a numeric conversion (step 3)
    // Promotion wins, so this is NOT ambiguous - calls print(int).
    std::cout << "\n=== char to int (promotion wins) ===\n";
    print('a'); // print(int) via promotion - no ambiguity here

    return 0;
}
