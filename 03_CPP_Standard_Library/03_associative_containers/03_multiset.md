# std::multiset

- `std::multiset` is an associative container that holds sorted elements (keys)
- Unlike set, multiset can hold duplicate keys
- Default sorting order is ascending
- Same as set, key object needs to have comparison operator

```cpp
// Source: Examples/03_CPP_Standard_Library/03_associative_containers/39_multiset.cpp
#include <iostream>
#include <set>

class A
{
public:
    A() : m_x{0} {}
    explicit A(int x) : m_x{x} {}

    bool operator<(const A& a) const
    {
        return (m_x < a.m_x);
    }

    bool operator>(const A& a) const
    {
        return (m_x > a.m_x);
    }

    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::multiset<T>& set)
{
    int count{0};
    out << "Set print" << std::endl;
    for (auto& it : set)
    {
        out << "\tIndex=" << count++ << " -> " << it << std::endl;
    }
    return out;
}
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::multiset<T, std::greater<T> >& set)
{
    int count{0};
    out << "Set print" << std::endl;
    for (auto& it : set)
    {
        out << "\tIndex=" << count++ << " -> " << it << std::endl;
    }
    return out;
}

int main()
{
    std::multiset<int> iset1 {6, 2, 10, 5, 1, 1, 2, 6, 10};
    std::multiset<int, std::greater<int> > iset2 {6, 2, 10, 5, 1, 1, 2, 6, 10};
    std::cout << iset1 << std::endl;
    std::cout << iset2 << std::endl;

    std::multiset<A> aset;
    aset.insert({A(6), A(2), A()});
    aset.insert(A(5));
    aset.emplace(10);
    aset.emplace(A(1));
    aset.emplace(1);
    aset.emplace(1);
    aset.emplace(10);
    std::cout << aset << std::endl;

    std::multiset<A, std::greater<A> > aset2; // needs operator>
    aset2.emplace(2);
    aset2.emplace(2);
    aset2.emplace(2);
    aset2.emplace(4);
    aset2.emplace(20);
    std::cout << aset2 << std::endl;

    auto it = aset.find(A(5));
    std::cout << "Find A(5) --> " << *it << std::endl;
    
    auto pair = aset.equal_range(A(1));
    std::cout << "Equal range: " << *pair.first << " - " << *pair.second << std::endl;

    auto lower = aset.lower_bound(A(1));
    std::cout << "Lower bound: " << *lower << std::endl;
    auto upper = aset.upper_bound(A(1));
    std::cout << "Upper bound: " << *upper << std::endl;

    return 0;
}
```

