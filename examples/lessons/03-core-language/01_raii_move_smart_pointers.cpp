// Lesson 5: RAII with stack unwinding, std::move traps, unique_ptr / shared_ptr / weak_ptr, cycles.
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

struct File {                                          // RAII: acquire in the ctor, release in the dtor
    explicit File(const char* n) : name(n) { std::cout << "open " << name << '\n'; }
    ~File() { std::cout << "close " << name << '\n'; }
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    std::string name;
};

void work() {
    File f("data.txt");
    throw std::runtime_error("risky() failed");        // f is still closed: stack unwinding
}

struct Node {
    std::shared_ptr<Node> child;
    std::weak_ptr<Node> parent;                        // weak back-link: no ownership cycle
    ~Node() { std::cout << "Node destroyed\n"; }
};

int main() {
    try { work(); } catch (const std::exception& e) { std::cout << "caught: " << e.what() << '\n'; }

    // std::move on a const object COPIES: a const rvalue cannot bind to the move constructor
    const std::string cs = "abc";
    std::string t1 = std::move(cs);
    std::cout << "after moving a const string, source still = \"" << cs << "\"\n";
    std::string s = "abc";
    std::string t2 = std::move(s);
    std::cout << "after moving a non-const string, source size = " << s.size() << " (valid but unspecified)\n";

    auto p = std::make_unique<File>("unique.txt");
    // auto q = p;                                      // ERROR: unique_ptr cannot be copied
    auto q = std::move(p);                              // ownership moves, p is now null
    std::cout << "p is " << (p ? "set" : "null") << ", q is " << (q ? "set" : "null") << '\n';
    q.reset();                                          // closes the file now

    auto s1 = std::make_shared<int>(2);
    auto s2 = s1;
    std::weak_ptr<int> w = s1;
    std::cout << "use_count = " << s1.use_count() << " (weak_ptr does not add to it)\n";
    s1.reset(); s2.reset();
    std::cout << "w expired: " << std::boolalpha << w.expired() << '\n';
    if (auto sp = w.lock()) std::cout << "still alive\n"; else std::cout << "lock() gave null\n";

    {
        auto parent = std::make_shared<Node>();
        parent->child = std::make_shared<Node>();
        parent->child->parent = parent;                 // weak: both Nodes are destroyed at the end of this block
    }
    (void)t1; (void)t2;
}
