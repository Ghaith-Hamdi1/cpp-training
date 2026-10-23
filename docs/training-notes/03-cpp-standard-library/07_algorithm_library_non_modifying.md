# Algorithm library: non-modifying

(Slides 38–45)

- `std::for_each`: parse a range of container using iterators and perform a unary operation on each element (shown using lambdas, a function, and functors)
- `std::find`: returns an iterator to the first element equal to the provided element in arguments
- `std::find_if`: returns an iterator to the first element tested by the predicate which returns true when evaluating it
- `std::search`: find a range of elements inside a container and return an iterator to the first occurrence
- `std::find_end`: find a range of elements inside a container and return an iterator to the last occurrence
- `std::find_first_of`: searches for the first occurrence of an element in a sequence in a given container and returns an iterator to it
- `std::adjacent_find`: searches the range of elements in order to find the first pair of adjacent consecutive elements. If such a pair is found, the iterator to the first element is returned.
  - Needs `operator==` overload for user defined types for the default version, or define a binary predicate to define adjacence meaning
- `std::count`: returns the number of occurrences of an element
- `std::count_if`: returns the number of occurrences of an element for which the predicate returns true
- `std::mismatch`: compares two ranges of elements, and returns the iterators which point to the place where those sequences differ. If the ranges are identical, the function returns the last iterator, and the corresponding iterator value from the second sequence.
- `std::search_n`: searches the range `[first, last)` for the first sequence of `count` identical elements, each equal to the given value.
  - The first version uses the equality operator to compare the elements, while the second version uses the given binary predicate `p`.

```cpp
// Trimmed excerpt — full runnable example: examples/course/03-cpp-standard-library/07-algorithm-library-non-modifying/49_non_modifying_algorithm.cpp
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
    explicit A(int x) : m_x{x} {}
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

struct Comparer
{
    bool operator()(const char& c1, const char& c2) {
        return std::tolower(c1) == std::tolower(c2);
    }
};

int main()
{
    ///// std::for_each
    std::map<A, std::string> map;
    map.insert({{A(5), "A(5)"}, {A(10), "A(10)"}});
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
        return (n % 2 == 0);
    });
    if (itf != dq.end()) {
        std::cout << "Found even with lambda " << *itf << " at position " << std::distance(dq.begin(), itf) << std::endl;
    }

    ///// std::search and std::find_end
    std::vector<A> vect {A(3), A(5), A(6), A(2), A(4), A(15), A(5), A(6), A(10), A(8)};
    std::list<A> ls {A(5), A(6)};
    std::vector<A>::iterator its = std::search(vect.begin(), vect.end(), ls.begin(), ls.end());
    if (its != vect.end()) {
        std::cout << "Found range with search at position " << std::distance(vect.begin(), its) << std::endl; 
    }

    // find_end returns the LAST occurrence of the range, unlike search which returns the first
    its = std::find_end(vect.begin(), vect.end(), ls.begin(), ls.end(), [](const A& a1, const A& a2){
        return a1.getX() == a2.getX();
    });
    if (its != vect.end()) {
        std::cout << "Found range with find_end at position " << std::distance(vect.begin(), its) << std::endl; 
    }

    ////// std::find_first_of
    std::set<int> set {5, 6, 1, 8, 10, 19, 28, 4, 3};
    std::list<int> find_list {19, 8};
    std::set<int>::iterator itsS = std::find_first_of(set.begin(), set.end(), find_list.begin(), find_list.end());
    if (itsS != set.end()) {
        std::cout << "Found element in set " << *itsS << " at position " << std::distance(set.begin(), itsS) << std::endl;
    }

    ////// std::adjacent_find (with binary predicate)
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
        std::cout << "Collections vect_m / list_m are equal!" << std::endl;
    }
    else
    {
        std::cout << "Mismatch at position: " << std::distance(vect_m.begin(), p1.first)
                  << " first not matching element - vect_m: " << *(p1.first) << " list_m: " << *(p1.second) << std::endl;
    }

    ///// std::search_n
    std::vector<int> vect_s {1, 2, 3, 4, 1, 1, 1, 2, 3, 3, 5, 6, 7, 7, 7, 2, 3, 4};
    // equality-based overload
    std::vector<int>::iterator found = std::search_n(vect_s.begin(), vect_s.end(), 3, 7);
    if (found != vect_s.end())
    {
        std::cout << "Sequence: 7 7 7 found at position: " << std::distance(vect_s.begin(), found) << std::endl;
    }

    // predicate-based overload
    std::list<char>::iterator found_c = std::search_n(cls.begin(), cls.end(), 2, 'A', [] (const char& c1, const char& c2){
        return std::tolower(c1) == std::tolower(c2);
    });
    if (found_c != cls.end())
    {
        std::cout << "Sequence: A A found at position: " << std::distance(cls.begin(), found_c) << std::endl;
    }

    return 0;
}
```

---

