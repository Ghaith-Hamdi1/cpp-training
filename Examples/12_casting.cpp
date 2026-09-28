#include <iostream>
int fun(int* ptr)
{
    *ptr = *ptr + 10;
    return (*ptr);
}

class A {
public:
    A(){};
    virtual ~A() = default;
};

class B : public A 
{
public:
    B(){}
    virtual ~B() = default;
};

class C : public A 
{
public:
    C(){}
    virtual ~C() = default;
};

int main(){
    int a = static_cast<int>('R');
    auto c = static_cast<char>(a);

    std::cout << "Static cast " << a << " " << c << std::endl;

    int val = 10;
    const int *ptr {&val}; 
    int *ptr1 = const_cast <int *>(ptr);
    fun(ptr1);
    std::cout << "Const cast " << val << std::endl;

    A * ab = new B;
    A * ac = new C;

    B * bb = dynamic_cast<B*>(ab);
    B * bc = dynamic_cast<B*>(ac);

    std::cout << "Dynamic cast bb is B " << (bb != nullptr) << " bc is B " << (bc != nullptr) << std::endl;
    delete ab;
    delete ac;

    int intVal[4]{0, 1, 2, 3};
    char * charPtr {nullptr};
    
    std::cout << "Reinterprete cast: " << std::endl;
    charPtr = reinterpret_cast<char*>(&intVal[0]);
    // according to endianess
    for (int i = 0; i < sizeof(intVal); i++){
        std::cout << "i =" << std::dec << i << std::hex << " -> 0x" << static_cast<int>(charPtr[i]) << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
