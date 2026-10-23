// Chapter 25 - Project 05: Virtual Destructors
// ===============================================
// When you delete a derived object through a base pointer, the destructor
// that runs depends on the STATIC type of the pointer - unless the
// destructor is virtual.
//
// Without a virtual destructor → only ~Base() runs → the derived portion
// is NEVER cleaned up → UNDEFINED BEHAVIOR (resource leaks, corruption).
//
// Rule: ALWAYS give base classes intended for inheritance a virtual destructor.
//
// You can also bypass virtual dispatch using the scope resolution operator:
//   obj.Base::getName()  - calls Base::getName() regardless of dynamic type.

#include <iostream>
#include <string>

// ========== BAD: non-virtual destructor ==========
class BadBase
{
public:
    std::string name{"BadBase"};

    // Non-virtual destructor - dangerous if deleting through BadBase*.
    ~BadBase()
    {
        std::cout << "  ~BadBase()\n";
    }
};

class BadDerived : public BadBase
{
public:
    std::string *data; // heap-allocated resource

    BadDerived() : data{new std::string{"important data"}}
    {
        name = "BadDerived";
    }

    ~BadDerived()
    {
        std::cout << "  ~BadDerived() - freeing data\n";
        delete data;
    }
};

// ========== GOOD: virtual destructor ==========
class GoodBase
{
public:
    std::string name{"GoodBase"};

    // Virtual destructor - safe to delete through GoodBase*.
    virtual ~GoodBase()
    {
        std::cout << "  ~GoodBase()\n";
    }
};

class GoodDerived : public GoodBase
{
public:
    std::string *data;

    GoodDerived() : data{new std::string{"important data"}}
    {
        name = "GoodDerived";
    }

    ~GoodDerived() override // 'override' works on destructors too
    {
        std::cout << "  ~GoodDerived() - freeing data\n";
        delete data;
    }
};

// ========== Bypassing virtual dispatch ==========
class Animal
{
public:
    virtual std::string_view speak() const { return "???"; }
    virtual ~Animal() = default;
};

class Cat : public Animal
{
public:
    std::string_view speak() const override { return "Meow"; }
};

// ---------- main ----------
int main()
{
    // --- Bad example: non-virtual destructor ---
    std::cout << "=== BAD: non-virtual destructor ===\n";
    std::cout << "Deleting BadDerived directly (OK):\n";
    {
        BadDerived bd;
    } // ~BadDerived() then ~BadBase() - correct

    std::cout << "\nDeleting through BadBase* (UNDEFINED BEHAVIOR!):\n";
    // In practice this often only calls ~BadBase(), leaking 'data'.
    // We demonstrate it here but this is UB - never do this in real code.
    BadBase *badPtr = new BadDerived();
    delete badPtr; // UB! Only ~BadBase() is called in many compilers.

    // --- Good example: virtual destructor ---
    std::cout << "\n=== GOOD: virtual destructor ===\n";
    std::cout << "Deleting through GoodBase*:\n";
    GoodBase *goodPtr = new GoodDerived();
    delete goodPtr; // ~GoodDerived() then ~GoodBase() - correct!

    // --- Bypassing virtual dispatch with scope resolution ---
    std::cout << "\n=== Bypassing virtual dispatch ===\n";
    Cat cat;
    Animal &ref = cat;
    std::cout << "ref.speak()          = " << ref.speak() << '\n';         // Meow (virtual)
    std::cout << "ref.Animal::speak()  = " << ref.Animal::speak() << '\n'; // ??? (bypassed)

    return 0;
}
