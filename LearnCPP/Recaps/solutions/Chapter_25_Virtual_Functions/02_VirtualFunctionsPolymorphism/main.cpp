// Chapter 25 - Project 02: Virtual Functions and Polymorphism
// ============================================================
// Marking a base-class function as `virtual` tells the compiler to
// resolve calls through pointers/references to the MOST-DERIVED
// override at RUNTIME.  This is the heart of runtime polymorphism.
//
// Key rules:
//   1. Once a function is declared virtual in the base, it is implicitly
//      virtual in all derived classes.
//   2. Virtual resolution only works through pointers or references -
//      NOT on plain objects (that causes slicing - see Project 11).
//   3. Never call virtual functions from constructors or destructors:
//      the derived portion doesn't exist yet (or has been destroyed).

#include <iostream>
#include <string_view>

// ---------- base ----------
class Animal
{
public:
    // Virtual - enables runtime dispatch.
    virtual std::string_view speak() const { return "???"; }
    virtual std::string_view getName() const { return "Animal"; }

    // Virtual destructor (best practice for any base class - see Project 05).
    virtual ~Animal() = default;
};

// ---------- derived ----------
class Cat : public Animal
{
public:
    // 'override' enforces that this matches a base virtual signature.
    std::string_view speak() const override { return "Meow"; }
    std::string_view getName() const override { return "Cat"; }
};

class Dog : public Animal
{
public:
    std::string_view speak() const override { return "Woof"; }
    std::string_view getName() const override { return "Dog"; }
};

class Kitten : public Cat
{
public:
    // Overrides Cat::speak() (which itself overrides Animal::speak()).
    std::string_view speak() const override { return "Mew"; }
    std::string_view getName() const override { return "Kitten"; }
};

// ---------- helper using base reference ----------
void report(const Animal &animal)
{
    // NOW the call resolves to the most-derived version at runtime.
    std::cout << animal.getName() << " says " << animal.speak() << '\n';
}

// ---------- main ----------
int main()
{
    Cat cat;
    Dog dog;
    Kitten kitten;

    std::cout << "=== Through base reference (virtual - works!) ===\n";
    report(cat);    // Cat says Meow
    report(dog);    // Dog says Woof
    report(kitten); // Kitten says Mew

    std::cout << "\n=== Through base pointer ===\n";
    Animal *ptr = &cat;
    std::cout << ptr->getName() << " says " << ptr->speak() << '\n'; // Cat says Meow

    ptr = &kitten;
    std::cout << ptr->getName() << " says " << ptr->speak() << '\n'; // Kitten says Mew

    // Even a Cat* pointing to a Kitten resolves correctly:
    std::cout << "\n=== Cat* pointing to Kitten ===\n";
    Cat *catPtr = &kitten;
    std::cout << catPtr->getName() << " says " << catPtr->speak() << '\n'; // Kitten says Mew

    // Direct object call - virtual, but no polymorphism needed
    // because the compiler knows the exact type.
    std::cout << "\n=== Direct object call ===\n";
    std::cout << dog.getName() << " says " << dog.speak() << '\n'; // Dog says Woof

    return 0;
}
