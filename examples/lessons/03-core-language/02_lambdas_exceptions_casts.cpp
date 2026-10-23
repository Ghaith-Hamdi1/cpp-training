// Lesson 9: lambda captures, exceptions and catch order, named casts, constexpr, std::optional / variant / string_view.
#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

struct Animal { virtual ~Animal() = default; };
struct Dog : Animal { void fetch() const { std::cout << "fetch!\n"; } };
struct Cat : Animal {};

double divide(double a, double b) {
    if (b == 0) throw std::invalid_argument("division by zero");
    return a / b;
}

constexpr int square(int x) { return x * x; }

std::optional<int> parse(const std::string& s) {
    try { return std::stoi(s); } catch (...) { return std::nullopt; }
}

int main() {
    int x = 1;
    auto byVal = [x] { return x; };                     // snapshot taken now
    auto byRef = [&x] { return x; };                    // sees the live variable
    x = 2;
    std::cout << byVal() << byRef() << "   // 12\n";

    std::vector<int> v{5, 2, 9, 1};
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
    for (int n : v) std::cout << n << ' ';
    std::cout << "  // descending\n";

    try { divide(1, 0); }
    catch (const std::invalid_argument& e) { std::cout << "specific handler: " << e.what() << '\n'; }
    catch (const std::exception& e) { std::cout << "general handler: " << e.what() << '\n'; }

    double avg = static_cast<double>(7) / 2;            // avoids integer division
    std::cout << "avg = " << avg << '\n';
    Animal* a = new Dog;
    if (auto* d = dynamic_cast<Dog*>(a)) d->fetch();    // checked downcast
    if (!dynamic_cast<Cat*>(a)) std::cout << "not a Cat: dynamic_cast gave null\n";
    delete a;

    constexpr int n = square(4);                        // computed at compile time
    static_assert(n == 16);
    int arr[square(3)];                                 // array of 9: needs a constant expression
    std::cout << "n = " << n << ", sizeof(arr)/sizeof(int) = " << sizeof(arr) / sizeof(int) << '\n';

    if (auto r = parse("42")) std::cout << "parsed " << *r << '\n';
    if (!parse("abc")) std::cout << "\"abc\" is not a number\n";

    std::variant<int, std::string> var = "hi";
    std::visit([](auto&& val) { std::cout << "variant holds " << val << '\n'; }, var);

    std::string_view sv = "hello world";               // non-owning view of a literal: safe
    std::cout << sv.substr(6) << '\n';
}
