# std::unordered_set

- `std::unordered_set` is an associative container that contains elements that don't follow a specific order
- Elements should be unique -> it uses a hash algorithm for storage to allow fast access to elements
- Elements cannot be modified (change value) to not corrupt the container
- Objects that are stored in `unordered_set` need to overload `operator==`

```cpp
// Source: Examples/03_CPP_Standard_Library/03_associative_containers/41_unordered_set.cpp
#include <iostream>
#include <unordered_set>

class A
{
public:
    A() : m_x{0} {}
    explicit A(int x) : m_x{x} {}

    int getX() const { return m_x; }

    bool operator==(const A& a) const
    {
        return (m_x == a.m_x);
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
std::ostream& operator<<(std::ostream& out, const std::unordered_set<T>& set)
{
    int count{0};
    out << "Set print" << std::endl;
    for (auto& it : set)
    {
        out << "\tIndex=" << count++ << " -> " << it << std::endl;
    }
    return out;
}

// template specialization to create an overload of hash for A
// the hash should be unique
namespace std {
    template<>
    struct hash<A>
    {
        size_t operator()(const A& a) const
        {
            return hash<int>()(a.getX());
        } 
    };
}

int main()
{
    std::unordered_set<int> iset1 {6, 2, 10, 5, 1, 1, 1, 1};
    std::cout << iset1 << std::endl;

    std::unordered_set<A> aset;
    aset.insert({A(6), A(2), A()});
    aset.insert(A(5));
    aset.emplace(10);
    aset.emplace(A(1));
    std::cout << aset << std::endl;

    aset.emplace(A(1));
    std::cout << "No change after inserting the same value \n" << aset << std::endl;

    auto it = aset.find(A(5));
    std::cout << "Find A(5) --> " << *it << std::endl;

    return 0;
}
```

