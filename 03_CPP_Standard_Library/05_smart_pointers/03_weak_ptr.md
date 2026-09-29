# std::weak_ptr\<T\>

- `std::weak_ptr<T>` was designed to resolve the circular dependency issue
- It is just an observer of `shared_ptr`, not an owner
- It must be converted to `shared_ptr` using the `lock()` method to access the resource
- To solve the previous circular dependency, the `circular` member is made a `weak_ptr` (it will just monitor and not hold the object), so the destructor is called

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/05_smart_pointers/48_weak_ptr.cpp
#include <iostream>
#include <memory>



class X
{
    std::weak_ptr<X> circular;
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
    void print() 
    {
        std::cout << "Print " << id << std::endl;
    }
};

int main()
{
    auto x1 = std::make_shared<X>("X1");
    auto x2 = std::make_shared<X>("X2");

    x1->setCircular(x2);
    x2->setCircular(x1);

    // use of weak_ptr

    auto x3 = std::make_shared<X>("X3");
    auto weak = std::weak_ptr<X>(x3);
    weak.lock()->print();
    return 0;
}
```

---

