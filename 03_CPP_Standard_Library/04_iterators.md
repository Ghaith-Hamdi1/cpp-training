# Iterators

(Slides 23–28)

- Iterator is an object that allows parsing a container and provides access to the elements
- Iterator types:
  - Forward iterator
  - Reverse iterator
  - Constant forward iterator
  - Constant reverse iterator
- Advantage of iterators: can parse the container with standard way without caring about container implementation, `++` operator for incrementation and `*` for accessing elements

# Forward and reverse iterators

- Forward iterators
  - Iterator to get the container beginning: `begin` (non-const) and `cbegin` (constant)
  - Iterator to get the container end: `end` (non-const) and `cend` (constant)
- Reverse iterators
  - Iterator to get the container beginning: `rbegin` (non-const) and `crbegin` (constant)
  - Iterator to get the container end: `rend` (non-const) and `crend` (constant)
- Difference between forward and reverse iterators: `end` and `rend` are always not part of the container, but just give a reference to the container ending

# Range based loops and iterator invalidation

- Range based loops
  - [Code screenshot in source — not extractable as text; the visible caption reads: "type here is int"]
- Iterator invalidation: when an iterator is iterating on an element that has changed address or been destroyed, we say that the iterator has been invalidated. So, the iterator is dangling and accessing it causes undefined behavior. *(the accompanying code sample for this was also a screenshot in the source and could not be extracted as text)*

# Operators for iterators

- `operator*` — dereferencing the iterator returns the element value the iterator is pointing on
- `operator++` — move iterator to point on next element
- `operator--` — move iterator to point on next element (not always available for all containers)
- `operator==` and `operator!=`
- `operator=` — assigning an iterator to another

# Standard iteration pattern

- Generally, to iterate through a container, we use the following pattern:
  - [Code screenshot in source — "Forward iterator" pattern and "Reverse iterator" pattern shown side by side; not extractable as text. Recovered equivalent code below from `Examples/03_CPP_Standard_Library/04_iterators/45_iterators.cpp`]

```cpp
// Source: Examples/03_CPP_Standard_Library/04_iterators/45_iterators.cpp
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>

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
    bool operator==(const A& a) const 
    {
        return (m_x == a.m_x);
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

int main()
{
    std::vector<int> vect {1, 2, 3, 4, 5};

    std::vector<int>::iterator itf = vect.begin();
    std::cout << "Forward vector iterator" << std::endl;
    while (itf != vect.end()) {
        std::cout << *itf << std::endl; // access element value
        (*itf)++; // increment value
        itf++; // increment iterator
    }
    std::cout << "Forward vector const iterator" << std::endl;
    // using for loop
    for (auto citf = vect.cbegin(); citf != vect.cend(); ++citf) {
        std::cout << *citf << std::endl;
        // cannot change value since it is const iterator
        //(*citf)++;
    }
    // using while loop
    std::cout << "Reverse vector iterator" << std::endl;
    std::vector<int>::reverse_iterator itr = vect.rbegin();
    while (itr != vect.rend()) {
        std::cout << *itr << std::endl; // access element value
        (*itr)++; // increment value
        itr++; // increment iterator
    }
    std::cout << "Reverse vector const iterator" << std::endl;
    // using for loop
    for (auto citr = vect.crbegin(); citr != vect.crend(); ++citr) {
        std::cout << *citr << std::endl;
        // cannot change value since it is const iterator
        //(*citr)++;
    }

    std::cout << "/**************  List  ********/" << std::endl;
    std::list<int> li;
    for (int count=0; count < 6; ++count)
        li.push_back(count);

    std::list<int>::const_iterator it; // declare an iterator
    it = li.cbegin(); // assign it to the start of the list
    while (it != li.cend()) // while it hasn't reach the end
    {
        std::cout << *it << ' '; // print the value of the element it points to
        ++it; // and iterate to the next element
    }
    --it; // back to before end()
    while (it != li.cbegin()) // while it hasn't reach the end
    {
        std::cout << *it << ' '; // print the value of the element it points to
        --it; // and iterate to the next element
    }

    std::cout << *it /*begin*/ << std::endl;

    std::forward_list<int> fwl {1, 2, 3, 4, 5, 6};
    auto itfw = fwl.cbegin(); // assign it to the start of the list
    while (itfw != fwl.cend()) // while it hasn't reach the end
    {
        std::cout << *itfw << ' '; // print the value of the element it points to
        ++itfw; // and iterate to the next element
        //itfw--;
    }

    std::cout << "/**************  Set  ********/" << std::endl;
    std::set<int> myset;
    myset.insert(7);
    myset.insert(2);
    myset.insert(-6);
    myset.insert(8);
    myset.insert(1);
    myset.insert(-4);

    std::set<int>::const_iterator its; // declare an iterator
    its = myset.cbegin(); // assign it to the start of the set
    while (its != myset.cend()) // while it hasn't reach the end
    {
        std::cout << *its << ' '; // print the value of the element it points to
        ++its; // and iterate to the next element
    }
    std::cout << std::endl;

    std::cout << "/**************  Map  ********/" << std::endl;
    std::map<int, std::string> mymap;
	mymap.insert(std::make_pair(4, "apple"));
	mymap.insert(std::make_pair(2, "orange"));
	mymap.insert(std::make_pair(1, "banana"));
	mymap.insert(std::make_pair(3, "grapes"));
	mymap.insert(std::make_pair(6, "mango"));
	mymap.insert(std::make_pair(5, "peach"));

	auto itm{ mymap.cbegin() }; // declare a const iterator and assign to start of vector
	while (itm != mymap.cend()) // while it hasn't reach the end
	{
		std::cout << (*itm).first << '=' << itm->second << ' '; // print the value of the element it points to
		++itm; // and iterate to the next element
	}
	std::cout << std::endl;

    ///////////////////////////  containers APIs using iterators /////////////////////////////
    std::list<A> ls {A(0), A(3), A(2), A(10), A(8)};
    std::list<A> ls_a {A(100), A(200), A(300)};
    std::cout << "List insertion" << std::endl;
    for (auto ls_it = ls.cbegin(); ls_it != ls.cend(); ls_it++)
    {
        if (*ls_it == A(3))
        {
            ls.insert(ls_it, ls_a.begin(), ls_a.end());
            ls.erase(ls_it);
            break;
        }
    }
    for (auto ls_it = ls.begin(); ls_it != ls.end(); ls_it++)
    {
        std::cout << *ls_it << " ";
    }
    std::cout << std::endl;

    

    return 0;
}
```

---

