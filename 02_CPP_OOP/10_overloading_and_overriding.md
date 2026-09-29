# Overloading and overriding

- Function Overloading: have the same function with same name in the same scope
  - Must have different function signature
    - Function signature doesn't include return type
    - Number and type of parameters are used to change function signature
  - [Diagram: same signature => compilation error; different signature => OK]
  - Compiler may perform implicit conversion for overloading matching
    - [example note: implicitly converted to int and `print(int)` is called]
- Functions overriding: redefining a function in derived class
  - Same function name and parameters
  - Base function must be declared as virtual
  - Add "override" key optionally to indicate override in derived class (generate compile error in case of signature mismatch)
- Pure virtual function or abstract function
  - Function that doesn't have a body
  - Cannot be called and must be overridden by derived classes
  - Add "= 0" at the end of pure virtual function declaration
  - Generally used to give a behavior that is undefined in base class but must be defined only by derived classes
- Pure virtual class or abstract class or interface is a class that have at least one pure virtual function
  - An abstract class can have definition of other non-pure virtual function than pure virtual function
  - An abstract class cannot be instantiated (can just be inherited)
- Virtual base class: diamond problem illustration
  - When instantiating the lower derived class, the upper base class will be instantiated twice
  - Solution: add virtual keyword to the inheritance access specifier
  - This allows sharing the base class
  - The lower derived class will be then responsible for base class creation
  - [Diagram — extracted labels: class hierarchy with `Car` at the top, `ElectricCar` and `GasolineCar` both inheriting (virtually) from `Car`, and `HybridCar` at the bottom inheriting from both `ElectricCar` and `GasolineCar` — the classic diamond shape]

```cpp
// Trimmed excerpt — full runnable example: Examples/02_CPP_OOP/10_overloading_and_overriding/23_overloading.cpp
#include <iostream>

class Base
{
public:
     virtual void virtualFunc() const { std::cout << "Const Base class impl" << std::endl; }
     virtual void virtualFunc() { std::cout << "Base class impl" << std::endl; }

     void foo(int x, int y = 1)
     {
     }
     void foo(int x) // different from the previous one
     {
     }
};
class Derived1 : public Base
{
public:
     void virtualFunc() const { std::cout << "Const Derived1 class impl" << std::endl; }
     void virtualFunc() { std::cout << "Derived1 class impl" << std::endl; }
}; 
class Derived2 : public Base
{
public:
     void virtualFunc() const { std::cout << "Const Derived2 class impl" << std::endl; }
};

void callVirtual(const Base& base)
{
    base.virtualFunc();
}
void callVirtual(Base& base)
{
    base.virtualFunc();
}

int main()
{
     Derived1 drv1;
     Derived2 drv2;
     const Derived1 cdrv1;
     const Derived2 cdrv2;
     callVirtual(drv1);
     callVirtual(cdrv1);
     callVirtual(drv2);
     callVirtual(cdrv2);
     return 0;
}
```

```cpp
// Trimmed excerpt — full runnable example: Examples/02_CPP_OOP/10_overloading_and_overriding/24_overriding.cpp
#include <iostream>

class Base
{
public:
     virtual void virtualFunc() const { std::cout << "Base class impl" << std::endl; }
     virtual ~Base() {}
};
class Derived1 : public Base
{
public:
     void virtualFunc() const override { std::cout << "Derived1 class impl" << std::endl; }
     // void virtualFunc() override {} // compile error since 
}; 

// Abstract class
class Vehicle
{
public:
    int getSpeed () const
    {
        return m_speed;
    }
    void setSpeed (int speed)
    {
        m_speed = speed;
    }
    virtual int wheelsNumber() const = 0;
    virtual ~Vehicle() {}
protected:
    int m_speed;
};

class Car : public Vehicle
{
public:
    int wheelsNumber() const override
    {
        return Car::WHEELS;
    }
private:
    static constexpr int WHEELS{4};
};


class Bicycle : public Vehicle
{
public:
    int wheelsNumber() const override
    {
        return Bicycle::WHEELS;
    }
private:
    static constexpr int WHEELS{2};
};

int main()
{
    Derived1 drv1;
    Base& base = drv1;
    Base * pbase = &drv1;

    base.virtualFunc();
    pbase->virtualFunc();

    Car car;
    Bicycle bicycle;

    Vehicle &v1 = car;
    Vehicle &v2 = bicycle;

    car.setSpeed(120);
    bicycle.setSpeed(12);

    // Vehicle v; // compile error pure virtual class

    std::cout << "Car wheels " << v1.wheelsNumber() << " bicycle wheels " << v2.wheelsNumber() << std::endl;
    std::cout << "Car speed " << v1.getSpeed() << " bicycle speed " << v2.getSpeed() << std::endl;
    return 0;
}
```

```cpp
// Examples/02_CPP_OOP/08_inheritance/25_diamond_problem.cpp
#include <iostream>

class Car 
{
public:
    Car() 
    { 
        std::cout << "Car constructor" << std::endl;
    }
    virtual ~Car() = default;
};

class ElectricCar : virtual public Car
{
public:
    ElectricCar() 
    { 
        std::cout << "ElectricCar constructor" << std::endl;
    }
};
class GasolineCar : virtual public Car
{
public:
    GasolineCar() 
    { 
        std::cout << "GasolineCar constructor" << std::endl;
    }
};
class HybridCar : public ElectricCar, public GasolineCar
{
public:
    HybridCar() 
    { 
        std::cout << "HybridCar constructor" << std::endl;
    }
};

int main()
{
    HybridCar hbr;
    // 
}
```
