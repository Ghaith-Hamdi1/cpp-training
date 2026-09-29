#include <iostream>
#include <vector>
#include <functional>

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

void callVirtual(const Base& base)
{
    base.virtualFunc();
}

int main()
{
     Derived1 drv11;
     Derived1 drv12;
     Derived2 drv21;
     Derived2 drv22;
     std::vector<Base* > vect2 {&drv11, &drv21, &drv12, &drv22};
     for(int i = 0; i < vect2.size(); i++)
     {
          vect2[i]->virtualFunc();
     }
     
     std::vector<std::reference_wrapper<Base> > vect;
     vect.push_back(drv11);
     vect.push_back(drv21);
     vect.push_back(drv12);
     vect.push_back(drv22);
     for(int i = 0; i < vect.size(); i++)
     {
          vect[i].get().virtualFunc();
     }

     callVirtual(drv11);
     callVirtual(drv22);

     return 0;
}