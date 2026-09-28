#include <iostream>
#include <array>
#include <exception>

class A
{
public:
    A() : m_x{0} {}
    A(int x) : m_x{x} 
    {
    }
    int getX() const {return m_x;}
private:
    int m_x;
};

int main()
{
    // call user defined constructor
    // std::array<A, 6> array_of_A {A(1), A(2), A(3), A(4), A(5),A(6)};
    std::array<A, 6> array_of_A; // call default constructor A() with m_x = 0
    std::cout << "Array size " << array_of_A.size() << " isEmpty()=" << array_of_A.empty() << std::endl;
    try 
    {
        std::cout << "In range value " << array_of_A.at(2).getX() << std::endl;
        // out of range, throws exception
        array_of_A.at(6).getX();
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Out range value " << e.what() << std::endl;
    }

    std::cout << "Using operator[] " << array_of_A[4].getX() << std::endl;
    std::cout << "Array size " << array_of_A.size() << " isEmpty()=" << array_of_A.empty() << std::endl;
    std::cout << "Front element " << array_of_A.front().getX() << " back element " << array_of_A.back().getX() << std::endl;

    array_of_A.fill(A(10));
    std::cout << "Using operator[4] " << array_of_A[4].getX() << std::endl;

    return 0;
}