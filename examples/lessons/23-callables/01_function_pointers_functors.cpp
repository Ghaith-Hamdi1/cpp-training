// Function Pointers and Functors: a function pointer, a functor, std::function holding each, std::invoke on a member
// function, std::bind next to the lambda that replaces it, and when std::function allocates (libstdc++ behaviour; the
// exact limit is implementation-defined). Compile with -std=c++23.
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <new>
#include <vector>

static int g_allocs = 0;                                          // counts calls to operator new
void* operator new(std::size_t n) { ++g_allocs; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

int twice(int x) { return 2 * x; }
bool descending(int a, int b) { return a > b; }
void apply(int (*op)(int), int x) { std::cout << op(x) << '\n'; }
struct GreaterThan { int limit; bool operator()(int x) const { return x > limit; } };
struct Times { int k; int operator()(int x) const { return x * k; } };
struct Account { int bal = 50; int balance() const { return bal; } };
int add3(int a, int b, int c) { return a * 100 + b * 10 + c; }

int main() {
    int (*f)(int) = twice;                                        // a function pointer
    std::cout << f(21) << ' ' << (*f)(21) << "   // both call twice\n";
    apply(twice, 21);

    std::vector<int> v{5, 2, 9, 1};
    std::sort(v.begin(), v.end(), descending);                    // the comparison is a function
    for (int x : v) std::cout << x << ' ';
    std::cout << "  // 9 5 2 1\n";

    GreaterThan gt{4};                                            // a functor with state
    std::cout << gt(5) << gt(3) << ' ' << std::count_if(v.begin(), v.end(), GreaterThan{1}) << "   // 10 3\n";
    std::sort(v.begin(), v.end(), std::greater<>{});              // a standard functor
    std::cout << "largest first: " << v.front() << '\n';

    std::function<int(int)> g = twice;                            // one type, three kinds of callable
    std::cout << g(10) << ' ';
    g = Times{3};
    std::cout << g(10) << ' ';
    g = [](int x) { return x + 1; };
    std::cout << g(10) << "   // 20 30 11\n";

    Account acct;
    std::cout << "std::invoke on a member function: " << std::invoke(&Account::balance, acct) << '\n';

    using namespace std::placeholders;
    auto b1 = std::bind(add3, 1, _1, _2);
    auto l1 = [](int b, int c) { return add3(1, b, c); };
    std::cout << "bind: " << b1(2, 3) << ", lambda: " << l1(2, 3) << "   // both 123\n";

    int before = g_allocs;
    { int a = 1; std::function<int()> small = [a] { return a; }; (void)small; }
    int smallAllocs = g_allocs - before;
    before = g_allocs;
    { char big[64] = {1}; std::function<int()> large = [big] { return big[0]; }; (void)large; }
    std::cout << "heap allocations: small capture " << smallAllocs << ", 64-byte capture " << (g_allocs - before) << '\n';
}
