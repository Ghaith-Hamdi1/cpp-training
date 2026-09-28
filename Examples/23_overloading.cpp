#include <iostream>
#include <vector>
#include <functional>

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