#include <iostream>

template<typename ... ARGS>
class Test
{
public:
    void print();
};

template<typename T, typename ... ARGS>
class Test<T, ARGS ...>
{
public:
    Test(const T& first, const ARGS& ... args)
        : first(first)
        , args(args...)
    {}

    void print();
private:
    T first;
    Test<ARGS ... > args;
    
};

template<typename T, typename ... ARGS>
void Test<T, ARGS ...>::print()
{
    std::cout << "Print " << first << std::endl;
    args.print();
}

template<typename ... ARGS>
void Test<ARGS ...>::print()
{
    std::cout << "End" << std::endl;
}

template<typename T>
void foo(const T& t)
{
    std::cout << "Print foo with one parameter " << t << std::endl;
}

template<typename T, typename... ARGS>
void foo(const T& t, const ARGS&... args)
{
    std::cout << "Print foo with multiple parameters " << t << std::endl;
    foo(args...);
}

template<typename... ARGS>
void bar(const ARGS&... args)
{
}

template<typename T, typename... ARGS>
void bar(const T& t, const ARGS&... args)
{
    std::cout << "Print bar with multiple parameters " << t << std::endl;
    bar(args...);
}

int main()
{
    Test<int, float, std::string> data(1, 2.1, "Hello");
    
    data.print();

    foo(1, "Hello", 2.1, 'C');

    bar(1, 'D', 2.14);
    
    return 0;
}
