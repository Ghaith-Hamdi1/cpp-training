// Chapter 26 - Project 2: Member Functions Defined Outside the Class
// ====================================================================
// When member functions of a template class are defined outside the
// class body, each one needs:
//   1. Its own `template <typename T>` declaration.
//   2. The fully-qualified class name including template arguments:
//      `Array<T>::functionName`.
//
// Common pitfalls demonstrated here:
//   - Forgetting the template declaration → compile error.
//   - Writing `Array::` instead of `Array<T>::` outside the class body
//     → compile error (inside the class, `Array` implicitly means the
//       current instantiation, but outside it does not).

#include <cassert>
#include <iostream>

// ---------------------------------------------------------------------------
// Class declaration - only prototypes inside the class
// ---------------------------------------------------------------------------
template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    Pair(const T &first, const T &second);

    const T &first() const;
    const T &second() const;
    T max() const;

    void print() const;
};

// ---------------------------------------------------------------------------
// Member function definitions - all outside the class body
// ---------------------------------------------------------------------------

// Each definition must repeat the template header and use Pair<T>::

template <typename T> // ← required on every definition
Pair<T>::Pair(const T &first, const T &second)
    : m_first{first}, m_second{second}
{
}

template <typename T>
const T &Pair<T>::first() const // ← Pair<T>::, not Pair::
{
    return m_first;
}

template <typename T>
const T &Pair<T>::second() const
{
    return m_second;
}

template <typename T>
T Pair<T>::max() const
{
    return (m_first >= m_second) ? m_first : m_second;
}

template <typename T>
void Pair<T>::print() const
{
    std::cout << "(" << m_first << ", " << m_second << ")\n";
}

// ---------------------------------------------------------------------------
// PITFALL illustration (commented out - would not compile):
//
//   // Missing template <typename T>:
//   const T& Pair<T>::first() const { return m_first; }  // ERROR
//
//   // Using Pair:: instead of Pair<T>::  :
//   template <typename T>
//   const T& Pair::first() const { return m_first; }     // ERROR
// ---------------------------------------------------------------------------

int main()
{
    Pair<int> p1(3, 7);
    std::cout << "Pair<int>:    ";
    p1.print();                                  // (3, 7)
    std::cout << "  max = " << p1.max() << '\n'; // 7

    Pair<double> p2(4.4, 2.2);
    std::cout << "Pair<double>: ";
    p2.print();                                  // (4.4, 2.2)
    std::cout << "  max = " << p2.max() << '\n'; // 4.4

    Pair<std::string> p3("alpha", "beta");
    std::cout << "Pair<string>: ";
    p3.print();                                  // (alpha, beta)
    std::cout << "  max = " << p3.max() << '\n'; // beta

    return 0;
}
