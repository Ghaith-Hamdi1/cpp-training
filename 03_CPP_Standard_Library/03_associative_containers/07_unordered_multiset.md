# std::unordered_multiset

- `std::unordered_multiset` is an associative container that contains elements that don't follow a specific order
- Elements can be duplicated
- Elements cannot be modified (change value) to not corrupt the container
- Objects that are stored in `unordered_multiset` need to overload `operator==`

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/03_associative_containers/43_unordered_multiset.cpp
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
std::ostream& operator<<(std::ostream& out, const std::unordered_multiset<T>& set)
{
    int count{0};
    out << "UnorderedMultiSet print" << std::endl;
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
    std::unordered_multiset<A> aset;
    aset.emplace(10);
    aset.emplace(A(1));
    aset.insert({A(6), A(2)}); // duplicates across inserts are kept
    std::cout << aset << std::endl;

    aset.emplace(A(1));
    std::cout << "Value 1 is duplicated \n" << aset << std::endl;

    auto it = aset.find(A(1));
    std::cout << "Find A(1) --> " << *it << std::endl;

    return 0;
}
```

