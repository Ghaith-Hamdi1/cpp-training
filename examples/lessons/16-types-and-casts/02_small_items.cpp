// Small items from several lessons: std::bind (lesson 10), <random> (lesson 13), user-defined literals (lesson 5),
// extern "C" (lesson 3) and placement new (lesson 4). Compile with -std=c++20.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <new>
#include <random>
#include <string>
#include <vector>

// user-defined literals
constexpr long long operator""_ticks(unsigned long long v) { return static_cast<long long>(v) * 25; }   // one tick = 25 units
constexpr double operator""_bp(long double v) { return static_cast<double>(v) / 10000.0; }              // basis points
std::string operator""_s(const char* s, std::size_t n) { return std::string(s, n); }

// extern "C": a function with C linkage can be passed to C APIs and called from C code
extern "C" int compareInts(const void* a, const void* b) {
    int x = *static_cast<const int*>(a), y = *static_cast<const int*>(b);
    return (x > y) - (x < y);
}

struct Order { int qty; Order(int q) : qty(q) { std::cout << "Order(" << q << ") constructed in place\n"; } ~Order() { std::cout << "~Order(" << qty << ")\n"; } };

int add3(int a, int b, int c) { return a * 100 + b * 10 + c; }

int main()
{
    using namespace std::placeholders;
    auto f = std::bind(add3, 1, _1, _2);                               // fix the first argument, leave two open
    auto g = std::bind(add3, _2, _1, 9);                               // reorder the arguments
    std::cout << "bind(add3, 1, _1, _2)(2, 3) = " << f(2, 3) << ", bind(add3, _2, _1, 9)(4, 5) = " << g(4, 5) << '\n';
    auto lam = [](int b, int c) { return add3(1, b, c); };             // the lambda says the same thing, more readably
    std::cout << "equivalent lambda gives " << lam(2, 3) << '\n';

    std::mt19937 gen(12345);                                           // a seeded engine is deterministic: the same numbers every run
    std::uniform_int_distribution<int> dice(1, 6);
    int a = dice(gen), b = dice(gen);
    std::mt19937 gen2(12345);
    std::uniform_int_distribution<int> dice2(1, 6);
    std::cout << "same seed, same sequence: " << std::boolalpha << (a == dice2(gen2) && b == dice2(gen2)) << ", values in 1..6: " << (a >= 1 && a <= 6) << '\n';
    int count[6] = {};
    for (int i = 0; i < 6000; ++i) ++count[dice(gen) - 1];
    bool near = true;
    for (int c : count) if (c < 850 || c > 1150) near = false;
    std::cout << "6000 rolls, every face within 850..1150 times: " << near << '\n';
    std::normal_distribution<double> nd(0.0, 1.0);
    double sum = 0; for (int i = 0; i < 10000; ++i) sum += nd(gen);
    std::cout << "10000 normal samples have mean near 0: " << (std::abs(sum / 10000) < 0.05) << '\n';

    std::cout << "literals: 4_ticks = " << 4_ticks << ", 25.0_bp = " << 25.0_bp << ", \"abc\"_s has size " << "abc"_s.size() << '\n';

    int arr[] = {5, 1, 4, 2, 3};
    std::qsort(arr, 5, sizeof(int), compareInts);                      // a C API taking a C-linkage callback
    std::cout << "qsort with an extern \"C\" comparator: " << arr[0] << arr[1] << arr[2] << arr[3] << arr[4] << '\n';

    alignas(Order) unsigned char storage[sizeof(Order)];               // raw memory, no object yet
    Order* o = new (storage) Order(7);                                 // placement new: construct INTO this memory, no allocation
    std::cout << "object lives at the storage address: " << (static_cast<void*>(o) == static_cast<void*>(storage)) << '\n';
    o->~Order();                                                       // we must call the destructor ourselves; no delete
}
