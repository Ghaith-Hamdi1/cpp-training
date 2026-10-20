// Project 01 - Basic Inheritance
// ================================
// Demonstrates the fundamental syntax of public inheritance in C++.
// A derived class acquires all members of the base class and can add its own.
// Inheritance models "is-a" relationships: a Dog "is-a" Animal.

#include <iostream>
#include <string>
#include <string_view>

// Base class - represents a generic Animal
class Animal
{
private:
    std::string m_name{};
    int m_age{};

public:
    Animal(std::string_view name, int age)
        : m_name{name}, m_age{age}
    {
    }

    const std::string &getName() const { return m_name; }
    int getAge() const { return m_age; }

    void speak() const
    {
        std::cout << m_name << " says: ...\n";
    }
};

// Derived class - Dog "is-a" Animal
// Uses public inheritance: `class Dog : public Animal`
// Dog inherits getName(), getAge(), and speak() from Animal
// and adds its own member (m_breed) and function (fetch).
class Dog : public Animal
{
private:
    std::string m_breed{};

public:
    // The derived constructor delegates initialization of inherited members
    // (name, age) to the base class constructor via the member initializer list.
    Dog(std::string_view name, int age, std::string_view breed)
        : Animal{name, age} // call base constructor
          ,
          m_breed{breed} // initialize own member
    {
    }

    const std::string &getBreed() const { return m_breed; }

    // New functionality specific to Dog
    void fetch() const
    {
        std::cout << getName() << " fetches the ball!\n";
    }
};

int main()
{
    // Create an Animal object - uses base class only
    Animal genericAnimal{"Generic Animal", 5};
    std::cout << genericAnimal.getName() << " is " << genericAnimal.getAge() << " years old.\n";
    genericAnimal.speak();

    std::cout << '\n';

    // Create a Dog object - has all Animal members plus Dog-specific ones
    Dog rex{"Rex", 3, "German Shepherd"};
    std::cout << rex.getName() << " is " << rex.getAge() << " years old.\n";
    std::cout << "Breed: " << rex.getBreed() << '\n';
    rex.speak(); // inherited from Animal
    rex.fetch(); // defined only in Dog

    // Note: genericAnimal.fetch() would NOT compile -
    // base class objects cannot access derived-class-only functions.

    return 0;
}
