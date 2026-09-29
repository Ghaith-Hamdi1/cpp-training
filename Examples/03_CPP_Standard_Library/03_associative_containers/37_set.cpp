#include <iostream>
#include <set>

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
    int getX() const
    {
        return m_x;
    }
private:
    int m_x;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& set)
{
    int count{0};
    out << "Set print" << std::endl;
    for (auto& it : set)
    {
        out << "\tIndex=" << count++ << " -> " << it << std::endl;
    }
    return out;
}
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T, std::greater<T> >& set)
{
    int count{0};
    out << "Set print" << std::endl;
    for (auto& it : set)
    {
        out << "\tIndex=" << count++ << " -> " << it << std::endl;
    }
    return out;
}

class Comparer
{
public:
    bool operator()(const A& a1, const A& a2)
    {
        return a1.getX() > a2.getX();
    } 
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T, Comparer >& set)
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
    std::set<int> iset1 {6, 2, 10, 5, 1, 1, 1, 1};
    std::set<int, std::greater<int> > iset2 {6, 2, 10, 5, 1, 1, 1, 1};
    std::cout << iset1 << std::endl;
    std::cout << iset2 << std::endl;

    std::set<A> aset;
    aset.insert({A(6), A(2), A()});
    aset.insert(A(5));
    aset.emplace(10);
    aset.emplace(A(1));
    std::cout << aset << std::endl;

    aset.emplace(A(1));
    std::cout << "No change after inserting the same value \n" << aset << std::endl;

    std::set<A, std::greater<A> > aset2; // needs operator>
    aset2.emplace(2);
    std::cout << aset2 << std::endl;

    auto it = aset.find(A(5));
    std::cout << "Find A(5) --> " << *it << std::endl;
    
    const auto pair = aset.equal_range(A(2));
    std::cout << "Equal range: " << *pair.first << " - " << *pair.second << std::endl;

    auto lower = aset.lower_bound(A(5));
    std::cout << "Lower bound: " << *lower << std::endl;
    auto upper = aset.upper_bound(A(5));
    std::cout << "Upper bound: " << *upper << std::endl;

    std::cout << "***********************" << std::endl;
    std::set<A, Comparer> set_com;
    set_com.emplace(1);
    set_com.insert({A(3), A(5)});

    std::cout << set_com << std::endl;
    return 0;
}