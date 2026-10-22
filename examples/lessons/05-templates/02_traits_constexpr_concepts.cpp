// Lessons 9 and 13: type traits, if constexpr, SFINAE/enable_if, concepts, constexpr / consteval, template metaprogramming.
#include <array>
#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>

static_assert(std::is_integral_v<int>);
static_assert(!std::is_integral_v<double>);
static_assert(std::is_same_v<int, std::remove_reference_t<int&>>);
static_assert(!std::is_same_v<int, const int>);         // const is part of the type
static_assert(std::is_same_v<std::decay_t<const int&>, int>);
static_assert(std::is_base_of_v<std::ios_base, std::ostream>);

template <typename T>
T multiply(T a, T b) {
    static_assert(std::is_arithmetic_v<T>, "multiply needs a number type");
    return a * b;
}

template <typename T>
std::string describe(const T& v) {
    if constexpr (std::is_integral_v<T>)            return "integer " + std::to_string(v);
    else if constexpr (std::is_floating_point_v<T>) return "float " + std::to_string(v);
    else                                            return "something else";   // not compiled for numbers
}

template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void show(const T& v) { std::cout << "enable_if integral: " << v << '\n'; }
template <typename T, std::enable_if_t<!std::is_integral_v<T>, bool> = true>
void show(const T& v) { std::cout << "enable_if other: " << v << '\n'; }

template <std::integral T>                              // C++20 concept: readable constraint
T twice(T x) { return x * 2; }

constexpr int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }
consteval int sq(int x) { return x * x; }               // MUST be evaluated at compile time

template <unsigned N>
struct Fact { static constexpr unsigned long value = N * Fact<N - 1>::value; };   // classic TMP
template <>
struct Fact<0> { static constexpr unsigned long value = 1; };

int main() {
    std::cout << multiply(6, 7) << ' ' << multiply(1.5, 2.0) << '\n';
    // multiply(std::string("a"), std::string("b"));     // compile error with YOUR message

    std::cout << describe(42) << ", " << describe(2.5) << ", " << describe(std::string("x")) << '\n';
    show(21);
    show(2.5);
    std::cout << "twice(21) = " << twice(21) << '\n';
    // twice(2.5);                                       // error: constraint not satisfied

    constexpr int f10 = factorial(10);                   // computed by the compiler
    int arr[factorial(4)];                               // size 24
    int n = 5;
    int r = factorial(n);                                // same function, run at run time
    constexpr int s7 = sq(7);
    // int bad = sq(n);                                  // ERROR: consteval needs a constant
    static_assert(Fact<5>::value == 120);
    std::array<int, factorial(3)> small{};
    std::cout << f10 << ' ' << sizeof(arr) / sizeof(int) << ' ' << r << ' ' << s7 << ' ' << Fact<5>::value << ' ' << small.size() << '\n';
}
