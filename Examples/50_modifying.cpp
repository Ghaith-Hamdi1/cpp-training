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

    A operator+(const A& a) const {
        return A(m_x + a.m_x);
    }

    int getX() const { return m_x; }
};

template<typename T>
class Printer
{
public:
    Printer() {
        std::cout << "Printer" << std::endl;
    }
    ~Printer() {
        std::cout << std::endl;
    }
    void operator()(const T& t) const {
        std::cout << t << " ";
    }
};

std::ostream& operator<<(std::ostream& out, const std::vector<A>& t)
{
    std::for_each(t.begin(), t.end(), [&out](const A& a){
        out << a << " ";
    });
    out << std::endl;
    return out;
}
std::ostream& operator<<(std::ostream& out, const std::deque<A>& t)
{
    std::for_each(t.begin(), t.end(), [&out](const A& a){
        out << a << " ";
    });
    out << std::endl;
    return out;
}
std::ostream& operator<<(std::ostream& out, const std::list<A>& t)
{
    std::for_each(t.begin(), t.end(), [&out](const A& a){
        out << a << " ";
    });
    out << std::endl;
    return out;
}

struct Generator
{
    int n;
    Generator() : n{0} {
        std::cout << "Generator constructor" << std::endl;
    }

    int generate(int n)
    {
        if (n == 0)
        {
            return 0;
        }
        else if (n == 1)
        {
            return 1;
        }
        else 
        {
            int n_1{1};
            int n_2{0};
            int n_n{0};
            for (int i = 2; i <= n; i++)
            {
                n_n = n_1 + n_2;
                n_2 = n_1;
                n_1 = n_n;
            }
            return n_n;
        }
    }

    A operator() () {
        return A(generate(n++));
    } 
};

int main()
{
    //// std::copy
    std::vector<A> vect_a {A(1), A(5), A(4)};
    std::deque<A> deq_a;
    deq_a.resize(3, A(0));
    std::copy(vect_a.begin(), vect_a.end(), deq_a.begin());
    std::cout << vect_a;
    std::cout << deq_a;

    ////// std::swap, std::swap_ranges, std::iter_swap
    std::vector<A> vect_a1 {A(10), A(50), A(40), A(45)};
    std::swap(vect_a, vect_a1);
    std::cout << "New values " << vect_a << vect_a1;
    auto it = vect_a.begin();
    std::advance(it, 2);
    std::swap_ranges(vect_a.begin(), it, vect_a1.begin());
    std::cout << "swap_ranges values vect_a " << vect_a << "vect_a1" <<vect_a1;

    std::iter_swap(vect_a.begin(), vect_a1.begin());
    std::cout << "iter_swap values vect_a " << vect_a << "vect_a1" <<vect_a1;

    //////// std::transform
    std::string str("lowercase string");
    std::transform(str.begin(), str.end(), str.begin(), [](std::string::value_type& c){
        return std::toupper(c);
    });
    std::cout << "Transform string to upper case " << str << std::endl;

    std::vector<A> source_vect1 {A(10), A(50), A(40), A(45)};
    std::vector<A> source_vect2;
    std::vector<A> dest_vect;

    // back_inserter is unsed to insert into destination vector, since starting size is 0
    // without it, we will have segmentation fault since memory is not allocated
    std::transform(source_vect1.begin(), source_vect1.end(), std::back_inserter(dest_vect), [](const A& a){
        return A(a.getX() + 1);
    });
    std::cout << "Transform A -> A + 1 " << dest_vect << std::endl;
    std::swap(dest_vect, source_vect2);
    std::cout << "Source vect1 " << source_vect1 << std::endl;
    std::cout << "Source vect2 " << source_vect2 << std::endl;
    dest_vect.shrink_to_fit();

    std::transform(source_vect1.begin(), source_vect1.end(), source_vect2.begin(), 
                    std::back_inserter(dest_vect), std::plus<>());
    std::cout << "Transform sum " << dest_vect << std::endl;

    ////// std::replace and std::replace_if
    std::replace(source_vect1.begin(), source_vect1.end(), A(45), A(90));
    std::cout << "Source vect1 after replace A(90) " << source_vect1 << std::endl;

    std::replace_if(source_vect1.begin(), source_vect1.end(), [](const A& a){
        if (a.getX() == 90) {
            return true;
        }
        else {
            return false;
        }
    }, A(100));
    std::cout << "Source vect1 after replace_if A(100) " << source_vect1 << std::endl;

    ////// std::fill & std::fill_n
    std::list<A> list_fill(10, A(0));
    std::cout << "List created with given size " << list_fill;
    std::fill(list_fill.begin(), list_fill.end(), A(10));
    std::cout << "List filled with A(10) " << list_fill;

    std::fill_n(list_fill.begin(), 15, A(25));
    std::cout << "List filled with fill_n A(25) " << list_fill;

    ////// std::generater & std::generate_n
    std::vector<A> vect_generate;
    vect_generate.resize(10, A(0));
    std::generate(vect_generate.begin(), vect_generate.end(), Generator());
    std::cout << "Vector generated with Fibonacci sequence " << vect_generate;

    vect_generate.resize(20, A(0));
    std::generate_n(vect_generate.begin(), 20, Generator());
    std::cout << "Vector generated with Fibonacci sequence with generate_n " << vect_generate;

    ///// std::remove, std::remove_if
    std::vector<A>::iterator new_end = std::remove(vect_generate.begin(), vect_generate.end(), A(1));
    std::cout << "Vector printed with old end " << vect_generate;
    std::cout << "Vector printed with new end";
    std::for_each(vect_generate.begin(), new_end, [](const A& a){
        std::cout << " " << a;
    });
    std::cout << std::endl;
    // remove extra elements
    vect_generate.erase(new_end, vect_generate.end());

    std::string string_with_spaces{"this is a test string"};
    std::string::iterator str_it = std::remove_if(string_with_spaces.begin(), string_with_spaces.end(), [](const std::string::value_type & c){
        if (c == ' ')
        {
            return true;
        }
        else 
        {
            return false;
        }
    });
    string_with_spaces.erase(str_it, string_with_spaces.end());
    std::cout << "New string " << string_with_spaces << std::endl;

    return 0;
}