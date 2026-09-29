# std::unordered_multimap

- `std::unordered_multimap` is an associative container that stores key value pairs without sorting
- Must define a template specialization for `std::hash` with specific `key` type if the `key` type is not a native type
- Element keys are not unique
- Objects that are stored in `unordered_multimap` need to overload `operator==`
- The `operator[]` and `at()` function are not available for `unordered_multimap`

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/03-associative-containers/44_unordered_multimap.cpp
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
std::ostream& operator<<(std::ostream& out, const std::unordered_multimap<K, V>& map)
{
    int count{0};
    out << "Unordered_multimap print" << std::endl;
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
    std::unordered_multimap<A, std::string> amap;
    amap.insert({{A(6), "A(6)"}, {A(2), "A(2)"}});
    amap.emplace(A(5), "A(5)");
    amap.emplace(A(5), "A(555)"); // duplicate key is kept
    std::cout << amap << std::endl;

    auto nb = amap.count(A(5));
    std::cout << "Count for key A(5) --> " << nb << std::endl;

    auto pair_it = amap.equal_range(A(5));
    for (auto it = pair_it.first; it != pair_it.second; it++)
    {
        std::cout << "Value for " << it->first << " -> " << it->second << std::endl;
    }

    return 0;
}
```

---

