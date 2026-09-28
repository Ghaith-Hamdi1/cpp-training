#include <iostream>

void func1(int& x)
{
    std::cout << "Pass by reference: " << std::endl << x << " -> ";
    x++;
    std::cout << x << std::endl;
}

void func2(const int& x)
{
    std::cout << "Pass by const reference: " << std::endl << x << std::endl;
    // x++; compile error
}

void printReferenceValue(int&& x)
{
    std::cout << x << std::endl;
}
int test()
{
    return 5;
}

int main(){

    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << std::endl; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << std::endl; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref <<  std::endl; // prints 77

    func1(x);

    const int y { 100 };
    func2(x); // lvalue
    func2(y); // const lvalue
    func2(500); // rvalue

    // rvalue reference
    int&& rRef { 20 };

    std::cout << "rvalue reference: " << rRef << std::endl;
    rRef = 40;
    std::cout << "rvalue reference changed: " << rRef << "/ " << &rRef << std::endl;
    
    // This line will generate an error
    // as non-const lvalue reference of 
    // type ‘int&‘ to an rvalue of type ‘int’
    // int& lref = 10;
    int& lref = rRef; // but this works using rvalue reference

    // This line will generate an error
    // as l-value cannot be assigned
    // to the r-value references
    // printReferenceValue(x);
    printReferenceValue(10); // but this works fine
    printReferenceValue(test()); // but this works fine
    
    return 0;
}