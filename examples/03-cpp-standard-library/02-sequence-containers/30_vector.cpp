#include <iostream>
#include <vector>

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
    std::vector<A> vector_of_A;

    std::cout << "Initial state capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << " max_size " << vector_of_A.max_size() << std::endl;
    vector_of_A.emplace_back(0); // works fine even constructor is explicit
    std::cout << "After emplace_back capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;
    //vector_of_A.push_back(0); // doesn't work since constructor is explicit
    // checking capacity and size
    for (size_t i = 1; i < 17; i++)
    {   
        vector_of_A.push_back(A(i));
        std::cout << "After push_back capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;
    }
    vector_of_A.shrink_to_fit();
    std::cout << "After shrink_to_fit capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;
    
    vector_of_A.clear();
    std::cout << "After clear capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;
    vector_of_A.shrink_to_fit();
    std::cout << "After shrink_to_fit capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;
    //vector_of_A.resize(10); // doesn't work since A doesn't have default constructor
    vector_of_A.resize(10, A(5));
    std::cout << "After resize capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;
    std::cout << "New values " << vector_of_A[0] << " " << vector_of_A[1] << " " << vector_of_A[9] << std::endl;

    vector_of_A.reserve(50);
    std::cout << "After reserve capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;

    vector_of_A.pop_back();
    std::cout << "After pop_back capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;

    return 0;
}