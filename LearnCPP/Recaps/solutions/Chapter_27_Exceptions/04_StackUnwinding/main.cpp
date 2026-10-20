// Chapter 27 - Project 04: Stack Unwinding in Detail
// =====================================================
// When an exception is thrown:
//   1. The runtime looks for a matching catch handler in the current function.
//   2. If none is found, the function is removed from the call stack and its
//      local variables are destroyed (their destructors run).
//   3. The search continues in the calling function - repeat until a handler
//      is found or the call stack is exhausted (→ std::terminate).
//
// This project shows the exact order of destruction during unwinding.

#include <iostream>
#include <string>

class Resource
{
    std::string m_name;
    int m_id;

public:
    Resource(const std::string &name, int id)
        : m_name{name}, m_id{id}
    {
        std::cout << "  + Resource(" << m_name << ", " << m_id << ") acquired\n";
    }

    ~Resource()
    {
        std::cout << "  - Resource(" << m_name << ", " << m_id << ") released\n";
    }
};

void innerFunction()
{
    Resource r1{"inner", 1};
    Resource r2{"inner", 2};

    std::cout << "  innerFunction(): throwing after creating 2 resources\n";
    throw std::string{"Error in innerFunction"};

    // r3 is never constructed because the throw happens first
    // Resource r3{ "inner", 3 }; // would be here
}

void middleFunction()
{
    Resource r1{"middle", 1};

    std::cout << "  middleFunction(): calling innerFunction()\n";
    innerFunction();

    // This resource is never created - the exception propagates
    Resource r2{"middle", 2};
}

void outerFunction()
{
    Resource r1{"outer", 1};
    Resource r2{"outer", 2};
    Resource r3{"outer", 3};

    std::cout << "  outerFunction(): calling middleFunction()\n";
    middleFunction();
}

int main()
{
    std::cout << "=== Stack unwinding: destruction order ===\n";
    std::cout << "Observe: resources are destroyed in reverse order of creation,\n";
    std::cout << "from innermost function outward.\n\n";

    try
    {
        outerFunction();
    }
    catch (const std::string &error)
    {
        std::cout << "\nmain(): caught: " << error << '\n';
    }

    // Expected output order of destruction:
    //   inner-2, inner-1   (innerFunction's locals, reverse order)
    //   middle-1           (middleFunction's local; middle-2 was never created)
    //   outer-3, outer-2, outer-1  (outerFunction's locals, reverse order)

    std::cout << "\n=== Partial construction ===\n";
    std::cout << "If an exception occurs partway through creating objects,\n";
    std::cout << "only the already-constructed objects are destroyed.\n\n";

    try
    {
        Resource a{"partial", 1};
        Resource b{"partial", 2};
        throw std::string{"mid-construction error"};
        Resource c{"partial", 3}; // never constructed
    }
    catch (const std::string &error)
    {
        std::cout << "\nCaught: " << error << '\n';
        std::cout << "(Resource partial-3 was never created, so never destroyed)\n";
    }

    return 0;
}
