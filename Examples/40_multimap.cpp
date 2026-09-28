#include <iostream>
#include <map>

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

template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::multimap<K,V>& map)
{
    int count{0};
    out << "Multimap print" << std::endl;
    for (auto& it : map)
    {
        out << "\tIndex=" << count++ << " -> " << it.first << "/" << it.second << std::endl;
    }
    return out;
}
template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::multimap<K, V, std::greater<K> >& map)
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
    amap.emplace(std::pair<int, A>(2, A(222)));
    std::cout << amap << std::endl;

    amap.emplace(3, 333);
    amap.emplace(3, 33);
    amap.emplace(0, 0); 
    std::cout << amap << std::endl;

    std::multimap<int, A, std::greater<int>> amap2;
    amap2.emplace(3, 3);
    amap2.insert({{2, A(2)}, {1, A(1)}});
    std::cout << amap2 << std::endl;
    
    return 0;
}