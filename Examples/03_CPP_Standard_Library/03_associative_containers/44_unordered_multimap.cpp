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
    std::unordered_multimap<int, int> imap {{6, 2}, {10, 5}, {1, 1}, {1, 1}};
    std::cout << imap << std::endl;

    std::unordered_multimap<A, std::string> amap;
    amap.insert({{A(6), "A(6)"}, {A(2), "A(2)"}, {A(), "A(0)"}});
    amap.insert({A(5), "A(5)"});
    amap.emplace(A(10), "A(10)");
    amap.emplace(A(1), "A(1)");
    amap.emplace(A(5), "A(555)");
    std::cout << amap << std::endl;

    amap.insert({A(1), "A(11)"});
    amap.insert({A(5), "A(55)"});
    std::cout << "After inserting the same value \n" << amap << std::endl;

    auto nb = amap.count(A(5));
    std::cout << "Find A(5) --> " << nb << std::endl;

    auto pair_it = amap.equal_range(A(5));
    if (pair_it.first != amap.end())
    {
        for (auto it = pair_it.first; it != pair_it.second; it++)
        {
            std::cout << "Value for " << it->first << " -> " << it->second << std::endl;
        }
    }
    return 0;
}