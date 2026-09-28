#include <iostream>
#include <string>
#include <vector>

class A 
{
public:
    A();
    A(int x, int y = 1);
    A(const A& a);
    A(A&& a);
    virtual ~A();

    void setId(const std::string& id);

    std::string getId() const;    
private:
    std::string id;
};

class B
{
public:
    B(int x);
};

B::B(int x)
{
    std::cout << "B constructor " << x << std::endl;
}

class C
{
public:
    C();
};

C::C()
{
    std::cout << "C default constructor" << std::endl;
}


class D
{
public:
    D();
private:
    C c;
    B b;
};

D::D() : b(1)
{
    std::cout << "D default constructor" << std::endl;
}

A::A() : id("")
{
    std::cout << "A Default constructor" << std::endl;
}

A::A(int x, int y) : id{std::to_string(x)}
{
    std::cout << "A Constructor with int parameters " << x << ", " << y << std::endl;
}

A::A(const A& a) : id{ a.id }
{
    // have to define the copy processing
    std::cout << "A Copy constructor " << a.id << std::endl;
}

A::A(A&& a)
{
    // have to define the move processing
    std::cout << "A Move constructor " << a.id << std::endl;
    this->id = std::move(a.id);
}

A::~A() 
{
    std::cout << "A destructor called" << std::endl;
}

void A::setId(const std::string& id)
{
    this->id = id;
}

std::string A::getId() const 
{
    return id;
}

struct STR
{
    int a;
    int b;
    float c;
};

int main()
{

    // STR str(1, 2, 3.0f); // error no corresponding constructor
    STR str{1, 2, 3.0f}; // correct, init list
    std::cout << "STR members " << str.a << ", " << str.b << ", " << str.c << std::endl;

    A a1;
    a1.setId(std::string("a10"));
    std::cout << "a1 " << a1.getId() << std::endl;
    A a2 = a1;
    std::cout << "a2 " << a2.getId() << std::endl;

    A a3{a1};
    std::cout << "a3 " << a3.getId() << std::endl;

    A a4(std::move(a1));
    std::cout << "a4 " << a4.getId() << std::endl;
    
    a4.setId("a4");

    A a5{1, 2};
    A a6{5};

    A a7 = std::move(a6);
    a6.setId("30");
    std::cout << "After move " << a6.getId() << std::endl;

    std::string s1{"Test"};
    std::string s2{std::move(s1)};
    // move well managed s1 is invalid after move
    std::cout << "Move string " << s2 << " old string " << s1 << std::endl;
    
    // instantiation order of attributes checking
    D d;

    return 0;
}