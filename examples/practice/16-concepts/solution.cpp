// Exercise 16: concepts and constrained templates (C++20). Worked solution.
// Build: g++ -std=c++20 -Wall -Wextra solution.cpp -o sol && ./sol
#include <concepts>
#include <string>
#include <vector>
#include "../check.h"

template <typename T>
concept Summable = requires(T a, T b) { { a + b } -> std::convertible_to<T>; };

template <Summable T>
T sumAll(const std::vector<T>& v)
{
    T total{};
    for (const auto& x : v) total = total + x;
    return total;
}

std::string kind(std::integral auto) { return "integer"; }
std::string kind(std::floating_point auto) { return "float"; }

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
    return finish("16 concepts");
}
