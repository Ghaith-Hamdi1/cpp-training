// Chapter 10 - Project 09: Type Deduction for Objects Using 'auto'
//
// The 'auto' keyword lets the compiler deduce a variable's type from
// its initializer, reducing redundancy.
//
// Key rules:
//   1. auto DROPS const - add const/constexpr explicitly if needed
//   2. String literals deduce to const char*, NOT std::string
//   3. auto requires an initializer (no uninitialized auto variables)
//   4. Use auto when the exact type doesn't matter
//   5. Prefer explicit types when clarity is important
//
// Benefits: avoids redundancy, prevents unintended conversions,
//           guarantees initialization.

#include <iostream>
#include <string>
#include <string_view>

using namespace std::string_literals;      // for "..."s suffix
using namespace std::string_view_literals; // for "..."sv suffix

int main()
{
    // =============================================================
    // 1. Basic auto deduction
    // =============================================================
    std::cout << "=== Basic auto deduction ===\n";

    auto i{42};   // deduces to int
    auto d{3.14}; // deduces to double
    auto f{1.5f}; // deduces to float (because of 'f' suffix)
    auto c{'A'};  // deduces to char
    auto b{true}; // deduces to bool

    std::cout << "  auto i{42} -> int: " << i << '\n';
    std::cout << "  auto d{3.14} -> double: " << d << '\n';
    std::cout << "  auto f{1.5f} -> float: " << f << '\n';
    std::cout << "  auto c{'A'} -> char: " << c << '\n';
    std::cout << std::boolalpha;
    std::cout << "  auto b{true} -> bool: " << b << '\n';

    // =============================================================
    // 2. auto DROPS const - must re-apply it explicitly
    // =============================================================
    std::cout << "\n=== auto drops const ===\n";

    const int constVal{100};

    auto nonConst{constVal}; // deduces to int (NOT const int!)
    nonConst = 200;          // compiles! nonConst is mutable
    std::cout << "  auto from const int -> int (mutable): " << nonConst << '\n';

    const auto staysConst{constVal}; // const auto -> const int
    // staysConst = 200;             // Won't compile - staysConst is const
    std::cout << "  const auto from const int -> const int: " << staysConst << '\n';

    constexpr auto ce{42}; // constexpr auto -> constexpr int
    std::cout << "  constexpr auto{42} -> constexpr int: " << ce << '\n';

    // =============================================================
    // 3. String literal pitfall
    // =============================================================
    std::cout << "\n=== String literal type deduction ===\n";

    auto cstr{"hello"}; // deduces to const char* (NOT std::string!)
    std::cout << "  auto{\"hello\"} -> const char*: " << cstr << '\n';

    auto str{"hello"s}; // deduces to std::string (using s suffix)
    std::cout << "  auto{\"hello\"s} -> std::string: " << str << '\n';

    auto sv{"hello"sv}; // deduces to std::string_view (using sv suffix)
    std::cout << "  auto{\"hello\"sv} -> std::string_view: " << sv << '\n';

    // =============================================================
    // 4. auto prevents unintended conversions
    // =============================================================
    std::cout << "\n=== auto prevents unintended conversions ===\n";

    // Without auto, you might accidentally convert:
    // int x{ someDoubleFunc() };   // silently truncates!

    // With auto, you get the actual return type:
    auto noSurprise{3.14 / 2.0}; // auto -> double, no truncation
    std::cout << "  auto{3.14 / 2.0} = " << noSurprise << " (no truncation)\n";

    // =============================================================
    // 5. auto guarantees initialization
    // =============================================================
    std::cout << "\n=== auto guarantees initialization ===\n";

    // int uninit;         // compiles (but uninitialized - undefined behavior!)
    // auto uninit;        // won't compile! auto needs an initializer

    std::cout << "  'auto x;' won't compile - must provide an initializer.\n";
    std::cout << "  This prevents accidental use of uninitialized variables.\n";

    // =============================================================
    // 6. When to use auto vs explicit types
    // =============================================================
    std::cout << "\n=== Guidelines ===\n";
    std::cout << "  Use auto when:\n";
    std::cout << "    - The type is obvious from the initializer\n";
    std::cout << "    - The exact type doesn't matter\n";
    std::cout << "    - You want to avoid redundancy\n";
    std::cout << "  Use explicit types when:\n";
    std::cout << "    - Clarity about the type is important\n";
    std::cout << "    - You want a specific type different from the initializer\n";

    return 0;
}
