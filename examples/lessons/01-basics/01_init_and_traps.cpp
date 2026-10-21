// Lesson 1: initialization forms, the signed/unsigned trap, prefix vs postfix, pass by value/reference.
#pragma GCC diagnostic ignored "-Wsign-compare"   // the trap below is deliberate; the compiler warns about it
#include <iostream>
#include <string>

void byValue(int n) { n++; (void)n; }                         // works on a COPY
void byRef(int& n) { n++; }                            // works on the ORIGINAL
void byConstRef(const std::string& s) { std::cout << "read-only: " << s << '\n'; }

int main() {
    int b = 5;      // copy initialization
    int c(5);       // direct initialization
    int d{5};       // brace initialization: preferred
    int e{};        // empty braces: zero-initialized
    // int f{3.7};  // ERROR: braces forbid narrowing double -> int
    auto g = 5;     // g is int
    std::cout << b << c << d << e << g << '\n';

    std::cout << "(-1 < 1u) = " << (-1 < 1u) << "   // -1 became 4294967295\n";

    int x = 5;
    int a = x++;    // use x (5), then increment
    int p = ++x;    // increment first, then use
    std::cout << a << ' ' << p << ' ' << x << "   // 5 7 7\n";

    int v = 1;
    byValue(v);
    byRef(v);
    std::cout << "after byValue + byRef: " << v << "   // only byRef changed it\n";
    byConstRef("no copy made");

    std::cout << "7 / 2 = " << 7 / 2 << ", 7 % 2 = " << 7 % 2 << ", 7 / 2.0 = " << 7 / 2.0 << '\n';
}
