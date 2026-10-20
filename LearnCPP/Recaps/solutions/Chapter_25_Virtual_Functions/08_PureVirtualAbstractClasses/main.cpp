// Chapter 25 - Project 08: Pure Virtual Functions and Abstract Base Classes
// ==========================================================================
// A PURE VIRTUAL function is declared with = 0:
//     virtual void doWork() = 0;
//
// - Any class with at least one pure virtual function is ABSTRACT.
// - You CANNOT instantiate an abstract class.
// - Derived classes MUST override all pure virtual functions to be concrete
//   (instantiable).  If they don't, they're also abstract.
//
// A pure virtual function CAN have a body/definition - the class is still
// abstract, but derived classes can call the base implementation via
// Base::pureFunc().

#include <iostream>
#include <string>

// ---------- Abstract base class ----------
class Animal
{
protected:
    std::string m_name;

public:
    explicit Animal(std::string_view name) : m_name{name} {}

    // Pure virtual - every derived class MUST provide an implementation.
    virtual std::string_view speak() const = 0;

    // A pure virtual with a default body.
    // Derived classes MUST still override it, but they can delegate to this.
    virtual std::string describe() const = 0;

    const std::string &getName() const { return m_name; }

    virtual ~Animal() = default;
};

// Provide a default body for the pure virtual (outside the class).
std::string Animal::describe() const
{
    return m_name + " is an animal";
}

// ---------- Concrete derived class ----------
class Cat : public Animal
{
public:
    explicit Cat(std::string_view name) : Animal{name} {}

    std::string_view speak() const override { return "Meow"; }

    // Overrides the pure virtual but delegates to the base body.
    std::string describe() const override
    {
        return Animal::describe() + " (specifically a cat)";
    }
};

class Dog : public Animal
{
public:
    explicit Dog(std::string_view name) : Animal{name} {}

    std::string_view speak() const override { return "Woof"; }

    std::string describe() const override
    {
        return Animal::describe() + " (specifically a dog)";
    }
};

// ---------- Still-abstract class (does NOT override speak) ----------
class AbstractBird : public Animal
{
public:
    using Animal::Animal;
    // speak() is NOT overridden - AbstractBird is still abstract.
    // It does provide describe().
    std::string describe() const override
    {
        return Animal::describe() + " (some kind of bird)";
    }
};

// ---------- Concrete bird ----------
class Parrot : public AbstractBird
{
public:
    using AbstractBird::AbstractBird;
    // Now ALL pure virtuals are overridden - Parrot is concrete.
    std::string_view speak() const override { return "Squawk"; }
};

// ---------- main ----------
int main()
{
    // Animal a{"test"};        // ERROR: cannot instantiate abstract class
    // AbstractBird ab{"test"}; // ERROR: still abstract (speak() not overridden)

    Cat cat{"Whiskers"};
    Dog dog{"Rex"};
    Parrot parrot{"Polly"};

    std::cout << "=== Pure virtual functions & abstract classes ===\n\n";

    // Polymorphic calls through base pointer.
    Animal *animals[] = {&cat, &dog, &parrot};
    for (const auto *a : animals)
    {
        std::cout << a->getName() << " says: " << a->speak() << '\n';
        std::cout << "  Description: " << a->describe() << '\n';
    }

    std::cout << "\n- A class with = 0 functions is abstract (not instantiable).\n";
    std::cout << "- Pure virtual CAN have a body - derived classes can call it.\n";
    std::cout << "- Derived class must override ALL pure virtuals to be concrete.\n";

    return 0;
}
