// Chapter 15 - Project 12: Common Pitfalls
// ==========================================
//
// This project demonstrates the most common mistakes from Chapter 15,
// shows what goes wrong, and provides the correct fix for each.
//
// Each pitfall is in its own clearly-labelled section.

#include <iostream>
#include <string>

// =====================================================================
// PITFALL 1: `this` is a pointer, not a reference
// =====================================================================
//
// WRONG: this.member     (treating `this` like a reference)
// RIGHT: this->member    (treating `this` like a pointer)
//    OR: (*this).member
//
// This is just a syntax issue - the compiler will catch it, but it
// confuses beginners who are used to the dot operator.

class Pitfall1
{
private:
    int m_value{};

public:
    Pitfall1(int v) : m_value{v} {}

    void printCorrect() const
    {
        // CORRECT: use -> because `this` is a pointer
        std::cout << "  this->m_value = " << this->m_value << '\n';
        // Also correct: dereference first
        std::cout << "  (*this).m_value = " << (*this).m_value << '\n';
    }

    // WRONG (wouldn't compile):
    // void printWrong() const { std::cout << this.m_value; }
};

// =====================================================================
// PITFALL 2: Returning *this by value breaks method chaining
// =====================================================================
//
// If a chainable function returns by VALUE, it returns a COPY.
// Subsequent calls in the chain operate on the copy, not the original.

class BrokenChain
{
private:
    int m_value{0};

public:
    // WRONG: Returns by value - creates a copy!
    BrokenChain add(int x)
    {
        m_value += x;
        return *this; // Returns a COPY
    }

    int getValue() const { return m_value; }
};

class CorrectChain
{
private:
    int m_value{0};

public:
    // CORRECT: Returns by reference - no copy, chain works on original.
    CorrectChain &add(int x)
    {
        m_value += x;
        return *this;
    }

    int getValue() const { return m_value; }
};

// =====================================================================
// PITFALL 3: Accessing non-static members from a static function
// =====================================================================
//
// Static member functions have NO `this` pointer - they cannot access
// non-static data members or call non-static member functions.

class Pitfall3
{
private:
    int m_instanceData{42};
    static inline int s_sharedData{100};

public:
    static void staticFunc()
    {
        // CORRECT: Can access static members
        std::cout << "  s_sharedData = " << s_sharedData << '\n';

        // WRONG (wouldn't compile):
        // std::cout << m_instanceData;   // Error: no `this` pointer!
        // The compiler would say: "invalid use of member in static function"
    }

    void instanceFunc() const
    {
        // Instance functions CAN access both static and non-static:
        std::cout << "  m_instanceData = " << m_instanceData << '\n';
        std::cout << "  s_sharedData = " << s_sharedData << '\n';
    }
};

// =====================================================================
// PITFALL 4: Assuming friendship is reciprocal
// =====================================================================
//
// If class A declares `friend class B;`, B can access A's privates.
// But A CANNOT access B's privates - friendship is one-way.

class ClassA
{
private:
    int m_secretA{111};

public:
    friend class ClassB; // B can access A's privates

    // A CANNOT access B's privates - this would fail:
    // void tryAccessB(const ClassB& b) { std::cout << b.m_secretB; } // ERROR!
};

class ClassB
{
private:
    int m_secretB{222};

public:
    void accessA(const ClassA &a) const
    {
        // ClassB CAN access ClassA's private members (A friended B)
        std::cout << "  ClassB reads ClassA's secret: " << a.m_secretA << '\n';
    }

    int getSecret() const { return m_secretB; }
};

// =====================================================================
// PITFALL 5: Forgetting the template parameter in external definitions
// =====================================================================
//
// When defining a member function OUTSIDE a class template, you must:
//   1. Resupply `template <typename T>`
//   2. Qualify the class name: `MyClass<T>::func()`

template <typename T>
class Container
{
private:
    T m_data{};

public:
    Container(const T &data) : m_data{data} {}

    // Declared inside, defined outside
    void print() const;
};

// CORRECT: template parameter re-declared, class name qualified with <T>
template <typename T>
void Container<T>::print() const
{
    std::cout << "  Container holds: " << m_data << '\n';
}

// WRONG (wouldn't compile):
// void Container::print() const { ... }  // Missing template<typename T> and <T>

// =====================================================================
// PITFALL 6: std::exit() does NOT call destructors for local objects
// =====================================================================

class ResourceHolder
{
private:
    std::string m_name{};

public:
    ResourceHolder(const std::string &name) : m_name{name}
    {
        std::cout << "  " << m_name << " acquired\n";
    }

    ~ResourceHolder()
    {
        std::cout << "  " << m_name << " released\n";
    }
};

// =====================================================================
// MAIN - run all pitfall demonstrations
// =====================================================================

int main()
{
    std::cout << "=== PITFALL 1: this is a pointer ===\n";
    Pitfall1 p1{42};
    p1.printCorrect();
    // p1.printWrong(); // Would not compile: `this.m_value` is invalid

    std::cout << "\n=== PITFALL 2: Return *this by REFERENCE, not by value ===\n";
    BrokenChain broken;
    broken.add(10).add(20).add(30);
    std::cout << "  BrokenChain result:  " << broken.getValue()
              << "  (expected 60, got 10 - chaining broke!)\n";

    CorrectChain correct;
    correct.add(10).add(20).add(30);
    std::cout << "  CorrectChain result: " << correct.getValue()
              << "  (expected 60, got 60 - works!)\n";

    std::cout << "\n=== PITFALL 3: Static functions can't access instance data ===\n";
    Pitfall3::staticFunc(); // OK - accesses only static data
    Pitfall3 p3;
    p3.instanceFunc(); // OK - accesses both

    std::cout << "\n=== PITFALL 4: Friendship is NOT reciprocal ===\n";
    ClassA a;
    ClassB b;
    b.accessA(a); // B reads A's private - OK
    // a.tryAccessB(b);  // Would NOT compile - A is NOT a friend of B
    std::cout << "  ClassA cannot access ClassB's secret (would not compile)\n";

    std::cout << "\n=== PITFALL 5: Template parameter in external definitions ===\n";
    Container<int> ci{42};
    ci.print();
    Container<std::string> cs{"hello"};
    cs.print();

    std::cout << "\n=== PITFALL 6: std::exit() skips destructors ===\n";
    {
        ResourceHolder rh{"Database Connection"};
        std::cout << "  Normal scope exit - destructor WILL be called:\n";
    } // rh destroyed here, destructor runs
    std::cout << "  (In contrast, std::exit() would skip the destructor entirely.)\n";
    std::cout << "  (We don't call std::exit() here to keep the demo running.)\n";

    std::cout << "\n=== All pitfalls demonstrated! ===\n";
    return 0;
}
