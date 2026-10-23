// Lesson 4: virtual vs non-virtual dispatch, override, object slicing, abstract interface, polymorphic container.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Animal {
    virtual void speak() const { std::cout << "...\n"; }
    void nonVirtual() const { std::cout << "Animal::nonVirtual\n"; }
    virtual ~Animal() = default;                       // ALWAYS virtual in a polymorphic base
};
struct Dog : Animal {
    void speak() const override { std::cout << "Woof\n"; }     // override: compiler checks the signature
    void nonVirtual() const { std::cout << "Dog::nonVirtual\n"; }
};

struct Shape {                                         // abstract interface
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
struct Circle : Shape {
    double r;
    explicit Circle(double r) : r(r) {}
    double area() const override { return 3.14159 * r * r; }
};
struct Square : Shape {
    double s;
    explicit Square(double s) : s(s) {}
    double area() const override { return s * s; }
};

struct Base {
    Base() { init(); }
    virtual void init() { std::cout << "Base::init\n"; }
    virtual ~Base() = default;
};
struct Derived : Base {
    void init() override { std::cout << "Derived::init\n"; }
};

int main() {
    Dog rex;
    Animal* p = &rex;
    p->speak();                                        // virtual: Dog's behaviour (dynamic type)
    p->nonVirtual();                                   // non-virtual: Animal's (static type)

    Animal sliced = rex;                               // SLICING: only the Animal part is copied
    sliced.speak();                                    // prints "..." : the Dog part is gone

    std::vector<std::unique_ptr<Shape>> shapes;        // owns the objects: no slicing, no manual delete
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Square>(3.0));
    for (const auto& s : shapes) std::cout << "area " << s->area() << '\n';

    std::cout << "virtual call inside a constructor:\n";
    Derived d;                                         // prints Base::init, NOT Derived::init
}
