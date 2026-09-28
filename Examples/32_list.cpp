#include <iostream>
#include <list>

class A
{
public:
    explicit A(int x): m_x{x}
    {

    }
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

std::ostream& operator<<(std::ostream& out, const std::list<A>& a)
{
    out << "List print " << std::endl;
    int count{0};
    for (auto it = a.cbegin(); it != a.cend(); it++)
    {
        out << "\tindex=" << count++ << " -> " << *it << std::endl;
    }
    return out;
}
std::ostream& operator<<(std::ostream& out, const std::list<int>& a)
{
    out << "List print " << std::endl;
    int count{0};
    for (auto it = a.cbegin(); it != a.cend(); it++)
    {
        out << "\tindex=" << count++ << " -> " << *it << std::endl;
    }
    return out;
}

int main()
{
    std::list<A> list_of_A;

    list_of_A.push_back(A(0));
    list_of_A.push_front(A(0));
    std::cout << "After push_back and push_front size=" << list_of_A.size() << std::endl;
    for (size_t i = 1; i < 17; i++)
    {   
        list_of_A.emplace_back(A(i));
        list_of_A.emplace_front(A(i));
    }
    std::cout << list_of_A << std::endl;
    // list_of_A[0]; // error, don't have operator[] since we have to parse all elements

    list_of_A.resize(10, A(0)); // A(0) used only if new size is bigger than old one
    std::cout << "After resize " << list_of_A << std::endl;
    list_of_A.resize(20, A(0)); // A(0) used only if new size is bigger than old one
    std::cout << "After resize " << list_of_A << std::endl;

    // merge two sorted lists
    std::list<int> list1 = {5, 9, 1, 3, 3};
    std::list<int> list2 = {8, 7, 2, 3, 4, 4};
 
    list1.sort();
    list2.sort();
    std::cout << "list1: " << list1 << '\n';
    std::cout << "list2: " << list2 << '\n';
    list1.merge(list2);
    std::cout << "merged:" << list1 << '\n';
    std::cout << "list2 after merge: " << list2 << '\n';

    // remove 3 from list1
    list1.remove(3);
    std::cout << "3 removed:" << list1 << '\n';
    list1.remove_if([](int n){
        // remove odd
        std::cout << "Predicate called" << std::endl;
        if (n % 2 != 0) {
            return true;
        }
        else {
            return false;
        }
    });
    std::cout << "Odd removed:" << list1 << '\n';

    return 0;
}