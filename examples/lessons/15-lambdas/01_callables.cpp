// Lesson 8: function pointers, functors, lambdas and std::function side by side; captures, init-capture, mutable,
// generic and recursive lambdas, std::invoke, and when std::function allocates (libstdc++ behaviour; the exact limit is
// implementation-defined). Compile with -std=c++20.
#include <array>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <new>
#include <vector>

static int g_allocations = 0;
void* operator new(std::size_t n) { ++g_allocations; if (void* p = std::malloc(n)) return p; throw std::bad_alloc(); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }

int addOne(int x) { return x + 1; }                              // a plain function
struct AddN { int n; int operator()(int x) const { return x + n; } };   // a functor: an object with operator()

template <typename F>
int applyTwice(F f, int x) { return f(f(x)); }                    // a template: the callable's exact type is known, so it can inline

int applyTwiceErased(const std::function<int(int)>& f, int x) { return f(f(x)); }   // type-erased: one function for any callable

struct Counter { int base = 10; int plus(int x) const { return base + x; } };

int main()
{
    int factor = 3;
    auto lam = [factor](int x) { return x * factor; };            // a lambda: a compiler-made functor holding factor

    std::cout << "function pointer: " << applyTwice(addOne, 1) << ", functor: " << applyTwice(AddN{5}, 1)
              << ", lambda: " << applyTwice(lam, 1) << ", std::function: " << applyTwiceErased(lam, 1) << '\n';

    auto stateless = [](int x) { return x + 1; };
    int (*fp)(int) = stateless;                                   // a lambda with no captures converts to a function pointer
    std::cout << "stateless lambda as function pointer: " << fp(1) << '\n';
    std::cout << "sizeof: stateless lambda " << sizeof(stateless) << ", lambda capturing an int " << sizeof(lam)
              << ", function pointer " << sizeof(fp) << '\n';

    auto counter = [n = 0]() mutable { return ++n; };             // init-capture + mutable: the lambda owns changing state
    std::cout << "mutable lambda: " << counter() << counter() << counter() << '\n';

    auto owned = std::make_unique<int>(41);
    auto movedIn = [p = std::move(owned)] { return *p + 1; };     // C++14 init-capture: MOVE a move-only object into the lambda
    std::cout << "unique_ptr moved into a lambda: " << movedIn() << ", original is " << (owned ? "set" : "null") << '\n';

    auto generic = [](const auto& a, const auto& b) { return a < b ? b : a; };   // C++14 generic lambda: a template in disguise
    std::cout << "generic lambda: max(3, 7) = " << generic(3, 7) << ", max(2.5, 1.5) = " << generic(2.5, 1.5) << '\n';

    auto fact = [](auto self, int n) -> int { return n <= 1 ? 1 : n * self(self, n - 1); };   // recursion without std::function
    std::cout << "recursive lambda: 5! = " << fact(fact, 5) << '\n';

    const int limit = [] { int s = 0; for (int i = 1; i <= 4; ++i) s += i; return s; }();       // immediately invoked: const init
    std::cout << "immediately-invoked lambda: " << limit << '\n';

    Counter c;
    std::cout << "std::invoke with a member function pointer: " << std::invoke(&Counter::plus, c, 5) << '\n';

    std::vector<std::function<int(int)>> handlers{addOne, AddN{100}, lam};   // different callables, one type
    int sum = 0;
    for (auto& h : handlers) sum += h(1);
    std::cout << "std::function in a vector: " << sum << '\n';

    int before = g_allocations;
    std::function<int(int)> small = [factor](int x) { return x * factor; };
    int smallAllocs = g_allocations - before;
    before = g_allocations;
    std::array<int, 16> big{};
    std::function<int(int)> large = [big](int x) { return x + big[0]; };                       // a 64-byte capture
    int largeAllocs = g_allocations - before;
    std::cout << "std::function with a small capture allocates: " << (smallAllocs > 0 ? "yes" : "no")
              << "; with a 64-byte capture: " << (largeAllocs > 0 ? "yes" : "no") << " (libstdc++)\n";
    std::cout << small(2) << ' ' << large(2) << '\n';
}
