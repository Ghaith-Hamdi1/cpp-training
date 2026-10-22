// Lesson 19: multiple inheritance, the diamond and virtual inheritance, object layout, RTTI and typeid, private
// inheritance, explicit constructors and conversion operators, copy-and-swap. Compile with -std=c++20.
#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>

// 1. two interfaces: the object carries one vptr per polymorphic base
struct Reader { virtual int read() = 0; virtual ~Reader() = default; };
struct Writer { virtual void write(int) = 0; virtual ~Writer() = default; };
struct File : Reader, Writer { int v = 0; int read() override { return v; } void write(int x) override { v = x; } };

// 2. the diamond, without and with virtual inheritance
struct Base { int id = 1; Base() { std::cout << "Base "; } };
struct Left : Base { Left() { std::cout << "Left "; } };
struct Right : Base { Right() { std::cout << "Right "; } };
struct Diamond : Left, Right { Diamond() { std::cout << "Diamond\n"; } };

struct VBase { int id = 1; VBase() { std::cout << "VBase "; } };
struct VLeft : virtual VBase { VLeft() { std::cout << "VLeft "; } };
struct VRight : virtual VBase { VRight() { std::cout << "VRight "; } };
struct VDiamond : VLeft, VRight { VDiamond() { std::cout << "VDiamond\n"; } };

// 3. RTTI
struct Animal { virtual ~Animal() = default; };
struct Dog : Animal {};
struct Cat : Animal {};
struct Plain { int x; };                                              // not polymorphic

// 4. private inheritance: "implemented in terms of", not "is a"
struct Engine { void start() { std::cout << "engine started\n"; } };
struct Car : private Engine {
    void drive() { start(); }                                         // the base is an implementation detail
    using Engine::start;                                              // re-export one member if you want to
};

// 5. explicit constructors and conversion operators
struct Meters { double v; Meters(double x) : v(x) {} };               // implicit: a double silently becomes Meters
struct Feet { double v; explicit Feet(double x) : v(x) {} };         // explicit: needs Feet(3.0)
void takeMeters(Meters) {}
void takeFeet(Feet) {}

struct Handle {
    int fd;
    explicit operator bool() const { return fd >= 0; }                // usable in if(), not in arithmetic
};

// 6. copy-and-swap: one assignment operator, strong guarantee, self-assignment safe
class Buffer {
    std::size_t n_; int* p_;
public:
    explicit Buffer(std::size_t n) : n_(n), p_(new int[n]()) {}
    Buffer(const Buffer& o) : n_(o.n_), p_(new int[o.n_]) { for (std::size_t i = 0; i < n_; ++i) p_[i] = o.p_[i]; }
    ~Buffer() { delete[] p_; }
    friend void swap(Buffer& a, Buffer& b) noexcept { std::swap(a.n_, b.n_); std::swap(a.p_, b.p_); }
    Buffer& operator=(Buffer other) noexcept { swap(*this, other); return *this; }   // by value: the copy IS the temporary
    std::size_t size() const { return n_; }
};

int main()
{
    File f;
    Reader* r = &f;
    Writer* w = &f;
    std::cout << "File has two bases: sizeof(File) = " << sizeof(File) << " (two vptrs + int), Reader* and Writer* point to "
              << ((static_cast<void*>(r) == static_cast<void*>(w)) ? "the same" : "different") << " addresses\n";

    std::cout << "construct a plain diamond: "; Diamond d;
    std::cout << "plain diamond has two Base subobjects: sizeof(Diamond) = " << sizeof(Diamond) << " and d.id is ambiguous (d.Left::id = " << d.Left::id << ")\n";
    std::cout << "construct a virtual diamond: "; VDiamond vd;
    std::cout << "virtual diamond has one VBase: vd.id = " << vd.id << " (no ambiguity), sizeof(VDiamond) = " << sizeof(VDiamond) << '\n';

    Animal* a = new Dog;
    std::cout << "typeid(*a) == typeid(Dog): " << std::boolalpha << (typeid(*a) == typeid(Dog)) << ", == typeid(Cat): " << (typeid(*a) == typeid(Cat)) << '\n';
    std::cout << "dynamic_cast<Cat*>(a) is " << (dynamic_cast<Cat*>(a) ? "set" : "null") << ", dynamic_cast<Dog*>(a) is " << (dynamic_cast<Dog*>(a) ? "set" : "null") << '\n';
    Reader* rr = &f;
    Writer* cross = dynamic_cast<Writer*>(rr);                        // a cross-cast: sideways between two bases
    std::cout << "cross-cast Reader* -> Writer* works: " << (cross != nullptr) << '\n';
    try { (void)dynamic_cast<Cat&>(*a); } catch (const std::bad_cast&) { std::cout << "dynamic_cast to a reference type throws bad_cast\n"; }
    delete a;
    Plain p{1};
    std::cout << "typeid of a non-polymorphic object is static: " << (typeid(p) == typeid(Plain)) << '\n';

    Car c;
    c.drive();
    c.start();
    static_assert(!std::is_convertible_v<Car*, Engine*>);             // private inheritance: no conversion to the base
    std::cout << "Car* converts to Engine*: " << std::is_convertible_v<Car*, Engine*> << '\n';

    takeMeters(3.0);                                                  // compiles: implicit conversion
    // takeFeet(3.0);                                                 // ERROR: the constructor is explicit
    takeFeet(Feet(3.0));
    static_assert(std::is_convertible_v<double, Meters> && !std::is_convertible_v<double, Feet>);
    Handle h{3};
    if (h) std::cout << "explicit operator bool works in an if\n";
    static_assert(!std::is_convertible_v<Handle, int> && !std::is_convertible_v<Handle, bool>);
    std::cout << "Handle converts implicitly to bool: " << std::is_convertible_v<Handle, bool> << '\n';

    Buffer b1(3), b2(5);
    b1 = b2;
    b1 = b1;                                                          // self-assignment is safe
    std::cout << "copy-and-swap: b1.size() = " << b1.size() << " after b1 = b2\n";
}
