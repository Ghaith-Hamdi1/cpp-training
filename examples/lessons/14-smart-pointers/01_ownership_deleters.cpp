// Lesson 8: unique_ptr (moves, custom deleter, arrays), shared_ptr counting, a reference cycle that leaks and the
// weak_ptr fix, enable_shared_from_this, and passing smart pointers. Compile with -std=c++20.
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Widget {
    static inline int alive = 0;
    std::string name;
    explicit Widget(std::string n) : name(std::move(n)) { ++alive; }
    ~Widget() { --alive; }
};

std::unique_ptr<Widget> makeWidget(std::string n) { return std::make_unique<Widget>(std::move(n)); }   // factory: sole ownership
void use(const Widget& w) { std::cout << "  using " << w.name << '\n'; }                                // just uses: takes a reference
void take(std::unique_ptr<Widget> w) { std::cout << "  took ownership of " << w->name << '\n'; }         // takes ownership: by value

struct Node;
struct Owner  { std::shared_ptr<Node> child; static inline int alive = 0; Owner() { ++alive; } ~Owner() { --alive; } };
struct Node   { std::shared_ptr<Owner> parent;  static inline int alive = 0; Node() { ++alive; } ~Node() { --alive; } };       // cycle
struct OwnerW;
struct WNode  { std::weak_ptr<OwnerW> parent;   static inline int alive = 0; WNode() { ++alive; } ~WNode() { --alive; } };       // fixed: weak back-pointer
struct OwnerW { std::shared_ptr<WNode> child; static inline int alive = 0; OwnerW() { ++alive; } ~OwnerW() { --alive; } };

struct Session : std::enable_shared_from_this<Session> {
    std::shared_ptr<Session> self() { return shared_from_this(); }   // a safe second owner, SAME control block
};

int main()
{
    {
        auto w = makeWidget("alpha");
        use(*w);                                                    // pass the object, not the owner
        take(std::move(w));                                         // ownership moves; w is now null
        std::cout << "after take: w is " << (w ? "set" : "null") << ", widgets alive " << Widget::alive << '\n';
    }

    {
        auto closer = [](std::FILE* f) { std::cout << "  deleter: closing the file\n"; std::fclose(f); };
        std::unique_ptr<std::FILE, decltype(closer)> file(std::fopen("smartptr_demo.tmp", "w"), closer);   // custom deleter
        std::fputs("hello", file.get());
    }                                                               // closed here, automatically
    std::remove("smartptr_demo.tmp");

    auto arr = std::make_unique<int[]>(3);                          // unique_ptr<T[]> uses delete[]
    arr[0] = 1; arr[2] = 3;
    std::cout << "array element 2: " << arr[2] << '\n';

    auto s1 = std::make_shared<Widget>("shared");
    auto s2 = s1;
    std::weak_ptr<Widget> weak = s1;
    std::cout << "use_count " << s1.use_count() << " (weak_ptr does not count), expired: " << std::boolalpha << weak.expired() << '\n';
    s1.reset(); s2.reset();
    std::cout << "after both owners reset: expired " << weak.expired() << ", lock() is " << (weak.lock() ? "set" : "null") << '\n';

    {
        auto o = std::make_shared<Owner>();
        o->child = std::make_shared<Node>();
        o->child->parent = o;                                       // shared in both directions: a cycle
    }
    std::cout << "cycle with shared_ptr both ways, after the scope: Owner alive " << Owner::alive << ", Node alive " << Node::alive << "   <- leaked\n";
    {
        auto o = std::make_shared<OwnerW>();
        o->child = std::make_shared<WNode>();
        o->child->parent = o;                                       // weak: does not keep the owner alive
    }
    std::cout << "with a weak back-pointer: OwnerW alive " << OwnerW::alive << ", WNode alive " << WNode::alive << '\n';

    auto sess = std::make_shared<Session>();
    auto again = sess->self();
    std::cout << "shared_from_this: use_count " << sess.use_count() << '\n';
    try {
        Session onStack;
        onStack.self();                                             // not owned by any shared_ptr
    } catch (const std::bad_weak_ptr&) {
        std::cout << "shared_from_this on an object no shared_ptr owns throws bad_weak_ptr\n";
    }
}
