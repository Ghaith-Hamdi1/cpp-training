#include <iostream>
#include <exception>
#include <vector>

class TypeCastFraction
{
public:
    TypeCastFraction(int numerator, int denominator) : m_tc_numerator{numerator}, m_tc_denominator{denominator}
    {
        if (m_tc_denominator == 0)
        {
            throw std::runtime_error("Denominator cannot be equal to 0");
        }
    }
    // rule of 5
    TypeCastFraction(const TypeCastFraction&) = default;
    TypeCastFraction(TypeCastFraction&&) = default;
    TypeCastFraction& operator=(const TypeCastFraction&) = default;
    TypeCastFraction& operator=(TypeCastFraction&&) = default;
    virtual ~TypeCastFraction() = default;
    friend std::ostream& operator<<(std::ostream& out, const TypeCastFraction& fraction)
    {
        out << fraction.m_tc_numerator << "/" << fraction.m_tc_denominator;
        return out;
    }
private:
    int m_tc_numerator;
    int m_tc_denominator;
};

class Fraction
{
public:
    Fraction(int numerator, int denominator) : m_numerator{numerator}, m_denominator{denominator}
    {
        if (m_denominator == 0)
        {
            throw std::logic_error("Denominator cannot be equal to 0");
        }
    }
    Fraction& test()
    {
        std::cout << "Test " << std::endl;
        return *this;
    }
    // rule of 5
    Fraction(const Fraction&) = default;
    Fraction(Fraction&&) = default;
    Fraction& operator=(const Fraction&) = default;
    Fraction& operator=(Fraction&&) = default;
    virtual ~Fraction() = default;

    Fraction operator-() const
    {
        // negative unary operator is built-in for int
        return Fraction(-m_numerator, m_denominator);
    }

    bool operator==(const Fraction& right)
    {
        return (m_denominator * right.m_numerator == m_numerator * right.m_denominator);
    }

    Fraction operator+(const Fraction& right)
    {
        int numerator = m_numerator * right.m_denominator + right.m_numerator * m_denominator;
        int denominator = m_denominator * right.m_denominator;

        // simplify
        int dividor = pgcd(numerator, denominator);

        return Fraction(numerator / dividor, denominator / dividor);
    }

    Fraction operator-(const Fraction& right)
    {
        return (*this + (-right));
    }

    bool operator>=(const Fraction& right)
    {
        if (m_numerator * right.m_denominator >= right.m_numerator * m_denominator)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    bool operator<=(const Fraction& right)
    {
        if (*this == right || !(*this >= right))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Fraction& operator++() // prefix increment ++Fraction
    {
        m_numerator += m_denominator;
        return *this;
    }
    Fraction& operator--() // prefix decrement --Fraction
    {
        m_numerator -= m_denominator;
        return *this;
    }

    Fraction operator++(int)  // postfix
    {
        Fraction temporary{*this}; // save a copy
        ++(*this); // call prefix increment
        return temporary;
    }
    Fraction operator--(int)
    {
        Fraction temporary{*this}; // save a copy
        --(*this); // call prefix decrement
        return temporary;
    }

    // functor
    double operator()()
    {
        return (static_cast<double>(m_numerator) / static_cast<double>(m_denominator));
    }
    double operator()() const
    {
        return (static_cast<double>(m_numerator) / static_cast<double>(m_denominator));
    }
    double operator()(double d)
    {
        return ((*this)() + d);
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        out << fraction.m_numerator << "/" << fraction.m_denominator;
        return out;
    }

    // special operator (typecast)
    operator double() const // no return for typecast operators
    {
        std::cout << "Call typecast" << std::endl;
        return ((*this)()); // call double operator()() const
    }
    // typecast to TypeCastFraction
    operator TypeCastFraction() const 
    {
        std::cout << "Tpecast TypeCastFraction" << std::endl;
        return TypeCastFraction(m_numerator, m_denominator);
    }
private:
    int pgcd(int a, int b)
    {
        return b != 0 ? pgcd(b, a % b) : a;
    }
    int m_numerator;
    int m_denominator;
};

class FractionList
{
public:
    FractionList() {}
    // rule of 5
    FractionList(const FractionList&) = default;
    FractionList(FractionList&&) = default;
    FractionList& operator=(const FractionList&) = default;
    FractionList& operator=(FractionList&&) = default;
    virtual ~FractionList() = default;

    void insert(const Fraction& fraction)
    {
        fractions.push_back(fraction);
    }

    Fraction& operator*()
    {
        if (!fractions.empty())
        {
            return (*this)[0];
            // return fractions[0]; // it works as well
        }
        else 
        {
            throw std::range_error("Index value invalid");
        }
    } 
    Fraction* operator->()
    {
        if (fractions.size() > 1)
        {
            return &(*this)[1];
            // return fractions[0]; // it works as well
        }
        else 
        {
            throw std::range_error("Index value invalid");
        }
    } 

    Fraction& operator[](int index) // return by reference to have the real value
    {
        if (index >= 0 && index < fractions.size())
        {
            return fractions[index];
        }
        else
        {
            throw std::range_error("Index value invalid");
        }

    }
private:
    std::vector<Fraction> fractions;
};

void printClassTypeCast(const TypeCastFraction& fraction)
{
    std::cout << "Implicit typecast " << fraction << std::endl;
}

int main()
{
    Fraction a(1, 3); // 1/3
    Fraction b(1, 4); // 1/4

    std::cout << "Sum " << (a + b) << std::endl 
              << "Diff " << (a - b) << std::endl
              << "a >= b " << (a >= b) << std::endl
              << "prefix increment a " << ++a << std::endl
              << "postfix incrrement b "<< b++ << std::endl
              << "a value " << a() << " add double " << a(1.666667) << std::endl;
    std::cout << "Check b postfix increment " << b << std::endl;

    FractionList list;
    list.insert(a);
    list.insert(b);

    std::cout << "List[1]=" << list[1] << std::endl;
    std::cout << "List[0]=" << *list << std::endl;
    std::cout << "List[1]=" << list->test() << std::endl;

    double d = static_cast<double>(a); // typecast operator
    
    printClassTypeCast(a);
    return 0;
}