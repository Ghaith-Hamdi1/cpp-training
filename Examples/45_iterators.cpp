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
