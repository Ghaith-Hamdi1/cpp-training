# Operators overloading

- Introduction to operators: In C++, operators are considered as functions and can be overloaded
  - When we perform operation "x + y", compiler uses built-in version of `+` operator — it will be translated to `operator+(x, y)`
  - If x and y are built-in types, no problem is faced since built-in operators are already defined
  - If the operator operands are not defined, compiler tries to perform casting to existing operators
    - [Diagram: compile error]
  - Otherwise, compile error is generated
- Copy assignment operator: `class_name& operator=(const class_name&)`
  - Must be overloaded as member function of class
  - As special operator, unlike other operators, when neither provided nor deleted, compiler provides default one
- Copy assignment operator:
  - If class is simple, we can lean on default version of copy constructor or assignment operator
  - If class contains tricky things (like pointers), we have to define them: this is called deep copy
    - Make a copy of all members
    - Allocate new pointer (since we are creating a different object in copy operation)
- Move assignment operator: `class_name& operator=(class_name&&)`
  - Must be overloaded as member function of class
  - As special operator, unlike other operators, when neither provided nor deleted, compiler provides one
- Move assignment operator:
  - If class is simple, we can lean on default version of copy constructor or assignment operator
  - It will be better to define move constructor or move assignment operator when move is allowed for object in question
  - Move operation should leave the moved object in valid state. Since moved object is a temporary object (r-value), it will be deleted anyway and if we have pointers they will be deleted (and memory that it is pointing to will be lost)

```cpp
// Trimmed excerpt — full runnable example: examples/02-cpp-oop/12-operators-overloading/26_assignment_move_operators.cpp
#include <iostream>

class A {
public:
    A() : m_ptr{nullptr} {}
    void createPtr() { removePtr(); m_ptr = new int; }
    void removePtr() { if (m_ptr != nullptr) { delete m_ptr; m_ptr = nullptr; } }

    // copy constructor
    A(const A& a)
    {
        std::cout << "Copy constructor" << std::endl;
        if (a.m_ptr != nullptr)
        {
            createPtr();
            *m_ptr = *a.m_ptr;
        }
    }
    // copy assignment
    A& operator=(const A& a)
    {
        std::cout << "Copy assignment operator" << std::endl;
        if (this != &a) // check if it is not self assignment
        {
            createPtr();
        }
        return *this;
    }

    // move constructor 
    A(A&& a) noexcept : m_ptr{a.m_ptr} {
        std::cout << "Move constructor" << std::endl;
        a.m_ptr = nullptr; // ownership moved to this and a is no longer owner, => nullptr
    }

    // move assignment
    A& operator=(A&& a) noexcept 
    {
        std::cout << "Move assignment operator" << std::endl;
        if (this != &a) // check if it is not self assignment
        {
            m_ptr = a.m_ptr;
            a.m_ptr = nullptr;
        }
        return *this;
    } 

    virtual ~A() { removePtr(); }
private:
    int * m_ptr;
};

A generateA()
{
    A a;
    return a; // rule in C++: l-value returned by value favors move over copy
}

int main()
{
    A a;
    a = generateA(); // this assignment will invoke the move assignment
    a = A();// this assignment will invoke the move assignment as well

    A a1 = std::move(a); // this will invoke move constructor

    A a2{a};
    a2 = a;
    return 0;
}
```

- To overload an operator with specific operands, operator keyword is used followed by the operator
  - List of possible operators contains all built-in operator list
  - Good practice
    - Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value.
    - Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.
- Three ways to implement operator overloading, as:
  - Friend function
  - Member function
  - Normal function (non-member function)
  - As reminder we have 4 types of operators, only 2 are applicable for overloading
    - Unary
    - Binary
- Overloading principle
  - `z = x + y` → `type_z operator+(type_x, type_y)`
  - Return type can be a value or a reference, generally operators that doesn't modify the object like arithmetic operators (+, *, /, ...) are returned by value and operators that modify the object like stream `<<` operator are returned by reference
- Overloading using friend function: operator definition function will be declared as friend to the class and can be defined inside or outside the class
- Overloading using friend function: IO stream operator `<<`
  - Used to display class information by just putting object instance after the operator in streams
  - [Annotation contrasting the non-friend/getter-based approach: "Hard to read and requires getters to be defined"]
- Overloading using friend function: IO stream operator `<<`
  - Example of use of output stream operator overloading
- Overloading using normal function: operator definition will be in a simple function
- Overloading using member function:
  - Not everything can be overloaded as member function because the overloaded operator must be added as a member of the left operand.
- Overloading exercise
  - Implement a class named `Digit` that contains an int attribute and overload the increment and decrement operators
- Overloading operators examples: see examples source code for operators
  - Unary: negation `-`
  - Binary:
    - Comparison: e.g. `>=` (full source also overloads `==`, `<=`)
    - Subscript: `[]`
    - Parentheses (functor) `()` with arbitrary parameter number
    - Typecast samples

```cpp
// Trimmed excerpt — full runnable example: examples/02-cpp-oop/12-operators-overloading/27_operators_overloading.cpp
#include <string>
#include <iostream>

class A
{
public:
     explicit A(const int& value): m_value{value} {}
     int getA() const { return m_value; }

     // friend function: operator+ for (int, A)
     friend A operator+(int x, const A& a)
     { 
          A aRes(x + a.m_value);
          return aRes;
     }

     // member function: operator+ for (A, std::string)
     A operator+(std::string& str) { return A(m_value + std::atoi(str.c_str())); }
private:
     int m_value;
};

// normal (non-member, non-friend) function: delegates to the friend above
A operator+(const A& a, int x) { return x + a; }
////////////////////////////////////////////
class Frame
{
public:
     enum class Origin
     {
          Server,
          Client,
     };
     Frame(int length, const std::string& payload, Origin origin):
          m_length{length}, m_payload{payload}, m_origin{origin} {}
          
     friend std::ostream& operator<<(std::ostream& out, const Frame& frame);
private:
     int m_length;
     std::string m_payload;
     Origin m_origin;
};

std::ostream& operator<<(std::ostream& out, const Frame& frame)
{
     out << "length " << frame.m_length
               << " data " << frame.m_payload <<  " origin "
               << (frame.m_origin == Frame::Origin::Server ? "Server" : "Client");
     return out;
}

int main()
{
     A a(1);
     a = a + 2;
     std ::cout << "Result " << a.getA() << std::endl;
     a = 3 + a;
     std ::cout << "Result " << a.getA() << std::endl;

     std::string str("23");
     a = a + str;
     std ::cout << "Result sum string " << a.getA() << std::endl;

     Frame f(10, "Test frame", Frame::Origin::Client);
     std::cout << "Frame details: " << f << std::endl;

     return 0;
}
```

```cpp
// Trimmed excerpt — full runnable example: examples/02-cpp-oop/12-operators-overloading/28_operator_overload_samples.cpp
#include <iostream>
#include <vector>

// typecast target used by Fraction::operator TypeCastFraction() below
class TypeCastFraction
{
public:
    TypeCastFraction(int numerator, int denominator) : m_tc_numerator{numerator}, m_tc_denominator{denominator} {}
    friend std::ostream& operator<<(std::ostream& out, const TypeCastFraction& fraction)
    {
        out << fraction.m_tc_numerator << "/" << fraction.m_tc_denominator;
        return out;
    }
private:
    int m_tc_numerator;
    int m_tc_denominator;
};

class Fraction
{
public:
    Fraction(int numerator, int denominator) : m_numerator{numerator}, m_denominator{denominator} {}

    // unary: negation
    Fraction operator-() const { return Fraction(-m_numerator, m_denominator); }

    // comparison (representative — the full example also has ==, <=)
    bool operator>=(const Fraction& right)
    {
        return (m_numerator * right.m_denominator >= right.m_numerator * m_denominator);
    }

    // binary arithmetic
    Fraction operator+(const Fraction& right)
    {
        int numerator = m_numerator * right.m_denominator + right.m_numerator * m_denominator;
        int denominator = m_denominator * right.m_denominator;

        // simplify
        int dividor = pgcd(numerator, denominator);

        return Fraction(numerator / dividor, denominator / dividor);
    }

    // prefix/postfix increment (the "int" dummy parameter marks postfix)
    Fraction& operator++() { m_numerator += m_denominator; return *this; } // prefix ++Fraction
    Fraction operator++(int) // postfix Fraction++
    {
        Fraction temporary{*this}; // save a copy
        ++(*this); // call prefix increment
        return temporary;
    }

    // functor: object called like a function, overloaded on its parameter
    double operator()() const { return static_cast<double>(m_numerator) / static_cast<double>(m_denominator); }
    double operator()(double d) { return (*this)() + d; }

    // stream-insertion via friend function
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << "/" << fraction.m_denominator;
        return out;
    }

    // typecast operators: to a built-in type, and to a user-defined type
    operator double() const { return (*this)(); } // no return type in the declaration
    operator TypeCastFraction() const { return TypeCastFraction(m_numerator, m_denominator); }
private:
    int pgcd(int a, int b) { return b != 0 ? pgcd(b, a % b) : a; }
    int m_numerator;
    int m_denominator;
};

class FractionList
{
public:
    void insert(const Fraction& fraction)
    {
        fractions.push_back(fraction);
    }

    // subscript operator, returned by reference so callers can read/write it
    Fraction& operator[](int index)
    {
        return fractions[index];
    }
private:
    std::vector<Fraction> fractions;
};

void printClassTypeCast(const TypeCastFraction& fraction)
{
    std::cout << "Implicit typecast " << fraction << std::endl;
}

int main()
{
    Fraction a(1, 3); // 1/3
    Fraction b(1, 4); // 1/4

    std::cout << "Sum " << (a + b) << std::endl 
              << "-a " << (-a) << std::endl
              << "a >= b " << (a >= b) << std::endl
              << "prefix increment a " << ++a << std::endl
              << "postfix increment b " << b++ << std::endl
              << "a value " << a() << " add double " << a(1.666667) << std::endl;

    FractionList list;
    list.insert(a);
    list.insert(b);
    std::cout << "List[1]=" << list[1] << std::endl;

    double d = static_cast<double>(a); // typecast operator
    printClassTypeCast(a);
    return 0;
}
```
