# Polymorphism

- Polymorphism is the ability of an object or function to take multiple forms
- Generally, it allows accessing object through the same interface
- We call interface a pure virtual class (which have at least one pure virtual method)
- Each derived class (subclass) can have its own behavior for given method by implementing its own version of that method
- Polymorphism types in C++
  - Compile time polymorphism (will be detailed in next chapter)
    - Functions overloading
    - Operators overloading
  - Runtime polymorphism (called also early binding polymorphism)
    - Compiler cannot decide which form of object to be used, it will be decided at runtime
- Runtime polymorphism conditions in C++ (mandatory)
  - Use pointer or reference on the base class
  - Functions must be virtual (keyword used to indicate that the non-static function support the dynamic dispatch)
  - [Diagram — code screenshot with captions: "virtual keyword in base class:", "virtual keyword optional in derived class:", "Pointer or reference used". These captions were interleaved/garbled in the raw extraction (overlapping text boxes); reconstructed here from the `-layout` cross-check — see Conversion notes.]
- Base class passed in function parameter
  - Function should be virtual
  - Should be passed by reference or by address
- Heterogeneous lists: collection of objects based on same interface
  - Derived classes should be polymorphic
  - Do not call virtual method in constructor of destructor

```cpp
// Trimmed excerpt — full runnable example: examples/course/02-cpp-oop/09-polymorphism/22_polymorphism.cpp
#include <iostream>
#include <vector>

class Base
{
public:
     virtual void virtualFunc() const { std::cout << "Base class impl" << std::endl; }
};
class Derived1 : public Base
{
public:
     void virtualFunc() const { std::cout << "Derived1 class impl" << std::endl; }
}; 
class Derived2 : public Base
{
public:
     void virtualFunc() const { std::cout << "Derived2 class impl" << std::endl; }
};

// base class passed by reference: the call still dispatches at runtime
void callVirtual(const Base& base)
{
    base.virtualFunc();
}

int main()
{
     Derived1 drv1;
     Derived2 drv2;

     // heterogeneous list: same interface (Base*), different runtime behavior
     std::vector<Base*> vect {&drv1, &drv2};
     for (int i = 0; i < vect.size(); i++)
     {
          vect[i]->virtualFunc();
     }

     callVirtual(drv1);
     callVirtual(drv2);

     return 0;
}
```
