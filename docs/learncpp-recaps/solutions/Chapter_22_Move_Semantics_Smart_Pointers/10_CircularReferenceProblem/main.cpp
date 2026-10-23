// Chapter 22 - Project 10: Circular Reference Problem
// When two objects hold shared_ptrs to each other, a reference cycle forms.
// Neither object's count ever reaches 0, so neither is deallocated → LEAK.
//
// Solution: replace one of the shared_ptrs with a weak_ptr.

#include <iostream>
#include <memory>
#include <string>

// -----------------------------------------------------------------------
// PART A: The PROBLEM - circular shared_ptr references
// -----------------------------------------------------------------------
namespace Problem
{
    class Person; // forward declaration

    class Person
    {
        std::string m_name;
        std::shared_ptr<Person> m_partner; // <-- shared_ptr creates cycle

    public:
        explicit Person(const std::string &name) : m_name{name}
        {
            std::cout << "  [Person] \"" << m_name << "\" created\n";
        }
        ~Person()
        {
            std::cout << "  [Person] \"" << m_name << "\" destroyed\n";
        }

        void setPartner(std::shared_ptr<Person> partner)
        {
            m_partner = partner;
        }

        const std::string &name() const { return m_name; }
    };

    void demonstrate()
    {
        std::cout << "=== PROBLEM: Circular shared_ptr (memory leak) ===\n";

        auto alice = std::make_shared<Person>("Alice");
        auto bob = std::make_shared<Person>("Bob");

        std::cout << "  alice use_count = " << alice.use_count() << '\n'; // 1
        std::cout << "  bob   use_count = " << bob.use_count() << '\n';   // 1

        // Create circular reference: Alice → Bob → Alice
        alice->setPartner(bob);
        bob->setPartner(alice);

        std::cout << "  After linking:\n";
        std::cout << "  alice use_count = " << alice.use_count() << '\n'; // 2 (alice + bob->m_partner)
        std::cout << "  bob   use_count = " << bob.use_count() << '\n';   // 2 (bob + alice->m_partner)

        std::cout << "  Leaving scope...\n";
        // alice & bob shared_ptrs are destroyed → counts drop to 1, NOT 0.
        // Neither Person is ever destroyed → MEMORY LEAK!
    }
}

// -----------------------------------------------------------------------
// PART B: The SOLUTION - use weak_ptr for one direction
// -----------------------------------------------------------------------
namespace Solution
{
    class Person
    {
        std::string m_name;
        std::weak_ptr<Person> m_partner; // <-- weak_ptr breaks the cycle!

    public:
        explicit Person(const std::string &name) : m_name{name}
        {
            std::cout << "  [Person] \"" << m_name << "\" created\n";
        }
        ~Person()
        {
            std::cout << "  [Person] \"" << m_name << "\" destroyed\n";
        }

        void setPartner(std::shared_ptr<Person> partner)
        {
            m_partner = partner; // stores as weak_ptr - no ref count increase
        }

        // To access the partner, lock the weak_ptr
        std::shared_ptr<Person> getPartner() const
        {
            return m_partner.lock();
        }

        const std::string &name() const { return m_name; }
    };

    void demonstrate()
    {
        std::cout << "\n=== SOLUTION: weak_ptr breaks the cycle ===\n";

        auto alice = std::make_shared<Person>("Alice");
        auto bob = std::make_shared<Person>("Bob");

        alice->setPartner(bob);
        bob->setPartner(alice);

        // weak_ptr does NOT increase use_count
        std::cout << "  alice use_count = " << alice.use_count() << '\n'; // 1
        std::cout << "  bob   use_count = " << bob.use_count() << '\n';   // 1

        // Access partner through lock()
        if (auto partner = alice->getPartner())
            std::cout << "  Alice's partner: \"" << partner->name() << "\"\n";

        std::cout << "  Leaving scope...\n";
        // Counts drop to 0 → both Persons are properly destroyed!
    }
}

// -----------------------------------------------------------------------
int main()
{
    Problem::demonstrate();
    std::cout << "  ^ Notice: no \"destroyed\" messages → LEAK!\n";

    Solution::demonstrate();
    std::cout << "  ^ Notice: both \"destroyed\" messages appear → NO LEAK!\n";

    std::cout << "\nDone.\n";
    return 0;
}
