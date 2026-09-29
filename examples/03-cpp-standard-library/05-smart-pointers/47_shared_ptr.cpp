#include <iostream>
#include <memory>
#include <string>

class A
{
public:
    explicit A(int x) : m_x{x}
    {
        std::cout << "A Allocated x=" << m_x << std::endl; 
    }
    virtual ~A()
    {
        std::cout << "A deallocated" << std::endl;
    }
    virtual void foo()
    {
        std::cout << "Foo called from A" << std::endl;
    }
private:
    int m_x;
};

class B : public A
{
public:
    explicit B(int x) : A(x)
    {
        std::cout << "B Allocated x=" << x << std::endl; 
    }
    virtual void foo() override
    {
        std::cout << "Foo called from B" << std::endl;
    }
    virtual ~B()
    {
        std::cout << "B deallocated" << std::endl;
    }
};

std::shared_ptr<A> passValue(std::shared_ptr<A> a)
{
    std::cout << "passValue use_count " << a.use_count() << std::endl;
    return a;
}

std::shared_ptr<A>& passValueReference(std::shared_ptr<A> & a)
{
    std::cout << "passValueReference use_count " << a.use_count() << std::endl;
    return a;
}

std::shared_ptr<A> passRValue(std::shared_ptr<A>&& a)
{
    std::cout << "passRValue use_count " << a.use_count() << std::endl;
    return a;
}

class X
{
    std::shared_ptr<X> circular;
    std::string id;
public:
    X(const std::string& id) : id{id} 
    {
        std::cout << id << " created" << std::endl;
    }
    virtual ~X()
    {
        std::cout << id << " destroyed" << std::endl;
    }
    void setCircular(std::shared_ptr<X> & c)
    {
        std:: cout << "Set circular " << id << " use count " << c.use_count();
        circular = c;
        std:: cout << "Set circular " << id << " use count " << circular.use_count();
    }
    void releaseCircular()
    {
        std::shared_ptr<X> x(nullptr);
        circular.swap(x);
    }
};

int main()
{
    std::shared_ptr<A> aPtr = std::make_shared<B>(100);
    aPtr->foo(); // polymorphic
    std::cout << "Use count " << aPtr.use_count() << std::endl;
    {
        std::shared_ptr<A> aPtr2 {aPtr};
        std::cout << "Use count for second instance " << aPtr2.use_count() 
                  << " and for first " << aPtr.use_count() << std::endl;
        // check that they are pointing to same object
        std::cout << "First address " << aPtr.get() << " second " << aPtr2.get() << std::endl;

        // still polymorphic
        aPtr2->foo();
    }
    std::cout << "Use count " << aPtr.use_count() << std::endl;
    passValue(aPtr);
    std::cout << "Use count after passValue" << aPtr.use_count() << std::endl;
    aPtr = passValue(aPtr);
    std::cout << "Use count after passValue with return " << aPtr.use_count() << std::endl;
    aPtr = passValueReference(aPtr);
    std::cout << "Use count after passValueReference " << aPtr.use_count() << std::endl;
    aPtr = passRValue(std::move(aPtr));
    std::cout << "Use count after passRValue with move " << aPtr.use_count() << std::endl;

    // circular reference issue
    auto x1 = std::make_shared<X>("X1");
    auto x2 = std::make_shared<X>("X2");

    x1->setCircular(x2);
    x2->setCircular(x1);

    std::cout << x1.use_count() << " " << x2.use_count() << std::endl;

    //x1->releaseCircular();
    //x2->releaseCircular();
    std::cout << x1.use_count() << " " << x2.use_count() << std::endl;

    // destructors of x1 and x2 won't be called !!
    return 0;
}