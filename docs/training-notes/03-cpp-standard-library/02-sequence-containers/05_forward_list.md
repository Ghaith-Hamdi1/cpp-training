# std::forward_list

- `std::forward_list` — a container that allows non contiguous memory allocation
- Point of strongness: supports fast insertion and removal of elements from anywhere in the container
- Point of weakness: the list has to be parsed entirely to find the wanted element
- Iteration is unidirectional (but memory space efficient compared to lists)
- Operations can be done only from front (`push_front`, `pop_front`)

```cpp
// Trimmed excerpt — full runnable example: examples/course/03-cpp-standard-library/02-sequence-containers/33_forward_list.cpp
#include <iostream>
#include <forward_list>

class A
{
public:
    explicit A(int x): m_x{x} {}

    int getX() const
    {
        return m_x;
    }
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }

    friend bool Predicate(const A& a);
private:
    int m_x;
};

std::ostream& operator<<(std::ostream& out, const std::forward_list<A>& a)
{
    out << "Forward_list print " << std::endl;
    int count{0};
    for (auto it = a.cbegin(); it != a.cend(); it++)
    {
        out << "\tindex=" << count++ << " -> " << *it << std::endl;
    }
    return out;
}

bool Predicate(const A& a)
{
    return (a.m_x % 2 == 0);
}

int main()
{
    // don't have size accessor
    std::forward_list<A> forward_list_of_A;

    forward_list_of_A.push_front(A(0));
    forward_list_of_A.emplace_front(A(1));
    for (size_t i = 2; i < 17; i++)
    {
        forward_list_of_A.emplace_front(i);
    }
    std::cout << "Final forward_list " << forward_list_of_A << std::endl;

    forward_list_of_A.remove_if(Predicate);
    std::cout << "After even deleted " << forward_list_of_A << std::endl;

    forward_list_of_A.sort([](const A& a1, const A& a2){
        return a1.getX() < a2.getX();
    });
    std::cout << "After sort " << forward_list_of_A << std::endl;
    return 0;
}
```

