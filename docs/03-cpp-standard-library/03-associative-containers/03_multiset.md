# std::multiset

- `std::multiset` is an associative container that holds sorted elements (keys)
- Unlike set, multiset can hold duplicate keys
- Default sorting order is ascending
- Same as set, key object needs to have comparison operator

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/03-associative-containers/39_multiset.cpp
#include <iostream>
#include <set>

class A
{
public:
    A() : m_x{0} {}
    explicit A(int x) : m_x{x} {}

    bool operator<(const A& a) const { return (m_x < a.m_x); }
    bool operator>(const A& a) const { return (m_x > a.m_x); }

    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

// single template covers std::multiset<T> (default less<T>) and std::multiset<T, Compare>
template<typename T, typename Compare>
std::ostream& operator<<(std::ostream& out, const std::multiset<T, Compare>& set)
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
    // duplicates are kept, elements sorted ascending
    std::multiset<int> iset1 {6, 2, 10, 5, 1, 1, 2, 6, 10};
    std::cout << iset1 << std::endl;

    std::multiset<A> aset;
    aset.insert({A(6), A(2), A()});
    aset.insert(A(5));
    aset.emplace(10);
    aset.emplace(A(1));
    aset.emplace(1);
    std::cout << aset << std::endl;

    std::multiset<A, std::greater<A> > aset2; // needs operator>, custom sort order
    aset2.emplace(2);
    aset2.emplace(2);
    aset2.emplace(4);
    std::cout << aset2 << std::endl;

    auto it = aset.find(A(5));
    std::cout << "Find A(5) --> " << *it << std::endl;

    auto pair = aset.equal_range(A(1));
    std::cout << "Equal range: " << *pair.first << " - " << *pair.second << std::endl;

    return 0;
}
```

