#include <iostream>
#include <tuple>
#include <string>

class A
{
public:
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "This is A";
        return out;
    }
};

int main()
{
    std::tuple<int, A, std::string> tuple;
    tuple = std::make_tuple<int, A, std::string>(1, A(), "Hello");
    int i;
    A a;
    std::string s;

    std::tie(i, a, s) = tuple;
    std::cout << i << ", " << a << ", " << s << std::endl;
    int i1 = std::get<int>(tuple);
    std::cout << "Get i1=" << i1 << std::endl;

    auto tuple2 = std::make_tuple<int, int, float>(1, 2, 3.0f);
    auto i2 = std::get<0, int>(tuple2);

    std::cout << "Get i2=" << i2 << std::endl;

    std::tuple_element_t<2, decltype(tuple2)> te;
    std::cout << "Typeid = " << typeid(te).name() << std::endl;
    return 0;
}