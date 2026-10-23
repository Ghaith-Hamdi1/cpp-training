# std::set

- `std::set` is an associative container that stores elements (keys) so that they will be unique because the value of element identifies it
- Elements are always sorted in specific order
- Default order is ascending (first element is the lowest)
- Comparer has to be provided to change the sorting order

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/03-associative-containers/37_set.cpp
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

// single template covers std::set<T> (default less<T>) and std::set<T, Compare>
template<typename T, typename Compare>
std::ostream& operator<<(std::ostream& out, const std::set<T, Compare>& set)
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
    // duplicates are ignored, elements kept sorted ascending
    std::set<int> iset1 {6, 2, 10, 5, 1, 1, 1, 1};
    std::cout << iset1 << std::endl;

    std::set<A> aset;
    aset.insert({A(6), A(2), A()});
    aset.insert(A(5));
    aset.emplace(10);
    aset.emplace(A(1));
    std::cout << aset << std::endl;

    aset.emplace(A(1));
    std::cout << "No change after inserting the same value \n" << aset << std::endl;

    std::set<A, std::greater<A> > aset2; // needs operator>, custom sort order
    aset2.emplace(2);
    aset2.emplace(5);
    std::cout << aset2 << std::endl;

    auto it = aset.find(A(5));
    std::cout << "Find A(5) --> " << *it << std::endl;

    auto lower = aset.lower_bound(A(5));
    std::cout << "Lower bound: " << *lower << std::endl;
    auto upper = aset.upper_bound(A(5));
    std::cout << "Upper bound: " << *upper << std::endl;

    return 0;
}
```

