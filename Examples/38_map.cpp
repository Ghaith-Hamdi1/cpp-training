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
std::ostream& operator<<(std::ostream& out, const std::map<K,V>& map)
{
    int count{0};
    out << "Map print" << std::endl;
    for (auto& it : map)
    {
        out << "\tIndex=" << count++ << " -> " << it.first << "/" << it.second << std::endl;
    }
    return out;
}
template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::map<K, V, std::greater<K> >& map)
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
    amap[10] = A(10); // insert with key 0 and value A(0)
    amap.emplace(3, 3);
    amap.insert({{2, A(2)}, {1, A(1)}});

    std::cout << amap << std::endl;

    std::cout << amap[0] << std::endl; // 0 doesn't exist, creates a new element by calling default constructor

    std::cout << amap << std::endl;

    if (amap.find(10) != amap.end())
    {
        std::cout << amap[10] << std::endl;
    }
    std::map<int, A, std::greater<int>> amap2;
    amap2[10] = A(10); // insert with key 0 and value A(0)
    amap2.emplace(3, 3);
    amap2.insert({{2, A(2)}, {1, A(1)}});

    std::cout << amap2 << std::endl;

    try
    {
        std::cout << "At 10" << amap2.at(10) << std::endl;
        std::cout << "At 11 doesn't exist " << amap2.at(11) << " this will not be displayed" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
    }
    
    return 0;
}