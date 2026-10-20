// Chapter 25 - Project 01: Pointers and References to the Base Class
// ===================================================================
// A base pointer or reference can point/refer to any derived object,
// but WITHOUT virtual functions it can only see the base-class members.
// Calling a function through the base pointer always invokes the BASE
// version - the derived override is invisible.  This motivates the need
// for virtual functions (covered in Project 02).

#include <iostream>
#include <string_view>

// ---------- class hierarchy ----------
class Animal
{
public:
    // NON-virtual - resolved at compile time based on the static type.
    std::string_view speak() const { return "???"; }
    std::string_view getName() const { return "Animal"; }
};

class Cat : public Animal
{
public:
    std::string_view speak() const { return "Meow"; } // hides Animal::speak()
    std::string_view getName() const { return "Cat"; }
};

class Dog : public Animal
{
public:
    std::string_view speak() const { return "Woof"; } // hides Animal::speak()
    std::string_view getName() const { return "Dog"; }
};

// ---------- helper ----------
// Takes a base reference - can accept Cat, Dog, or any Animal-derived type.
void report(const Animal &animal)
{
    // Because speak() and getName() are NOT virtual, the compiler uses the
    // STATIC type (Animal&) to decide which function to call.
    // Result: always prints "Animal says ???" regardless of the real object.
    std::cout << animal.getName() << " says " << animal.speak() << '\n';
}

// ---------- main ----------
int main()
{
    Cat cat;
    Dog dog;

    // Direct calls - use the object's own type, so derived versions are called.
    std::cout << "=== Direct calls (no polymorphism needed) ===\n";
    std::cout << cat.getName() << " says " << cat.speak() << '\n'; // Cat says Meow
    std::cout << dog.getName() << " says " << dog.speak() << '\n'; // Dog says Woof

    // Calls through base reference - static type is Animal&.
    std::cout << "\n=== Through base reference (no virtual - broken!) ===\n";
    report(cat); // Animal says ???  <-- NOT what we want!
    report(dog); // Animal says ???  <-- NOT what we want!

    // Calls through base pointer - same issue.
    std::cout << "\n=== Through base pointer (no virtual - broken!) ===\n";
    Animal *ptr = &cat;
    std::cout << ptr->getName() << " says " << ptr->speak() << '\n'; // Animal says ???

    ptr = &dog;
    std::cout << ptr->getName() << " says " << ptr->speak() << '\n'; // Animal says ???

    // Takeaway: without 'virtual', base pointers/references always call
    // the base-class version.  Virtual functions fix this (see Project 02).

    return 0;
}
