// Project 14: Overloading Operators and Function Templates
// ==========================================================
// When a function template uses operators (like <, +=, /=, <<) on a
// template type T, the actual type substituted for T must have those
// operators defined. You enable your class to work with such templates
// by providing the required operator overloads - the template itself
// needs no modification.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// --- A generic function template that requires operator+= and operator/= ---
// This computes the average of elements in a vector.
// T must support: operator+=, operator/= (with int), and operator<< for output.
template <typename T>
T average(const std::vector<T> &values)
{
    T sum{values[0]}; // T must be copy-constructible

    for (std::size_t i{1}; i < values.size(); ++i)
        sum += values[i]; // T must have operator+=

    sum /= static_cast<int>(values.size()); // T must have operator/= with int

    return sum;
}

// --- A generic function template that requires operator< ---
template <typename T>
const T &findMin(const T &a, const T &b)
{
    return (a < b) ? a : b; // T must have operator<
}

// --- Our custom class that provides all needed operators ---
class Score
{
private:
    double m_value{};

public:
    Score(double value = 0.0) : m_value{value} {}

    double getValue() const { return m_value; }

    // operator+= needed by average() template
    Score &operator+=(const Score &rhs)
    {
        m_value += rhs.m_value;
        return *this;
    }

    // operator/= with int needed by average() template
    Score &operator/=(int divisor)
    {
        m_value /= divisor;
        return *this;
    }

    // operator< needed by findMin() template and std::sort
    friend bool operator<(const Score &a, const Score &b)
    {
        return a.m_value < b.m_value;
    }

    // operator> needed by std::sort with custom comparator
    friend bool operator>(const Score &a, const Score &b)
    {
        return a.m_value > b.m_value;
    }

    // operator== for completeness
    friend bool operator==(const Score &a, const Score &b)
    {
        return a.m_value == b.m_value;
    }

    // operator<< needed for output
    friend std::ostream &operator<<(std::ostream &out, const Score &s)
    {
        out << s.m_value;
        return out;
    }
};

int main()
{
    // --- Using templates with built-in types (operators already defined) ---
    std::cout << "=== Templates with int ===\n";
    std::vector<int> intVals{10, 20, 30, 40, 50};
    std::cout << "Average of ints: " << average(intVals) << '\n';
    std::cout << "Min of 15, 7: " << findMin(15, 7) << '\n';

    // --- Using templates with our custom Score class ---
    std::cout << "\n=== Templates with Score ===\n";
    std::vector<Score> scores{Score{85.0}, Score{92.5}, Score{78.0}, Score{96.0}, Score{88.5}};

    // average<Score> works because Score has operator+= and operator/=
    Score avg = average(scores);
    std::cout << "Average score: " << avg << '\n';

    // findMin<Score> works because Score has operator<
    Score minScore = findMin(scores[0], scores[1]);
    std::cout << "Min of " << scores[0] << " and " << scores[1] << ": " << minScore << '\n';

    // --- std::sort works because Score has operator< ---
    std::cout << "\n=== std::sort with Score ===\n";
    std::cout << "Before sort: ";
    for (const auto &s : scores)
        std::cout << s << ' ';
    std::cout << '\n';

    std::sort(scores.begin(), scores.end()); // Uses operator<

    std::cout << "After sort:  ";
    for (const auto &s : scores)
        std::cout << s << ' ';
    std::cout << '\n';

    // Sort descending using operator>
    std::sort(scores.begin(), scores.end(),
              [](const Score &a, const Score &b)
              { return a > b; });

    std::cout << "Descending:  ";
    for (const auto &s : scores)
        std::cout << s << ' ';
    std::cout << '\n';

    // Key points:
    // 1. Templates impose requirements on the types used with them
    // 2. If a template uses operator+=, T must have operator+= defined
    // 3. You enable your class for use with templates by providing the needed operators
    // 4. The template itself needs NO modification - just overload the operators on your class
    // 5. STL algorithms (std::sort, std::find, etc.) also rely on operator overloads

    return 0;
}
