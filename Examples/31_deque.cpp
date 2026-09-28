#include <iostream>
#include <deque>

class A
{
public:
    explicit A(int x): m_x{x}
    {

    }
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

std::ostream& operator<<(std::ostream& out, const std::deque<A>& a)
{
    out << "Deque print " << std::endl;
    for (int i = 0; i < a.size(); i++)
    {
        out << "\tindex=" << i << " -> " << a[i] << std::endl;
    }
    return out;
}

int main()
{
    std::deque<A> deque_of_A;

    std::cout << "Initial state size=" << deque_of_A.size() << std::endl;
    deque_of_A.emplace_back(0); // works fine even constructor is explicit
    deque_of_A.emplace_front(0); // works fine even constructor is explicit
    std::cout << "After emplace_back size=" << deque_of_A.size() << std::endl;
    //deque_of_A.push_back(0); // doesn't work since constructor is explicit
    // checking capacity and size
    for (size_t i = 1; i < 17; i++)
    {   
        deque_of_A.push_back(A(i));
        deque_of_A.push_front(A(i));
        std::cout << "After push_back size=" << deque_of_A.size() << std::endl;
    }
    std::cout << deque_of_A << std::endl;
    deque_of_A.pop_back();
    deque_of_A.pop_front();
    std::cout << "After one pop_back and pop_front " << deque_of_A << std::endl;

    deque_of_A.clear();
    std::cout << "After clear size=" << deque_of_A.size() << std::endl;
    deque_of_A.shrink_to_fit();
    std::cout << "After shrink_to_fit size=" << deque_of_A.size() << std::endl;
    //deque_of_A.resize(10); // doesn't work since A doesn't have default constructor
    deque_of_A.resize(10, A(5));
    std::cout << "After resize size=" << deque_of_A.size() << std::endl;
    std::cout << deque_of_A << std::endl;


    return 0;
}