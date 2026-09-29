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
// Examples/02_CPP_OOP/12_operators_overloading/26_assignment_move_operators.cpp
#include <iostream>

class A {
public:
    A() : m_ptr{nullptr}
    {
    }
    void createPtr() {
        removePtr();
        m_ptr = new int;
    }
    void removePtr() 
    {
        if (m_ptr != nullptr)
        {
            delete m_ptr;
            m_ptr = nullptr;
        }
    }
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

    virtual ~A()
    {
        removePtr();
    }
private:
    int * m_ptr;
};

A generateA()
{
    A a;

    return a; // rule in C++, l-value returned 
              // by value will favorize move than copy
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
    - Comparison: `==`, `>=`, `<=`
    - Subscript: `[]`
    - Parentheses (functor) `()` with arbitrary parameter number
    - Typecast samples

```cpp
// Examples/02_CPP_OOP/12_operators_overloading/27_operators_overloading.cpp
#include <string>
#include <iostream>

class A
{
public:
     explicit A(const int& value): m_value{value} {}
     int getA() const { return m_value; }
     A& operator=(A&& a) { m_value = a.m_value; return *this; }
     A(A&& a) : m_value {a.m_value} {}
     friend A operator+(const A& a, int);
     friend A operator+(int x, const A& a)
     { 
          A aRes(x + a.m_value);
          return aRes;
     }

     // member operator
     A operator+(std::string& str);
private:
     int m_value;
};

A A::operator+(std::string& str)
{
    m_value += std::atoi(str.c_str());
    return A(m_value);
}

A operator+(const A& a, int x)
{
     return x + a;
}
A operator+(const A& a, const A& b)
{
     int x = a.getA() + b.getA();
     return A(x);
}
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

std::ostream& operator<<(std::ostream& out, const Frame::Origin& origin)
{
    out << (origin == Frame::Origin::Server ? "Server" : "Client");
    return out;
}

std::ostream& operator<<(std::ostream& out, const Frame& frame)
{
     out << "length " << frame.m_length
               << " data " << frame.m_payload <<  " origin " 
               << frame.m_origin;
     return out;
}

int main()
{
     A a(1);
     a = a + 2;
     std ::cout << "Result " << a.getA() << std::endl;
     a = 3 + a;
     std ::cout << "Result " << a.getA() << std::endl;
     A a1(2);
     std::cout << "Sum " << (a + a1).getA() << std::endl;
     
     std::string str("23");
     a = a + str;
     std ::cout << "Result sum string " << a.getA() << std::endl;

     Frame f(10, "Test frame", Frame::Origin::Client);
     std::cout << "Frame details: " << f << std::endl;

     return 0;
}
```

```cpp
// Examples/02_CPP_OOP/12_operators_overloading/28_operator_overload_samples.cpp
#include <iostream>
#include <exception>
#include <vector>

class TypeCastFraction
{
public:
    TypeCastFraction(int numerator, int denominator) : m_tc_numerator{numerator}, m_tc_denominator{denominator}
    {
        if (m_tc_denominator == 0)
        {
            throw std::runtime_error("Denominator cannot be equal to 0");
        }
    }
    // rule of 5
    TypeCastFraction(const TypeCastFraction&) = default;
    TypeCastFraction(TypeCastFraction&&) = default;
    TypeCastFraction& operator=(const TypeCastFraction&) = default;
    TypeCastFraction& operator=(TypeCastFraction&&) = default;
    virtual ~TypeCastFraction() = default;
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
    Fraction(int numerator, int denominator) : m_numerator{numerator}, m_denominator{denominator}
    {
        if (m_denominator == 0)
        {
            throw std::logic_error("Denominator cannot be equal to 0");
        }
    }
    Fraction& test()
    {
        std::cout << "Test " << std::endl;
        return *this;
    }
    // rule of 5
    Fraction(const Fraction&) = default;
    Fraction(Fraction&&) = default;
    Fraction& operator=(const Fraction&) = default;
    Fraction& operator=(Fraction&&) = default;
    virtual ~Fraction() = default;

    Fraction operator-() const
    {
        // negative unary operator is built-in for int
        return Fraction(-m_numerator, m_denominator);
    }

    bool operator==(const Fraction& right)
    {
        return (m_denominator * right.m_numerator == m_numerator * right.m_denominator);
    }

    Fraction operator+(const Fraction& right)
    {
        int numerator = m_numerator * right.m_denominator + right.m_numerator * m_denominator;
        int denominator = m_denominator * right.m_denominator;

        // simplify
        int dividor = pgcd(numerator, denominator);

        return Fraction(numerator / dividor, denominator / dividor);
    }

    Fraction operator-(const Fraction& right)
    {
        return (*this + (-right));
    }

    bool operator>=(const Fraction& right)
    {
        if (m_numerator * right.m_denominator >= right.m_numerator * m_denominator)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    bool operator<=(const Fraction& right)
    {
        if (*this == right || !(*this >= right))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Fraction& operator++() // prefix increment ++Fraction
    {
        m_numerator += m_denominator;
        return *this;
    }
    Fraction& operator--() // prefix decrement --Fraction
    {
        m_numerator -= m_denominator;
        return *this;
    }

    Fraction operator++(int)  // postfix
    {
        Fraction temporary{*this}; // save a copy
        ++(*this); // call prefix increment
        return temporary;
    }
    Fraction operator--(int)
    {
        Fraction temporary{*this}; // save a copy
        --(*this); // call prefix decrement
        return temporary;
    }

    // functor
    double operator()()
    {
        return (static_cast<double>(m_numerator) / static_cast<double>(m_denominator));
    }
    double operator()() const
    {
        return (static_cast<double>(m_numerator) / static_cast<double>(m_denominator));
    }
    double operator()(double d)
    {
        return ((*this)() + d);
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << "/" << fraction.m_denominator;
        return out;
    }

    // special operator (typecast)
    operator double() const // no return for typecast operators
    {
        std::cout << "Call typecast" << std::endl;
        return ((*this)()); // call double operator()() const
    }
    // typecast to TypeCastFraction
    operator TypeCastFraction() const 
    {
        std::cout << "Tpecast TypeCastFraction" << std::endl;
        return TypeCastFraction(m_numerator, m_denominator);
    }
private:
    int pgcd(int a, int b)
    {
        return b != 0 ? pgcd(b, a % b) : a;
    }
    int m_numerator;
    int m_denominator;
};

class FractionList
{
public:
    FractionList() {}
    // rule of 5
    FractionList(const FractionList&) = default;
    FractionList(FractionList&&) = default;
    FractionList& operator=(const FractionList&) = default;
    FractionList& operator=(FractionList&&) = default;
    virtual ~FractionList() = default;

    void insert(const Fraction& fraction)
    {
        fractions.push_back(fraction);
    }

    Fraction& operator*()
    {
        if (!fractions.empty())
        {
            return (*this)[0];
            // return fractions[0]; // it works as well
        }
        else 
        {
            throw std::range_error("Index value invalid");
        }
    } 
    Fraction* operator->()
    {
        if (fractions.size() > 1)
        {
            return &(*this)[1];
            // return fractions[0]; // it works as well
        }
        else 
        {
            throw std::range_error("Index value invalid");
        }
    } 

    Fraction& operator[](int index) // return by reference to have the real value
    {
        if (index >= 0 && index < fractions.size())
        {
            return fractions[index];
        }
        else
        {
            throw std::range_error("Index value invalid");
        }

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
              << "Diff " << (a - b) << std::endl
              << "a >= b " << (a >= b) << std::endl
              << "prefix increment a " << ++a << std::endl
              << "postfix incrrement b "<< b++ << std::endl
              << "a value " << a() << " add double " << a(1.666667) << std::endl;
    std::cout << "Check b postfix increment " << b << std::endl;

    FractionList list;
    list.insert(a);
    list.insert(b);

    std::cout << "List[1]=" << list[1] << std::endl;
    std::cout << "List[0]=" << *list << std::endl;
    std::cout << "List[1]=" << list->test() << std::endl;

    double d = static_cast<double>(a); // typecast operator
    
    printClassTypeCast(a);
    return 0;
}
```
