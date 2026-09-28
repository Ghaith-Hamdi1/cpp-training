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