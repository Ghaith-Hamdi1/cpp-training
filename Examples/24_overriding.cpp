#include <iostream>
#include <vector>
#include <functional>

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
class Derived2 : public Base
{
public:
     void virtualFunc() const override { std::cout << "Derived2 class impl" << std::endl; }
};

class Derived21 : public Derived2
{
public:
     void virtualFunc() const override { std::cout << "Derived21 class impl" << std::endl; }
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
    Derived21 drv21;
    Base& base = drv21;
    Base * pbase = &drv21;

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