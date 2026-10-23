// Chapter 22 - Project 08: std::shared_ptr
// std::shared_ptr enables multiple pointers to co-own a resource via
// reference counting.  The resource is freed when the LAST shared_ptr
// owning it is destroyed.
//
// Key points:
//   - Use std::make_shared<T>(args) - one allocation for object + control block.
//   - Create additional shared_ptrs by COPYING an existing one (never from
//     the same raw pointer independently).
//   - A unique_ptr can be converted to shared_ptr, but NOT the reverse.
//   - use_count() returns the current reference count (for debugging only).

#include <iostream>
#include <memory> // std::shared_ptr, std::make_shared
#include <string>

// -----------------------------------------------------------------------
// Resource class to observe lifetimes
// -----------------------------------------------------------------------
class Widget
{
    std::string m_name;

public:
    explicit Widget(const std::string &name) : m_name{name}
    {
        std::cout << "  [Widget] \"" << m_name << "\" constructed\n";
    }

    ~Widget()
    {
        std::cout << "  [Widget] \"" << m_name << "\" destroyed\n";
    }

    const std::string &name() const { return m_name; }
};

// -----------------------------------------------------------------------
// 1. Basic shared ownership
// -----------------------------------------------------------------------
void basicSharedOwnership()
{
    std::cout << "=== 1. Shared ownership ===\n";

    // Create a shared_ptr with make_shared (preferred)
    auto sp1 = std::make_shared<Widget>("Alpha");
    std::cout << "  sp1 use_count = " << sp1.use_count() << '\n'; // 1

    {
        // Copy sp1 - both now share ownership
        auto sp2 = sp1;
        std::cout << "  sp1 use_count = " << sp1.use_count() << '\n'; // 2
        std::cout << "  sp2 use_count = " << sp2.use_count() << '\n'; // 2

        std::cout << "  sp2 going out of scope...\n";
    }
    // sp2 is destroyed, but Widget lives on - sp1 still owns it
    std::cout << "  sp1 use_count = " << sp1.use_count() << '\n'; // 1
    std::cout << "  sp1 going out of scope...\n";
    // Widget is destroyed here when sp1 is destroyed (count reaches 0)
}

// -----------------------------------------------------------------------
// 2. Sharing across functions
// -----------------------------------------------------------------------
void useWidget(std::shared_ptr<Widget> w) // receives shared ownership
{
    std::cout << "  useWidget: \"" << w->name()
              << "\" (use_count = " << w.use_count() << ")\n";
    // w is destroyed when function returns, decrementing count
}

void sharingAcrossFunctions()
{
    std::cout << "\n=== 2. Sharing across functions ===\n";

    auto sp = std::make_shared<Widget>("Beta");
    std::cout << "  Before call: use_count = " << sp.use_count() << '\n'; // 1

    useWidget(sp); // Copies sp into parameter - count goes to 2, then back to 1

    std::cout << "  After call:  use_count = " << sp.use_count() << '\n'; // 1
}

// -----------------------------------------------------------------------
// 3. Converting unique_ptr to shared_ptr
// -----------------------------------------------------------------------
void uniqueToShared()
{
    std::cout << "\n=== 3. unique_ptr → shared_ptr ===\n";

    auto uptr = std::make_unique<Widget>("Gamma");
    std::cout << "  unique_ptr owns \"" << uptr->name() << "\"\n";

    // Move unique_ptr into shared_ptr - unique_ptr becomes null
    std::shared_ptr<Widget> sptr = std::move(uptr);

    std::cout << "  unique_ptr is now " << (uptr ? "not null" : "null") << '\n';
    std::cout << "  shared_ptr owns \"" << sptr->name()
              << "\" (use_count = " << sptr.use_count() << ")\n";
}

// -----------------------------------------------------------------------
// 4. make_shared vs raw new (why make_shared is better)
// -----------------------------------------------------------------------
void makeSharedAdvantage()
{
    std::cout << "\n=== 4. make_shared vs new ===\n";

    // BAD: Two separate allocations (object + control block)
    // Also has exception-safety issues in complex expressions.
    // std::shared_ptr<Widget> sp1(new Widget("raw-new"));

    // GOOD: Single allocation for object + control block
    auto sp2 = std::make_shared<Widget>("make_shared");

    std::cout << "  Use make_shared - one allocation, exception-safe\n";
}

// -----------------------------------------------------------------------
// 5. reset() and null checks
// -----------------------------------------------------------------------
void resetDemo()
{
    std::cout << "\n=== 5. reset() and null checks ===\n";

    auto sp1 = std::make_shared<Widget>("Delta");
    auto sp2 = sp1;

    std::cout << "  Before reset: use_count = " << sp1.use_count() << '\n'; // 2

    sp1.reset(); // sp1 releases ownership, count drops to 1
    std::cout << "  sp1 is " << (sp1 ? "not null" : "null") << '\n';
    std::cout << "  sp2 use_count = " << sp2.use_count() << '\n'; // 1

    sp2.reset(); // count drops to 0 - Widget is destroyed
    std::cout << "  sp2 is " << (sp2 ? "not null" : "null") << '\n';
}

// -----------------------------------------------------------------------
int main()
{
    basicSharedOwnership();
    sharingAcrossFunctions();
    uniqueToShared();
    makeSharedAdvantage();
    resetDemo();

    std::cout << "\nDone.\n";
    return 0;
}
