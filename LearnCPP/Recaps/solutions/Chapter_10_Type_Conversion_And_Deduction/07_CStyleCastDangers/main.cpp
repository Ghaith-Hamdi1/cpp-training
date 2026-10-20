// Chapter 10 - Project 07: Why C-Style Casts Are Dangerous
//
// C-style casts use the syntax: (type)expression  or  type(expression)
//
// Problems with C-style casts:
//   1. They can silently perform ANY cast: static_cast, const_cast,
//      reinterpret_cast, or combinations - you can't tell which one.
//   2. They can strip const qualifiers without any warning.
//   3. They can reinterpret memory, leading to undefined behavior.
//   4. They're harder to search for in code (just parentheses).
//
// BEST PRACTICE: Always use static_cast instead.
// It's explicit, searchable, and only performs safe conversions.

#include <iostream>

int main()
{
    // =============================================================
    // 1. C-style cast doing a "safe" conversion (acts like static_cast)
    // =============================================================
    std::cout << "=== C-style cast as static_cast ===\n";

    double pi{3.14159};

    // C-style cast - works, but what kind of cast is this? Unclear.
    int cStyleResult{(int)pi};
    std::cout << "  (int)3.14159 = " << cStyleResult << '\n';

    // Preferred: static_cast - clear, searchable, safe
    int staticResult{static_cast<int>(pi)};
    std::cout << "  static_cast<int>(3.14159) = " << staticResult << '\n';

    // =============================================================
    // 2. C-style cast can strip const (acts like const_cast!)
    // =============================================================
    std::cout << "\n=== C-style cast removing const (DANGEROUS!) ===\n";

    const int constVal{42};
    // C-style cast silently removes const - this is DANGEROUS
    // Modifying a const object is undefined behavior!
    // int* nonConstPtr{ (int*)&constVal };   // Compiles! Very dangerous.
    // *nonConstPtr = 100;                     // Undefined behavior!

    // static_cast would NOT allow this:
    // int* safePtr{ static_cast<int*>(&constVal) };  // Compile error!

    std::cout << "  C-style cast can silently strip const (undefined behavior!).\n";
    std::cout << "  static_cast correctly prevents this.\n";

    // =============================================================
    // 3. Functional-style cast - same problems as C-style
    // =============================================================
    std::cout << "\n=== Functional-style cast ===\n";

    // Functional style uses Type(value) syntax
    int funcResult{int(pi)};
    std::cout << "  int(3.14159) = " << funcResult << '\n';
    // Same issues as C-style cast - prefer static_cast<int>(pi)

    // =============================================================
    // 4. Searchability comparison
    // =============================================================
    std::cout << "\n=== Searchability ===\n";
    std::cout << "  C-style:     (int)value  - hard to search for in code\n";
    std::cout << "  static_cast: static_cast<int>(value) - easy to find!\n";
    std::cout << "  You can grep for 'static_cast' to find all casts.\n";

    // =============================================================
    // 5. Summary: Why static_cast wins
    // =============================================================
    std::cout << "\n=== Summary ===\n";
    std::cout << "  static_cast advantages:\n";
    std::cout << "    - Compile-time type checking\n";
    std::cout << "    - Won't accidentally remove const\n";
    std::cout << "    - Won't reinterpret memory\n";
    std::cout << "    - Easy to search for in code\n";
    std::cout << "    - Makes programmer intent explicit\n";

    return 0;
}
