// Exercise 12: write a class template.
//
// Stack<T> is a LIFO stack of any type T, stored in a std::vector<T>:
//   void push(T value)          add on top (take the value BY VALUE and move it in, so move-only
//                               types such as unique_ptr work)
//   bool tryPop(T& out)         if not empty: move the top element into out, remove it, return true;
//                               if empty: return false and leave out alone
//   const T& top() const        the top element (precondition: not empty)
//   bool empty() const
//   std::size_t size() const
// Hints: this is a template, so the whole definition lives in the file you include, not in a .cpp.
#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../check.h"

template <typename T>
class Stack {
public:
    void push(T value) { (void)value; }                // TODO
    bool tryPop(T& out) { (void)out; return false; }   // TODO
    const T& top() const { static T dummy{}; return dummy; }   // TODO
    bool empty() const { return true; }                // TODO
    std::size_t size() const { return 0; }             // TODO
};

int main()
{
    Stack<int> s;
    CHECK(s.empty() && s.size() == 0);
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK(!s.empty() && s.size() == 3 && s.top() == 3);
    int v = 0;
    CHECK(s.tryPop(v) && v == 3);
    CHECK(s.tryPop(v) && v == 2);
    CHECK(s.tryPop(v) && v == 1);
    CHECK(!s.tryPop(v) && v == 1);                     // empty: false, out untouched
    CHECK(s.empty());

    Stack<std::string> names;
    names.push("alpha");
    names.push(std::string("beta"));
    std::string out;
    CHECK(names.tryPop(out) && out == "beta");
    CHECK(names.top() == "alpha");

    Stack<std::unique_ptr<int>> owners;                // a move-only element type
    owners.push(std::make_unique<int>(42));
    std::unique_ptr<int> p;
    CHECK(owners.tryPop(p) && p != nullptr && *p == 42);
    CHECK(owners.empty());
    return finish("12 Stack<T>");
}
