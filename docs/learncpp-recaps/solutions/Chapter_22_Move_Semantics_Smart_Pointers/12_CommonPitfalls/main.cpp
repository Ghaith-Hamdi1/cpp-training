// Chapter 22 - Project 12: Common Pitfalls
// This file demonstrates the most frequent mistakes with smart pointers
// and move semantics, and shows how to avoid them.

#include <iostream>
#include <memory>
#include <string>
#include <utility>

// -----------------------------------------------------------------------
// Pitfall 1: Two independent shared_ptrs from the same raw pointer
// -----------------------------------------------------------------------
// WRONG: Each shared_ptr gets its own reference count → double delete!
//
//   Widget* raw = new Widget();
//   std::shared_ptr<Widget> sp1(raw);
//   std::shared_ptr<Widget> sp2(raw);  // BUG: separate control block!
//
// CORRECT: Always copy an existing shared_ptr:
//   auto sp1 = std::make_shared<Widget>();
//   auto sp2 = sp1;   // copies the control block - same ref count.

class Widget
{
    std::string m_name;

public:
    explicit Widget(const std::string &n) : m_name{n}
    {
        std::cout << "  [Widget] \"" << m_name << "\" created\n";
    }
    ~Widget() { std::cout << "  [Widget] \"" << m_name << "\" destroyed\n"; }
    const std::string &name() const { return m_name; }
};

void pitfall1_correctUsage()
{
    std::cout << "=== Pitfall 1: shared_ptr from same raw pointer ===\n";
    std::cout << "  CORRECT: copy an existing shared_ptr\n";

    auto sp1 = std::make_shared<Widget>("Shared");
    auto sp2 = sp1; // Both share the same control block
    std::cout << "  use_count = " << sp1.use_count() << " (should be 2)\n";
}

// -----------------------------------------------------------------------
// Pitfall 2: Forgetting to null source in move operations
// -----------------------------------------------------------------------
// If the move constructor doesn't null out the source's pointer,
// the source's destructor will delete the resource → dangling pointer
// in the destination.
//
// This is demonstrated conceptually; the correct move ctor nulls the source:

class SafeMove
{
    int *m_ptr{};

public:
    explicit SafeMove(int val) : m_ptr{new int(val)} {}

    SafeMove(SafeMove &&src) noexcept
        : m_ptr{src.m_ptr}
    {
        src.m_ptr = nullptr; // CRITICAL: without this, src's dtor deletes m_ptr!
    }

    SafeMove &operator=(SafeMove &&src) noexcept
    {
        if (this != &src)
        {
            delete m_ptr;
            m_ptr = src.m_ptr;
            src.m_ptr = nullptr; // CRITICAL
        }
        return *this;
    }

    ~SafeMove() { delete m_ptr; }

    int value() const { return m_ptr ? *m_ptr : -1; }
};

void pitfall2_nullSource()
{
    std::cout << "\n=== Pitfall 2: Always null source in move ops ===\n";

    SafeMove a(42);
    SafeMove b(std::move(a));
    std::cout << "  b.value() = " << b.value() << '\n';
    std::cout << "  a.value() = " << a.value() << " (moved-from, safely null)\n";
}

// -----------------------------------------------------------------------
// Pitfall 3: Using a moved-from object's value
// -----------------------------------------------------------------------
void pitfall3_movedFromValue()
{
    std::cout << "\n=== Pitfall 3: Don't rely on moved-from values ===\n";

    std::string s = "Hello";
    std::string t = std::move(s);

    // DON'T do this - s's value is indeterminate:
    // if (s == "Hello") { ... }   // unreliable!

    // Instead, reassign before using:
    s = "Reset";
    std::cout << "  After reassign: s = \"" << s << "\"\n";
    std::cout << "  t = \"" << t << "\"\n";
}

// -----------------------------------------------------------------------
// Pitfall 4: Passing unique_ptr by value without std::move
// -----------------------------------------------------------------------
void takeOwnership(std::unique_ptr<Widget> w)
{
    std::cout << "  Received: \"" << w->name() << "\"\n";
}

void pitfall4_uniquePtrMove()
{
    std::cout << "\n=== Pitfall 4: Must std::move unique_ptr to pass by value ===\n";

    auto ptr = std::make_unique<Widget>("Owned");

    // This would NOT compile - copy is deleted:
    // takeOwnership(ptr);   // ERROR!

    // CORRECT: explicitly move it:
    takeOwnership(std::move(ptr));
    std::cout << "  ptr is now " << (ptr ? "not null" : "null") << '\n';
}

// -----------------------------------------------------------------------
// Pitfall 5: Manually deleting a smart-pointer-managed resource
// -----------------------------------------------------------------------
void pitfall5_noManualDelete()
{
    std::cout << "\n=== Pitfall 5: Never manually delete smart-pointer resources ===\n";
    std::cout << "  WRONG:  auto sp = make_shared<Widget>(\"X\");\n";
    std::cout << "          delete sp.get();   // BUG: sp will double-delete!\n";
    std::cout << "  RIGHT:  Let the smart pointer handle deletion automatically.\n";

    // Correct usage - just let it go out of scope:
    {
        auto sp = std::make_shared<Widget>("AutoClean");
        // No delete needed!
    }
}

// -----------------------------------------------------------------------
// Pitfall 6: std::swap in move ctor causes infinite recursion
// -----------------------------------------------------------------------
void pitfall6_noStdSwapInMove()
{
    std::cout << "\n=== Pitfall 6: Don't use std::swap inside move ctor ===\n";
    std::cout << "  std::swap calls move operations internally.\n";
    std::cout << "  If your move ctor calls std::swap → infinite recursion!\n";
    std::cout << "  Solution: use direct member-wise steal + null, or write\n";
    std::cout << "  a custom memberSwap() that swaps raw members.\n";
}

// -----------------------------------------------------------------------
// Pitfall 7: Never allocate smart pointers on the heap
// -----------------------------------------------------------------------
void pitfall7_noHeapSmartPtrs()
{
    std::cout << "\n=== Pitfall 7: Don't heap-allocate smart pointers ===\n";
    std::cout << "  WRONG: auto* p = new std::unique_ptr<int>(new int(5));\n";
    std::cout << "         // Now you need to delete p - defeating the purpose!\n";
    std::cout << "  RIGHT: auto p = std::make_unique<int>(5);\n";
    std::cout << "         // p lives on the stack, resource freed automatically.\n";
}

// -----------------------------------------------------------------------
int main()
{
    pitfall1_correctUsage();
    pitfall2_nullSource();
    pitfall3_movedFromValue();
    pitfall4_uniquePtrMove();
    pitfall5_noManualDelete();
    pitfall6_noStdSwapInMove();
    pitfall7_noHeapSmartPtrs();

    std::cout << "\nDone.\n";
    return 0;
}
