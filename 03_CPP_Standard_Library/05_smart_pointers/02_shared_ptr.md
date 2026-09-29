# std::shared_ptr\<T\>

- `std::shared_ptr<T>` is used to manage an object that will be shared by many users
- It won't be destroyed unless all shared instances go out of scope (it holds an internal counter that counts the number of shared instances and will stay alive until the counter goes back to 0)
- Copy is allowed for `shared_ptr`; it will increment the local counter instead of creating a new object (the object wrapped by `shared_ptr` remains the same)
- In C++14, we generally use `std::make_shared<T>(constructor_parameters)` to create a `shared_ptr` (very recommended for better performance)
- It can be copied as well as moved, no restrictions
- Generally it is passed by value and returned by value
- A `unique_ptr` can be converted to `shared_ptr` using a special `shared_ptr` constructor; in this case, the object of `unique_ptr` will be moved to `shared_ptr`

## Issue with shared_ptr: circular dependency

- In this case, destructors of `x1` and `x2` are **not called**!!
- What happens? When `x1` goes out of scope (`shared_ptr`), it is already held by `x2` and vice versa -> `use_count` is not 0 -> destructor is not called
- *(the on-slide code diagram illustrating this was an embedded image, not extractable as text; the equivalent circular-reference pattern is reconstructed below from `Examples/03_CPP_Standard_Library/05_smart_pointers/47_shared_ptr.cpp`'s `X` class)*

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/05_smart_pointers/47_shared_ptr.cpp
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
        circular = c;
    }
};

int main()
{
    std::shared_ptr<A> aPtr = std::make_shared<B>(100);
    aPtr->foo(); // polymorphic
    std::cout << "Use count " << aPtr.use_count() << std::endl;
    {
        std::shared_ptr<A> aPtr2 {aPtr}; // copy increments the shared counter
        std::cout << "Use count for second instance " << aPtr2.use_count()
                  << " and for first " << aPtr.use_count() << std::endl;
        aPtr2->foo(); // still polymorphic
    }
    std::cout << "Use count after scope ends " << aPtr.use_count() << std::endl;

    aPtr = passValue(aPtr);
    std::cout << "Use count after passValue " << aPtr.use_count() << std::endl;
    aPtr = passValueReference(aPtr);
    std::cout << "Use count after passValueReference " << aPtr.use_count() << std::endl;
    aPtr = passRValue(std::move(aPtr));
    std::cout << "Use count after passRValue with move " << aPtr.use_count() << std::endl;

    // circular reference issue: destructors of x1 and x2 won't be called!
    auto x1 = std::make_shared<X>("X1");
    auto x2 = std::make_shared<X>("X2");

    x1->setCircular(x2);
    x2->setCircular(x1);

    std::cout << x1.use_count() << " " << x2.use_count() << std::endl;

    return 0;
}
```

