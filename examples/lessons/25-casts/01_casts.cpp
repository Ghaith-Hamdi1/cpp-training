// Casts and Type Conversions: the classic implicit conversions, narrowing, a C-style cast removing const, static_cast, dynamic_cast on a
// pointer and a reference, const_cast for an old API, reinterpret_cast to read bytes, and memcpy / std::bit_cast. Compile with -std=c++23.
#pragma GCC diagnostic ignored "-Wsign-compare"   // the signed/unsigned comparison below is deliberate
#include <bit>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <typeinfo>

struct Base { virtual ~Base() = default; };
struct Derived : Base { int y = 7; };
struct Other : Base {};
void legacy(char* s) { std::printf("legacy: %s\n", s); }   // only reads

int main() {
    std::cout << (-1 < 1u) << ' ' << (7 / 2) << ' ' << (7 / 2.0) << ' ' << static_cast<int>(-3.9) << '\n';   // 0 3 3.5 -3
    std::uint8_t a = 200, b = 100;
    int s = a + b;
    std::uint8_t t = a + b;
    std::cout << s << ' ' << (int)t << '\n';                                                              // 300 44
    char c = static_cast<char>(0xFF);
    std::cout << static_cast<int>(c) << '\n';                                                             // -1 (signed char here)
    int g = 3.7;
    std::cout << g << '\n';                                                                               // 3
    long long big = 3000000000LL;
    int small = static_cast<int>(big);
    std::cout << small << '\n';                                                                           // implementation-defined before C++20, -1294967296 here
    // C-style cast silently removing const
    const int k = 5;
    int* pk = (int*)&k;
    (void)pk;
    // static_cast
    void* vp = &g;
    int* ip = static_cast<int*>(vp);
    std::cout << *ip << '\n';
    double avg = static_cast<double>(7) / 2;
    std::cout << avg << '\n';                                                                             // 3.5
    // dynamic_cast
    Base* bd = new Derived;
    Base* bo = new Other;
    std::cout << (dynamic_cast<Derived*>(bd) != nullptr) << (dynamic_cast<Derived*>(bo) != nullptr) << '\n';   // 10
    try { Base& r = *bo; (void)dynamic_cast<Derived&>(r); }
    catch (const std::bad_cast&) { std::puts("bad_cast"); }
    std::cout << (typeid(*bd) == typeid(Derived)) << '\n';                                                // 1
    delete bd; delete bo;
    // const_cast
    const char* msg = "hello";
    legacy(const_cast<char*>(msg));
    // reinterpret_cast bytes
    int x = 0x01020304;
    auto* bytes = reinterpret_cast<const unsigned char*>(&x);
    std::cout << (int)bytes[0] << '\n';                                                                   // 4 (little endian)
    std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(&x);
    std::cout << (reinterpret_cast<int*>(addr) == &x) << '\n';                                            // 1
    // memcpy and bit_cast
    float f = 1.0f;
    std::uint32_t u1; std::memcpy(&u1, &f, sizeof u1);
    std::uint32_t u2 = std::bit_cast<std::uint32_t>(f);
    std::printf("%08x %08x\n", u1, u2);                                                                   // 3f800000 3f800000
}
