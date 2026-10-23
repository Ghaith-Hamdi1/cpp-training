// Chapter 15 - Project 05: Class Templates with Member Functions
// ===============================================================
//
// Class template parameters are available inside member function
// definitions. When defining member functions OUTSIDE the class:
//   1. You must resupply the template parameter declaration:
//      template <typename T>
//   2. You must qualify the class name with the template parameter:
//      Pair<T>::someFunction()
//
// The "injected class name" rule: inside the class template Pair<T>,
// the unqualified name `Pair` is shorthand for `Pair<T>`.
//
// Member functions defined outside the class template should be placed
// in the SAME header file, just below the class definition.

#include <iostream>
#include <string>

// -------------------------------------------------------
// A simple class template: Pair<T>
// -------------------------------------------------------
template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    Pair(const T &first, const T &second)
        : m_first{first}, m_second{second}
    {
    }

    // Defined INSIDE the class - template parameter T is available implicitly.
    T getFirst() const { return m_first; }
    T getSecond() const { return m_second; }

    // Declared here, defined OUTSIDE the class below.
    bool isEqual() const;

    // Returns a new Pair with swapped elements.
    // Note: inside the class, `Pair` means `Pair<T>` (injected class name).
    Pair swapped() const
    {
        return Pair{m_second, m_first}; // Pair = Pair<T> here
    }

    void print() const;
};

// -------------------------------------------------------
// Member function defined OUTSIDE the class template.
// Must resupply `template <typename T>` and qualify as `Pair<T>::`.
// -------------------------------------------------------
template <typename T>
bool Pair<T>::isEqual() const
{
    return m_first == m_second;
}

template <typename T>
void Pair<T>::print() const
{
    std::cout << "Pair(" << m_first << ", " << m_second << ")\n";
}

// -------------------------------------------------------
// A class template with TWO type parameters
// -------------------------------------------------------
template <typename K, typename V>
class KeyValue
{
private:
    K m_key{};
    V m_value{};

public:
    KeyValue(const K &key, const V &value)
        : m_key{key}, m_value{value}
    {
    }

    const K &key() const { return m_key; }
    const V &value() const { return m_value; }

    void print() const;
};

template <typename K, typename V>
void KeyValue<K, V>::print() const
{
    std::cout << "{ " << m_key << " : " << m_value << " }\n";
}

int main()
{
    // --- Pair<int> ---
    Pair<int> pi{5, 5};
    pi.print();
    std::cout << "isEqual? " << std::boolalpha << pi.isEqual() << '\n';

    Pair<int> pi2{3, 7};
    pi2.print();
    std::cout << "isEqual? " << pi2.isEqual() << '\n';

    // --- Pair<std::string> ---
    Pair<std::string> ps{"hello", "world"};
    ps.print();

    // Demonstrate the injected class name (swapped returns Pair<std::string>)
    auto swapped = ps.swapped();
    std::cout << "Swapped: ";
    swapped.print();

    // --- KeyValue<std::string, int> (two type parameters) ---
    KeyValue<std::string, int> kv1{"age", 25};
    KeyValue<std::string, int> kv2{"score", 100};
    kv1.print();
    kv2.print();

    // --- KeyValue<int, double> ---
    KeyValue<int, double> kv3{42, 3.14};
    kv3.print();

    return 0;
}
