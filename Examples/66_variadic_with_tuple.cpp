#include <iostream>
#include <tuple>

template<class Tuple, std::size_t N>
struct TuplePrinter
{
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};
 
template<class Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<typename...Ts>
class Wrapper
{
private:
    std::tuple<Ts...> m_tuple;
public:
    Wrapper(Ts... ts) : m_tuple(ts...) 
    {
    }

    template<int N>
    using Nth = typename std::tuple_element<N, decltype(m_tuple)>::type;

    template<int N>
    Nth<N>& getElemet()
    {
        return std::get<N>(m_tuple);
    }

    void print()
    {
        TuplePrinter<decltype(m_tuple), sizeof...(Ts)>::print(m_tuple);
        std::cout << std::endl;
    }

    template<int N>
    void setValue(const Nth<N> & val)
    {
        getElemet<N>() = val;
    }
    template<int N>
    void setValue(Nth<N> && val)
    {
        getElemet<N>() = val;
    }

};

int main()
{
    Wrapper<int, char, int> wrp(1, 'C', 2);
    std::cout << "First element is " << wrp.getElemet<0>() << std::endl;
    wrp.print();
    wrp.setValue<0>(10);
    wrp.print();
    return 0;
}