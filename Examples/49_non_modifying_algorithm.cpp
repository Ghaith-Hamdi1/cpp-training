#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

class A
{
    int m_x;
public:
    explicit A(int x) : m_x{x} {
        std::cout << "Constructor A x=" << m_x << std::endl;
    }
    virtual ~A() {}

    bool operator<(const A& a) const {
        return (m_x < a.m_x);
    }
    bool operator==(const A& a) const {
        return (m_x == a.m_x);
    }
    friend std::ostream& operator<<(std::ostream& out, const A& a) {
        out << "x=" << a.m_x;
        return out;
    }

    int getX() const { return m_x; }
};

struct Printer
{
    void operator()(const A& a) {
        std::cout << "Functor for A " << a.getX() << std::endl;
    }
    void operator()(const std::pair<A, std::string>& apair) {
        std::cout << "Functor for pair " << apair.first << " / " << apair.second << std::endl;
    }
    void operator()(const int& x) {
        std::cout << "Functor for int " << x << std::endl;
    }
};

struct Even
{
    bool operator()(const A& a) {
        return (a.getX() % 2 == 0);
    }
    bool operator()(const int& x) {
        return (x % 2 == 0);
    }
};

struct Comparer
{
    bool operator()(const char& c1, const char& c2) {
        return std::tolower(c1) == std::tolower(c2);
    }
};

std::ostream& operator<<(std::ostream& out, const std::set<int>& set) {
    out << "Print Set elements:";
    std::for_each(set.cbegin(), set.cend(), [&out](const int& n){
        out << " " << n;
    });
    out << std::endl;
    return out;
}

int main()
{
    ///// std::for_each
    std::map<A, std::string> map;
    map.insert({{A(5), "A(5)"}, {A(10), "A(10)"}, {A(2), "A(2)"}, {A(1), "A(1)"}, {A(50), "A(50)"}});
    std::for_each(map.cbegin(), map.cend(), Printer());
    std::for_each(map.begin(), map.end(), [](auto & n){
        std::cout << "Lambda printer " << n.first << "-" << n.second << std::endl;
    });

    ////// std::find and std::find_if
    std::deque<int> dq {1, 3, 10, 25 , 5};
    std::deque<int>::const_iterator it = std::find(dq.cbegin(), dq.cend(), 25);
    if (it != dq.cend()) {
        std::cout << "Found " << *it << std::endl;
    }
    std::deque<int>::iterator itf = std::find_if(dq.begin(), dq.end(), [](int& n){
        if (n % 2 == 0)
        {
            n = 100;
            return true;
        }
        return false;  
    });
    if (itf != dq.end()) {
        std::cout << "Found even with lambda " << *itf << std::endl;
    }
    std::for_each(dq.begin(), dq.end(), [](const int& n){
        std::cout << "New list value=" << n << std::endl;
    });
    std::deque<int>::iterator itfF = std::find_if(dq.begin(), dq.end(), Even());
    if (itfF != dq.end()) {
        std::cout << "Found even with Functor " << *itfF << " at position " << std::distance(dq.begin(), itfF) << std::endl;
    }


    ///// std::search and std::find_end 
    std::vector<A> vect {A(3), A(5), A(6), A(2), A(4), A(15), A(5), A(6), A(10), A(8)};
    std::list<A> ls {A(5), A(6)};
    std::vector<A>::iterator its = std::search(vect.begin(), vect.end(), ls.begin(), ls.end());
    if (its != vect.end()) {
        std::cout << "Found range with search at position " << std::distance(vect.begin(), its) << std::endl; 
    }
    // use predicate
    its = std::search(vect.begin(), vect.end(), ls.begin(), ls.end(), [](const A& a1, const A& a2) -> bool {
        std::cout << "Called predicate with values " << a1.getX() << "/" << a2.getX() << std::endl;
        return ((a1.getX() == 2 && a2.getX() == 5) || 
                (a1.getX() == 4 && a2.getX() == 6)); // have to define own comparison
    });
    if (its != vect.end()) {
        std::cout << "Found range with search predicate at position " << std::distance(vect.begin(), its) << std::endl; 
    }

    its = std::find_end(vect.begin(), vect.end(), ls.begin(), ls.end(), [](const A& a1, const A& a2){
        std::cout << "Find_end predicate " << a1.getX() << "-" << a2.getX() << std::endl;
        return a1.getX() == a2.getX();
    });
    if (its != vect.end()) {
        std::cout << "Found range with find_end at position " << std::distance(vect.begin(), its) << std::endl; 
    }


    ////// std::find_first_of
    std::set<int> set {5, 6, 1, 8, 10, 19, 28, 4, 3};
    std::list<int> find_list {19, 8};
    std::cout << set;
    std::set<int>::iterator itsS = std::find_first_of(set.begin(), set.end(), find_list.begin(), find_list.end());
    if (itsS != set.end()) {
        std::cout << "Found element in set " << *itsS << " at position " << std::distance(set.begin(), itsS) << std::endl;
    }

    std::list<char> cls {'a','b', 'c', 'a', 'A', 'b','D', 'A', 'b', 'C', 'a', 'f'};
    std::list<char>::iterator itlc = std::adjacent_find(cls.begin(), cls.end(), Comparer());
    if (itlc != cls.end()) {
        std::cout << "Found adjacent elements " << *itlc << "/" << *(++itlc) << " at position " << std::distance(cls.begin(), --itlc) << std::endl; 
    }


    /////// std::count and std::count_if
    std::size_t nb = std::count(cls.begin(), cls.end(), 'a');
    std::cout << "Number of occurences of 'a' is " << nb << std::endl;

    nb = std::count_if(cls.begin(), cls.end(), [](const char& c){
        return std::tolower(c) == 'a';
    });
    std::cout << "Number of occurences of 'a' or 'A' is " << nb << std::endl;

    //////// std::mismatch
    std::vector<int> vect_m {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int> list_m {1, 2, 4, 6, 7, 3, 5, 9, 10, 8};
    std::pair<std::vector<int>::iterator, std::list<int>::iterator> p1 = std::mismatch(vect_m.begin(), vect_m.end(), list_m.begin());
    if (p1.first == vect_m.end() && p1.second == list_m.end())
    {
        std::cout<<"Collections vect_m / list_m are equal!" << std::endl;
    }
    else
    {
        std::cout << "Collections vect_m / list_m are NOT equal!" << std::endl;
        std::cout << "Mismatch at position: " << std::distance(vect_m.begin(), p1.first) << std::endl;
        std::cout << "First not matching element - vect_m: " << *(p1.first)<< " list_m: " << *(p1.second) << std::endl;
    }

    std::vector<int> vect_s {1, 2, 3, 4, 1, 1, 1, 2, 3, 3, 5, 6, 7, 7, 7, 2, 3, 4};
    // use operator==
    std::vector < int >::iterator found = std::search_n (vect_s.begin (), vect_s.end (), 3, 7);
    if (found != vect_s.end ())
    {
        std::cout << "Sequence: 7 7 7 " << *found << " has been found at position: "
	              << std::distance (vect_s.begin (), found) << std::endl;
    }
    else
    {
        std::cout << "Sequence 7 7 7 could not be found" << std::endl;
    }

    std::list < char >::iterator found_c = std::search_n (cls.begin (), cls.end (), 2, 'A', [] (const char& c1, const char& c2){
        return std::tolower(c1) == std::tolower(c2);
    });
    if (found_c != cls.end ())
    {
        std::cout << "Sequence: A A " << *found_c << " has been found at position: "
	              << std::distance (cls.begin (), found_c) << std::endl;
    }
    else
    {
        std::cout << "Sequence A A could not be found" << std::endl;
    }

    return 0;
}