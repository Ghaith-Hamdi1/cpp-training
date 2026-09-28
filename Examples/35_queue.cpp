#include <iostream>
#include <queue>

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

int main()
{
    std::queue<A> queue_of_A;

    queue_of_A.push(A(0));
    queue_of_A.emplace(A(1));
    queue_of_A.emplace(2);

    std::cout << "Size of queue " << queue_of_A.size() << std::endl;
    std::cout << "Element on top " << queue_of_A.front() << " and at the end " << queue_of_A.back() << std::endl;

    queue_of_A.emplace(A(3));
    std::cout << "Element on top " << queue_of_A.front() << " and at the end " << queue_of_A.back() << std::endl;

    queue_of_A.pop(); // remove element on top
    std::cout << "Element on top " << queue_of_A.front() << " and at the end " << queue_of_A.back() << std::endl;


    return 0;
}