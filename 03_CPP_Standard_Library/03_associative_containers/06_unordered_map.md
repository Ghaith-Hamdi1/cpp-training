# std::unordered_map

- `std::unordered_map` is an associative container that stores key value pairs without sorting
- Must define a template specialization for `std::hash` with specific `key` type if the `key` type is not a native type
- Element keys should be unique -> it uses a hash algorithm for storage to allow fast access to elements
- Objects that are stored in `unordered_map` need to overload `operator==`
- The `operator[]` and `at()` function are available for `unordered_map`

```cpp
// Source: Examples/03_CPP_Standard_Library/03_associative_containers/42_unordered_map.cpp
#include <iostream>
#include <unordered_map>
#include <string>

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

template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::unordered_map<K, V>& map)
{
    int count{0};
    out << "Unordered_map print" << std::endl;
    for (auto& it : map)
    {
        out << "\tIndex=" << count++ << " -> " << it.first << "/" << it.second << std::endl;
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
    std::unordered_map<int, int> imap {{6, 2}, {10, 5}, {1, 1}, {1, 1}};
    std::cout << imap << std::endl;

    std::unordered_map<A, std::string> amap;
    amap.insert({{A(6), "A(6)"}, {A(2), "A(2)"}, {A(), "A(0)"}});
    amap.insert({A(5), "A(5)"});
    amap.emplace(A(10), "A(10)");
    amap.emplace(A(1), "A(1)");
    std::cout << amap << std::endl;

    amap.insert({A(1), "A(11)"});
    std::cout << "After inserting the same value \n" << amap << std::endl;

    auto it = amap.find(A(5));
    std::cout << "Find A(5) --> " << it->second << std::endl;

    return 0;
}
```

