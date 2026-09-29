# Type traits

- Type traits defines a set of functions very useful in template programming that allows identifying the type of parameters of templates
- They are defined in header file `<type_traits>`
- They are generally used with `static_assert` to verify that the template type is compatible with the template implementation
- Generally used at compile time to make some verifications on template types properties

```cpp
// Representative example (Examples/04_Templates_And_Design_Patterns/02_type_traits/62_type_traits.cpp)
template<typename T>
T multiply(T& a, T& b)
{
    static_assert(std::is_integral<T>::value, "Multiplication can only be done using integral type");
    return a * b;
}

class Test
{
public:
    template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
    static void print(const T& t)
    {
        std::cout << "Print an itegral value " << t << std::endl;
    }

    template<typename T, std::enable_if_t<!std::is_integral<T>::value, bool> = true>
    static void print(const T& t)
    {
        std::cout << "Print a non integral value " << t << std::endl;
    }
};

// usage:
std::cout << "X is polymorphic " << std::boolalpha << std::is_polymorphic<X>::value << std::endl;
std::cout << "X is" << (std::is_base_of<A, X>::value == true ? " " : " not ") << "a derived from A" << std::endl;
```
