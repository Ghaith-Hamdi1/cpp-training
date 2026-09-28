#include <iostream>


int main() {
    int a{2};
    int b{3};
    int c{0};
    
    // different precedence
    c = a << b + 3;
    std::cout << "Different precedence " << c << std::endl;

    // same precedence (left to right in this case)
    c = a * b % 2;
    std::cout << "Same precedence " << c << std::endl;

    // unary prefix operator
    c = b++ * a;
    std::cout << "Unary prefix " << c << std::endl;

    // unary postfix operator
    c = ++b * a;
    std::cout << "Unary postfix " << c << std::endl;

    a = 5;
    b = 6;
    c = 9;
    int d{10};
    std::cout << "Complex operation " << ( a || b && c || d ) << std::endl; // a || (b && c) || d; -> (a || (b && c)) || d;

    int z{0};
    int y{5};
    z *= ++y + 5; // z *= ((++y) + 5);
    int x{10};
    y = 8;
    z = 6;
    x = y = z; // x = (y = z);

    return 0;
}