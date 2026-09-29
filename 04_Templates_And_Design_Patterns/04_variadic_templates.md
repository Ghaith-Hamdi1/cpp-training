# Variadic templates

- Ellipsis represents a variable arguments list ( noted by three points `...` )
- In C style, `va_list` is used to manage ellipsis. This is prohibited in modern C++
- A variadic template is a template that accepts one or more template parameter
- Syntax: `template<typename... pack_name>`
- Programmer can add also template parameters other than variadic parameter pack:
  - `template<typename T, typename... pack_name>`

- For template functions, the declaration will be:
  ```cpp
  template<typename... Args>
  void function_name(Args... args);
  ```
- For template classes / structures:
  ```cpp
  template<typename... Args>
  class Class_Name
  {
  };
  ```
- For both of examples above, simple types can be added to the template
  ```cpp
  template<typename T, typename... Args>
  void function_name(Args... args, T t);
  ```

- For classes methods definition, the syntax should be:
  ```cpp
  template<typename T, typename... Args>
  void Class_name<T, Args...>::member_name(Args... args, T t);
  ```
- Variadic classes and functions are used to pass as many as needed types to the corresponding structure and of course at compile time (cannot perform type definition during runtime)
- Generally, an effcient way to use variadic templates are recursive call of variadic templated classes or functions (see examples)
- `std::tuple` can be used as well for parameter pack management (see examples)

```cpp
// Recursive variadic template class (Examples/04_Templates_And_Design_Patterns/04_variadic_templates/64_variadic_templates.cpp)
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

// Recursive variadic function
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
```

```cpp
// std::tuple used for parameter pack management (Examples/04_Templates_And_Design_Patterns/04_variadic_templates/65_tuple.cpp)
std::tuple<int, A, std::string> tuple;
tuple = std::make_tuple<int, A, std::string>(1, A(), "Hello");

int i; A a; std::string s;
std::tie(i, a, s) = tuple;

int i1 = std::get<int>(tuple);
std::tuple_element_t<2, decltype(tuple2)> te;
```

```cpp
// Variadic template combined with std::tuple (Examples/04_Templates_And_Design_Patterns/04_variadic_templates/66_variadic_with_tuple.cpp)
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
};
```
