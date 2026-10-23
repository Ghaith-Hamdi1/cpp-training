// Exercise 16: concepts and constrained templates (C++20).
//
//   concept Summable<T>      T has an operator+ that gives back something convertible to T
//                            (use a requires-expression)
//   T sumAll(const std::vector<T>& v)   constrained with Summable; returns the sum of the elements
//                            (T{} for an empty vector)
//   std::string kind(x)      two overloads selected by concepts, not by enable_if:
//                            "integer" for std::integral types, "float" for std::floating_point types
// Build: g++ -std=c++20 -Wall -Wextra exercise.cpp -o ex && ./ex
#include <concepts>
#include <string>
#include <vector>
#include "../check.h"

template <typename T>
concept Summable = false;                                   // TODO: a requires-expression

template <typename T>
T sumAll(const std::vector<T>& v) { (void)v; return T{}; }  // TODO: constrain with Summable and add up the elements

std::string kind(int) { return ""; }                        // TODO: replace both with concept-constrained overloads
std::string kind(double) { return ""; }

struct NoPlus {};

int main()
{
    CHECK(Summable<int>);
    CHECK(Summable<double>);
    CHECK(Summable<std::string>);
    CHECK(!Summable<NoPlus>);
    CHECK(!Summable<std::vector<int>>);

    CHECK(sumAll(std::vector<int>{1, 2, 3, 4}) == 10);
    CHECK(sumAll(std::vector<double>{0.5, 0.25}) == 0.75);
    CHECK(sumAll(std::vector<std::string>{"a", "b", "c"}) == "abc");
    CHECK(sumAll(std::vector<int>{}) == 0);

    CHECK(kind(7) == "integer");
    CHECK(kind('x') == "integer");
    CHECK(kind(true) == "integer");
    CHECK(kind(2.5) == "float");
    CHECK(kind(2.5f) == "float");
    // Not tested, but try it: sumAll(std::vector<NoPlus>{}) must be rejected at compile time
    // with a message about the unsatisfied constraint, not with an error deep inside the body.
    return finish("16 concepts");
}
