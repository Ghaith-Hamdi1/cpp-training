# std::map

- `std::map` is an associative container that holds key-value pairs
- Pairs are stored in sorted way, default is ascending order
- Comparison is done on keys for ordering pairs
- Keys are unique within each map (using an already existing key will override the corresponding value)
- Using the `operator[]` creates a pair if it does not exist, so the value existence does not have to be checked using this operator

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/03_associative_containers/38_map.cpp
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

// single template covers std::map<K,V> (default less<K>) and std::map<K, V, Compare>
template<typename K, typename V, typename Compare>
std::ostream& operator<<(std::ostream& out, const std::map<K, V, Compare>& map)
{
    int count{0};
    out << "Map print" << std::endl;
    for (auto& it : map)
    {
        out << "\tIndex=" << count++ << " -> " << it.first << "/" << it.second << std::endl;
    }
    return out;
}

int main()
{
    std::map<int, A> amap;
    amap[10] = A(10); // insert with key 10
    amap.emplace(3, 3);
    amap.insert({{2, A(2)}, {1, A(1)}});
    std::cout << amap << std::endl;

    std::cout << amap[0] << std::endl; // 0 doesn't exist, creates a new element by calling default constructor
    std::cout << amap << std::endl;

    if (amap.find(10) != amap.end())
    {
        std::cout << amap[10] << std::endl;
    }

    std::map<int, A, std::greater<int>> amap2; // custom sort order
    amap2[10] = A(10);
    amap2.emplace(3, 3);
    std::cout << amap2 << std::endl;

    try
    {
        std::cout << "At 11 doesn't exist " << amap2.at(11) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
    }

    return 0;
}
```

