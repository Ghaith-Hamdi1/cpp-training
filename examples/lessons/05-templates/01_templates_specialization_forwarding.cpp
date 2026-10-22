// Lesson 11: function/class templates, specialization, forwarding references and perfect forwarding, variadics, fold expressions.
#include <iostream>
#include <memory>
#include <string>
#include <utility>

template <typename T>
T maxOf(T a, T b) { return a < b ? b : a; }

template <typename T, std::size_t Capacity = 8>         // type parameter + non-type parameter with a default
class Stack {
    T items_[Capacity];
    std::size_t size_ = 0;
public:
    bool push(const T& v) { if (size_ == Capacity) return false; items_[size_++] = v; return true; }
    T pop() { return items_[--size_]; }
    bool empty() const { return size_ == 0; }
};

template <typename T>
struct Printer {                                        // primary template
    static void print(const T& v) { std::cout << "generic: " << v << '\n'; }
};
template <>
struct Printer<bool> {                                  // full specialization
    static void print(bool v) { std::cout << "bool: " << (v ? "yes" : "no") << '\n'; }
};
template <typename T>
struct Printer<T*> {                                    // partial specialization: any pointer
    static void print(T* p) { std::cout << "pointer to " << *p << '\n'; }
};

struct Widget {
    explicit Widget(const std::string& s) { std::cout << "  Widget copied its argument: " << s << '\n'; }
    explicit Widget(std::string&& s) { std::cout << "  Widget MOVED its argument: " << s << '\n'; }
};

template <typename T, typename... Args>
std::unique_ptr<T> makeUnique(Args&&... args) {         // forwarding references
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));   // lvalues stay lvalues, rvalues stay rvalues
}

template <typename... Args>
auto sum(Args... args) { return (args + ...); }         // unary right fold

template <typename... Args>
void print(Args&&... args) { ((std::cout << args << ' '), ...); std::cout << '\n'; }   // comma fold

template <typename T>
T recSum(T v) { return v; }                             // pre-C++17 recursion: base case...
template <typename T, typename... Rest>
T recSum(T first, Rest... rest) { return first + recSum(rest...); }   // ...and peel one off

int main() {
    std::cout << maxOf(3, 7) << ' ' << maxOf(2.5, 1.5) << ' ' << maxOf<double>(3, 2.5) << '\n';
    // maxOf(3, 2.5);                                   // ERROR: T deduced as int and double

    Stack<int> a;                                       // Stack<int, 8>
    Stack<std::string, 100> b;                          // a different, unrelated type
    a.push(1); a.push(2);
    b.push("x");
    std::cout << "popped " << a.pop() << ", a.empty() = " << std::boolalpha << a.empty() << '\n';

    int n = 5;
    Printer<int>::print(1);
    Printer<bool>::print(true);
    Printer<int*>::print(&n);

    std::string s = "abc";
    std::cout << "makeUnique(lvalue):\n";
    auto w1 = makeUnique<Widget>(s);                    // s is an lvalue  -> copy
    std::cout << "makeUnique(temporary):\n";
    auto w2 = makeUnique<Widget>(std::string("xyz"));   // rvalue          -> move

    std::cout << "sum(1,2,3) = " << sum(1, 2, 3) << ", recSum(1,2,3) = " << recSum(1, 2, 3) << '\n';
    print(1, "two", 3.5);
}
