// Lesson 2: initialization forms and the braced-init traps, auto and decltype, implicit conversions and promotions,
// the named casts, and constexpr. Compile with -std=c++23.
#pragma GCC diagnostic ignored "-Wsign-compare"   // deliberate: the -1 < 1u trap
#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

struct Point { int x; int y; };                                   // an aggregate: no constructors

struct Widget {
    int v;
    Widget() : v(1) { std::cout << "default "; }
    Widget(std::initializer_list<int> l) : v(static_cast<int>(l.size())) { std::cout << "init-list "; }
    Widget(int a, int b) : v(a + b) { std::cout << "(int,int) "; }
};

constexpr int square(int x) { return x * x; }

int main()
{
    int a;                       (void)a;                          // default-initialized: INDETERMINATE value (never read it)
    int b{};                                                        // value-initialized: zero
    int c = 5;                                                      // copy-initialized
    int d(5);                                                       // direct-initialized
    int e{5};                                                       // list-initialized (preferred: rejects narrowing)
    // int f{3.7};                                                  // ERROR: narrowing double -> int in braces
    int g = 3.7;                                                    // compiles: silently truncates to 3
    std::cout << "b=" << b << " c=" << c << " d=" << d << " e=" << e << " g=" << g << '\n';

    Point p1{1, 2};                                                 // aggregate initialization
    Point p2{.x = 3, .y = 4};                                       // designated initializers (C++20)
    Point p3{};                                                     // every member zero
    std::cout << "points: " << p1.x << p1.y << ' ' << p2.x << p2.y << ' ' << p3.x << p3.y << '\n';

    std::vector<int> v1(3, 7);                                      // parentheses: 3 elements, each 7
    std::vector<int> v2{3, 7};                                      // braces: initializer_list wins -> the elements 3 and 7
    std::cout << "vector(3, 7) has " << v1.size() << " elements, vector{3, 7} has " << v2.size() << '\n';

    std::cout << "Widget w1{}:      "; Widget w1{};      std::cout << "-> v=" << w1.v << '\n';
    std::cout << "Widget w2{1, 2}:  "; Widget w2{1, 2};  std::cout << "-> v=" << w2.v << "   (braces prefer the initializer_list constructor)\n";
    std::cout << "Widget w3(1, 2):  "; Widget w3(1, 2);  std::cout << "-> v=" << w3.v << '\n';

    auto i1 = 5;           static_assert(std::is_same_v<decltype(i1), int>);
    auto i2 = 5.0f;        static_assert(std::is_same_v<decltype(i2), float>);
    auto i3 = {1, 2, 3};   static_assert(std::is_same_v<decltype(i3), std::initializer_list<int>>);   // NOT a vector
    const int ci = 9;
    auto i4 = ci;          static_assert(std::is_same_v<decltype(i4), int>);                         // auto drops const
    decltype(ci) i5 = 10;  static_assert(std::is_same_v<decltype(i5), const int>);                  // decltype keeps it
    (void)i1; (void)i2; (void)i3; (void)i4; (void)i5;
    std::cout << "auto and decltype types checked at compile time\n";

    std::cout << "-1 < 1u is " << std::boolalpha << (-1 < 1u) << "   (the signed value became unsigned)\n";
    std::uint8_t big = 200, other = 100;
    std::cout << "uint8_t 200 + 100 = " << (big + other) << " (promoted to int); stored back: " << int(std::uint8_t(big + other)) << '\n';
    std::cout << "7 / 2 = " << 7 / 2 << ", 7 / 2.0 = " << 7 / 2.0 << ", (double)7 / 2 = " << static_cast<double>(7) / 2 << '\n';
    std::cout << "static_cast<int>(3.9) = " << static_cast<int>(3.9) << ", static_cast<int>(-3.9) = " << static_cast<int>(-3.9) << " (toward zero)\n";
    char ch = static_cast<char>(0xFF);
    std::cout << "char 0xFF widened: " << int(ch) << " (signed char here), as unsigned char: " << int(static_cast<unsigned char>(ch)) << '\n';

    enum class Color { Red = 1, Green = 2 };
    Color col = Color::Green;
    std::cout << "enum class needs a cast: " << static_cast<int>(col) << '\n';

    constexpr int n = square(6);                                    // computed by the compiler
    static_assert(n == 36);
    int arr[square(3)];                                             // a constant expression: array of 9
    std::cout << "constexpr square(6) = " << n << ", array size " << sizeof(arr) / sizeof(int) << '\n';
}
