# std::multimap

- `std::multimap` is an associative container that holds key-value pairs
- Pairs are stored in sorted way, default is ascending order
- Comparison is done on keys for ordering pairs
- Multimap allows duplication of keys
- Using the `operator[]` and `at()` function is not allowed unlike map

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/03_associative_containers/40_multimap.cpp
#include <iostream>
#include <map>

class A
{
public:
    A() : m_x{0} {}
    explicit A(int x) : m_x{x} {}

    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

// single template covers std::multimap<K,V> (default less<K>) and std::multimap<K, V, Compare>
template<typename K, typename V, typename Compare>
std::ostream& operator<<(std::ostream& out, const std::multimap<K, V, Compare>& map)
{
    int count{0};
    out << "Multimap print" << std::endl;
    for (auto& it : map)
    {
        out << "\tIndex=" << count++ << " -> " << it.first << "/" << it.second << std::endl;
    }
    return out;
}

int main()
{
    std::multimap<int, A> amap;
    amap.emplace(3, 3);
    amap.insert({{2, A(2)}, {1, A(1)}});
    amap.emplace(std::pair<int, A>(2, A(222))); // duplicate key 2 is kept
    std::cout << amap << std::endl;

    std::multimap<int, A, std::greater<int>> amap2; // custom sort order
    amap2.emplace(3, 3);
    amap2.insert({{2, A(2)}, {1, A(1)}});
    std::cout << amap2 << std::endl;

    return 0;
}
```

