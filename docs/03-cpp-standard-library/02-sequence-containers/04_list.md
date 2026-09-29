# std::list

- `std::list` — a container that allows non contiguous memory allocation
- Point of strongness: insertion and deletion are very quick if insertion position is found
- Point of weakness: the list has to be parsed entirely to find the wanted element
- Iteration is bidirectional (will be discovered in iterators section)

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/02-sequence-containers/32_list.cpp
#include <iostream>
#include <list>

class A
{
public:
    explicit A(int x): m_x{x} {}
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::list<T>& a)
{
    out << "List print " << std::endl;
    int count{0};
    for (auto it = a.cbegin(); it != a.cend(); it++)
    {
        out << "\tindex=" << count++ << " -> " << *it << std::endl;
    }
    return out;
}

int main()
{
    std::list<A> list_of_A;

    list_of_A.push_back(A(0));
    list_of_A.push_front(A(0));
    for (size_t i = 1; i < 17; i++)
    {
        list_of_A.emplace_back(A(i));
        list_of_A.emplace_front(A(i));
    }
    std::cout << list_of_A << std::endl;
    // list_of_A[0]; // error, don't have operator[] since we have to parse all elements

    list_of_A.resize(10, A(0)); // A(0) used only if new size is bigger than old one
    std::cout << "After resize " << list_of_A << std::endl;

    // merge two sorted lists
    std::list<int> list1 = {5, 9, 1, 3, 3};
    std::list<int> list2 = {8, 7, 2, 3, 4, 4};

    list1.sort();
    list2.sort();
    list1.merge(list2);
    std::cout << "merged:" << list1 << '\n';

    // remove 3 from list1
    list1.remove(3);
    std::cout << "3 removed:" << list1 << '\n';
    list1.remove_if([](int n){
        return n % 2 != 0; // remove odd
    });
    std::cout << "Odd removed:" << list1 << '\n';

    return 0;
}
```

