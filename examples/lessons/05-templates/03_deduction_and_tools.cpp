// Lesson 12: how template arguments are deduced (by value, by reference, forwarding reference, arrays), class template
// argument deduction, alias templates, variable templates, template template parameters and std::index_sequence.
// Compile with -std=c++23.
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T> T byValue(T);                                       // declarations only: used inside decltype, never called
template <typename T> T& byRef(T&);
template <typename T> constexpr bool isLvalueArg(T&&) { return std::is_lvalue_reference_v<T>; }   // T = X& for lvalues

// alias template, variable template, template template parameter
template <typename T> using Table = std::map<std::string, std::vector<T>>;
template <typename T> constexpr T zero = T{};
template <template <typename...> class Container, typename T>
Container<T> makeTwo(T a, T b) { Container<T> c; c.push_back(a); c.push_back(b); return c; }

// std::index_sequence: expand a tuple into a call
template <typename F, typename Tuple, std::size_t... I>
auto applyImpl(F f, const Tuple& t, std::index_sequence<I...>) { return f(std::get<I>(t)...); }
template <typename F, typename Tuple>
auto applyTuple(F f, const Tuple& t) { return applyImpl(f, t, std::make_index_sequence<std::tuple_size_v<Tuple>>{}); }

// a user-defined deduction guide
template <typename T> struct Box { T value; };
template <typename T> Box(T) -> Box<T>;

int main()
{
    int i = 2;
    const int ci = 1;
    int arr[3] = {1, 2, 3};

    // by value: const and references are dropped; arrays decay to pointers
    static_assert(std::is_same_v<decltype(byValue(ci)), int>);
    static_assert(std::is_same_v<decltype(byValue(arr)), int*>);
    // by reference: the argument's constness is kept; arrays keep their size
    static_assert(std::is_same_v<decltype(byRef(ci)), const int&>);
    static_assert(std::is_same_v<decltype(byRef(arr)), int(&)[3]>);
    // forwarding reference: T records whether the argument was an lvalue
    std::cout << "forwarding reference deduces an lvalue for i: " << std::boolalpha << isLvalueArg(i)
              << ", for 5: " << isLvalueArg(5) << ", for std::move(i): " << isLvalueArg(std::move(i)) << '\n';
    std::cout << "by-value deduction dropped const and decayed the array (checked at compile time)\n";

    // class template argument deduction (C++17)
    std::pair p{1, 2.5};
    std::vector v{1, 2, 3};
    std::array a{1, 2, 3};
    Box b{std::string("x")};
    static_assert(std::is_same_v<decltype(p), std::pair<int, double>>);
    static_assert(std::is_same_v<decltype(v), std::vector<int>>);
    static_assert(std::is_same_v<decltype(a), std::array<int, 3>>);
    static_assert(std::is_same_v<decltype(b), Box<std::string>>);
    std::cout << "CTAD: pair<int,double>, vector<int>, array<int,3>, Box<string> deduced\n";

    Table<int> t;
    t["a"].push_back(1);
    static_assert(std::is_same_v<Table<int>, std::map<std::string, std::vector<int>>>);
    std::cout << "alias template Table<int> has " << t.size() << " key; zero<int> = " << zero<int> << ", zero<double> = " << zero<double> << '\n';

    auto two = makeTwo<std::vector>(3, 4);                                   // a template template argument
    std::cout << "makeTwo<std::vector>(3, 4) has " << two.size() << " elements\n";

    auto sum3 = [](int x, int y, int z) { return x + y + z; };
    std::cout << "applyTuple(sum3, tuple(1, 2, 3)) = " << applyTuple(sum3, std::tuple{1, 2, 3}) << '\n';
}
