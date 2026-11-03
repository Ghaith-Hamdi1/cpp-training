// unique_ptr: Exclusive Ownership: the object is freed at the closing brace, ownership moves but never copies, passing and
// returning, a vector of unique_ptrs, a Derived behind a unique_ptr<Base>, sizes with different deleters, release and reset.
// Compile with -std=c++23.
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct Widget {
    int id; std::string name;
    Widget(int i, std::string n) : id(i), name(std::move(n)) { std::cout << "Widget(" << id << ") built\n"; }
    ~Widget() { std::cout << "Widget(" << id << ") destroyed\n"; }
};
std::unique_ptr<Widget> makeWidget(int id) { return std::make_unique<Widget>(id, "w"); }
void use(const Widget& w) { std::cout << "using " << w.id << '\n'; }
void take(std::unique_ptr<Widget> w) { std::cout << "took " << w->id << '\n'; }   // destroyed at the closing brace

struct Base { virtual ~Base() = default; virtual const char* who() const { return "Base"; } };
struct Derived : Base { const char* who() const override { return "Derived"; } };

int main() {
    {
        auto p = std::make_unique<Widget>(1, "a");
        std::cout << "in scope\n";
    }                                                           // Widget(1) destroyed here
    std::cout << "after scope\n";

    auto a = std::make_unique<Widget>(2, "b");
    auto b = std::move(a);                                      // ownership moves
    std::cout << "a is " << (a ? "set" : "null") << ", b is " << (b ? "set" : "null") << '\n';

    auto w = makeWidget(3);
    use(*w);
    take(std::move(w));
    std::cout << "w is " << (w ? "set" : "null") << '\n';

    std::vector<std::unique_ptr<Widget>> v;
    v.push_back(std::make_unique<Widget>(4, "v"));
    v.push_back(makeWidget(5));
    std::cout << "vector holds " << v.size() << '\n';
    v.clear();

    std::unique_ptr<Base> base = std::make_unique<Derived>();
    std::cout << base->who() << '\n';

    auto closer = [](std::FILE* f) { if (f) std::fclose(f); };
    std::cout << sizeof(std::unique_ptr<int>) << ' ' << sizeof(int*) << ' '
              << sizeof(std::unique_ptr<std::FILE, decltype(closer)>) << ' '
              << sizeof(std::unique_ptr<std::FILE, void (*)(std::FILE*)>) << '\n';   // 8 8 8 16
    auto arr = std::make_unique<int[]>(3);
    arr[0] = 7;
    std::cout << arr[0] << arr[1] << '\n';                      // 70 (value-initialized)

    auto r = std::make_unique<Widget>(6, "r");
    Widget* raw = r.release();                                  // we own it now
    std::cout << "released, r is " << (r ? "set" : "null") << '\n';
    delete raw;
    auto s = std::make_unique<Widget>(7, "s");
    s.reset();                                                  // destroyed now
    std::cout << "reset done\n";
}
