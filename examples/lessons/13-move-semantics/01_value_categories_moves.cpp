// Lesson 7: value categories, what std::move really does, counting copies and moves, copy elision, moved-from objects,
// std::exchange and the sink-parameter idiom. Compile with -std=c++23.
#pragma GCC diagnostic ignored "-Wpessimizing-move"   // deliberate: makeWithMove shows the mistake
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

struct Counter {                                                  // counts how it was created
    static inline int copies = 0, moves = 0;
    static void reset() { copies = moves = 0; }
    Counter() = default;
    Counter(const Counter&) { ++copies; }
    Counter(Counter&&) noexcept { ++moves; }
    Counter& operator=(const Counter&) { ++copies; return *this; }
    Counter& operator=(Counter&&) noexcept { ++moves; return *this; }
};

Counter makeTemporary() { return Counter(); }                     // returns a prvalue
Counter makeNamed() { Counter c; return c; }                      // returns a named local (NRVO may apply)
Counter makeWithMove() { Counter c; return std::move(c); }        // the pessimising mistake: blocks NRVO

Counter passThrough(Counter c) { return c; }                      // returning a by-value PARAMETER: implicitly moved
struct Source { Counter m; Counter getCopy() { return m; } Counter takeMember() { return std::move(m); } };

void sinkByValue(Counter c) { (void)c; }                          // "I will keep it": take by value
struct Holder { Counter c; explicit Holder(Counter x) : c(std::move(x)) {} };   // sink parameter, then move into the member

class Buffer {
    int* data_;
    std::size_t n_;
public:
    explicit Buffer(std::size_t n) : data_(new int[n]()), n_(n) {}
    ~Buffer() { delete[] data_; }
    Buffer(const Buffer& o) : data_(new int[o.n_]), n_(o.n_) { for (std::size_t i = 0; i < n_; ++i) data_[i] = o.data_[i]; }
    Buffer(Buffer&& o) noexcept : data_(std::exchange(o.data_, nullptr)), n_(std::exchange(o.n_, 0)) {}   // steal and reset
    Buffer& operator=(Buffer o) noexcept { std::swap(data_, o.data_); std::swap(n_, o.n_); return *this; }   // copy-and-swap: by value
    std::size_t size() const { return n_; }
};

int main()
{
    // value categories: decltype((expr)) with double parentheses reports the category
    int x = 0;
    static_assert(std::is_same_v<decltype((x)), int&>);                              // lvalue
    static_assert(std::is_same_v<decltype((std::move(x))), int&&>);                  // xvalue
    static_assert(std::is_same_v<decltype((x + 1)), int>);                           // prvalue
    std::cout << "x is an lvalue, std::move(x) an xvalue, x + 1 a prvalue (checked at compile time)\n";

    Counter::reset();
    Counter a;
    [[maybe_unused]] Counter b = a;                                                // lvalue: copy
    [[maybe_unused]] Counter c = std::move(a);                                     // cast to rvalue: move
    std::cout << "copy then move: copies " << Counter::copies << ", moves " << Counter::moves << '\n';

    Counter::reset();
    const Counter k;
    [[maybe_unused]] Counter d = std::move(k);                                     // const rvalue cannot bind to Counter&&: COPIES
    std::cout << "std::move on a const object: copies " << Counter::copies << ", moves " << Counter::moves << '\n';

    Counter::reset();
    [[maybe_unused]] Counter e = makeTemporary();
    std::cout << "return prvalue (guaranteed elision, C++17): copies " << Counter::copies << ", moves " << Counter::moves << '\n';
    Counter::reset();
    [[maybe_unused]] Counter f = makeNamed();
    std::cout << "return named local (NRVO, allowed not required): copies " << Counter::copies << ", moves " << Counter::moves << '\n';
    Counter::reset();
    [[maybe_unused]] Counter g = makeWithMove();
    std::cout << "return std::move(local): copies " << Counter::copies << ", moves " << Counter::moves << "   <- the extra move is the mistake\n";

    Counter::reset();
    [[maybe_unused]] Counter pt = passThrough(Counter());
    std::cout << "return a by-value parameter: copies " << Counter::copies << ", moves " << Counter::moves << "   (no elision for parameters, but it is moved, not copied)\n";
    Counter::reset();
    Source src;
    [[maybe_unused]] Counter m1 = src.getCopy();
    [[maybe_unused]] Counter m2 = src.takeMember();
    std::cout << "return a member: copies " << Counter::copies << ", with std::move: moves " << Counter::moves << "   (a member is never moved implicitly)\n";

    Counter::reset();
    Counter lv;
    sinkByValue(lv);                                              // lvalue: one copy into the parameter
    sinkByValue(Counter());                                       // rvalue: constructed in place, no copy or move
    std::cout << "sink by value, lvalue then rvalue: copies " << Counter::copies << ", moves " << Counter::moves << '\n';
    Counter::reset();
    Holder h1(lv);                                                // copy into the parameter, then move into the member
    Holder h2(Counter{});                                         // temporary: only the move into the member
    std::cout << "Holder(lvalue), Holder(rvalue): copies " << Counter::copies << ", moves " << Counter::moves << '\n';

    std::string s = "hello";
    std::string t = std::move(s);
    std::cout << "moved-from string: size " << s.size() << " (valid but unspecified; usually empty), moved-to: " << t << '\n';
    s = "reassigned";                                             // a moved-from object may always be assigned to
    std::cout << "after assigning a new value: " << s << '\n';

    Buffer big(1000);
    Buffer moved = std::move(big);
    std::cout << "Buffer moved: new size " << moved.size() << ", old size " << big.size() << '\n';
    Buffer copy = moved;                                          // copy-and-swap assignment also works for copies
    Buffer other(5);
    other = copy;
    std::cout << "after other = copy: " << other.size() << '\n';

    std::vector<Counter> v;
    v.reserve(4);
    Counter::reset();
    Counter lv2;
    v.push_back(lv2);                                             // copy
    v.push_back(Counter());                                       // move
    v.emplace_back();                                             // constructed in place: neither
    std::cout << "push_back(lvalue), push_back(temp), emplace_back(): copies " << Counter::copies << ", moves " << Counter::moves << '\n';
}
