// Chapter 12 - Project 13: Type Deduction with Pointers, References, and Const
// ==============================================================================
// When using 'auto', the compiler deduces the type from the initializer.
// Important rules:
//
//   1. auto DROPS references          - auto x = ref;  → x is a copy, not a reference
//   2. auto DROPS top-level const     - auto x = constVar; → x is non-const
//   3. auto KEEPS pointers            - auto p = &x;  → p is int*
//   4. auto KEEPS low-level const     - auto p = constPtr; → p is const int*
//
// To get the type you want, be explicit:
//   auto&       - deduce a reference
//   const auto& - deduce a const reference
//   auto*       - make it clear you're deducing a pointer
//   const auto  - reapply top-level const

#include <iostream>

int main()
{
    // ========================================
    // 1. auto DROPS references
    // ========================================
    int x{10};
    int &ref{x};

    auto a{ref}; // 'a' is int (not int&) - reference is dropped
    a = 99;
    std::cout << "auto drops reference:\n";
    std::cout << "  x = " << x << '\n'; // 10 - x unchanged because 'a' is a copy
    std::cout << "  a = " << a << '\n'; // 99

    auto &b{x}; // 'b' is int& - we explicitly requested a reference
    b = 42;
    std::cout << "  auto& b = x; b = 42 → x = " << x << '\n'; // 42

    // ========================================
    // 2. auto DROPS top-level const
    // ========================================
    const int cx{100};

    auto c{cx}; // 'c' is int (not const int) - top-level const dropped
    c = 200;    // OK: c is non-const
    std::cout << "\nauto drops top-level const:\n";
    std::cout << "  c = " << c << '\n'; // 200

    const auto d{cx}; // explicitly re-add const → d is const int
    // d = 300;           // ERROR: d is const
    std::cout << "  const auto d = cx → d = " << d << '\n';

    // ========================================
    // 3. auto KEEPS pointers
    // ========================================
    int y{50};
    auto ptr{&y}; // ptr is int* - pointers are not dropped

    *ptr = 60;
    std::cout << "\nauto keeps pointers:\n";
    std::cout << "  y = " << y << '\n'; // 60

    // auto* makes pointer deduction explicit (and clearer)
    auto *ptr2{&y}; // ptr2 is int* - same result, but more readable
    std::cout << "  *ptr2 = " << *ptr2 << '\n';

    // ========================================
    // 4. auto KEEPS low-level const (const on pointed-to type)
    // ========================================
    const int z{70};
    auto ptr3{&z}; // ptr3 is const int* - low-level const is preserved!
    // *ptr3 = 80;      // ERROR: can't modify through pointer to const

    std::cout << "\nauto keeps low-level const:\n";
    std::cout << "  *ptr3 = " << *ptr3 << '\n'; // 70

    // auto* with const makes it very explicit
    const auto *ptr4{&z}; // const int* - crystal clear intention
    auto *const ptr5{&z}; // int const* const? No - const int* const (pointer is also const)

    std::cout << "  *ptr4 = " << *ptr4 << '\n';
    // ptr5 = &y;  // ERROR: ptr5 is a const pointer (can't reseat)

    // ========================================
    // 5. const auto& - deduce a const reference
    // ========================================
    const auto &cref{x}; // const int& - can't modify x through cref
    // cref = 0;             // ERROR
    std::cout << "\nconst auto& cref = x → cref = " << cref << '\n';

    // ========================================
    // Summary
    // ========================================
    std::cout << "\n=== Summary ===\n";
    std::cout << "auto       : drops & and top-level const, keeps * and low-level const\n";
    std::cout << "auto&      : deduces a reference\n";
    std::cout << "const auto&: deduces a const reference\n";
    std::cout << "auto*      : makes pointer deduction explicit\n";
    std::cout << "const auto : reapplies top-level const\n";

    return 0;
}
