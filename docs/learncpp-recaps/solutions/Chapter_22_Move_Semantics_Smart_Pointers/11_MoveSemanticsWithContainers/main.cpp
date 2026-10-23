// Chapter 22 - Project 11: Move Semantics with STL Containers
// The standard library uses move semantics extensively for efficiency.
//
// Key points:
//   - push_back(std::move(x)) moves x into the container instead of copying.
//   - std::vector will move elements on reallocation IF the move constructor
//     is marked noexcept.  Without noexcept, it falls back to copying for
//     strong exception safety.
//   - Standard algorithms like std::sort use moves when available.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

// -----------------------------------------------------------------------
// A class that logs copies and moves - demonstrates noexcept importance.
// -----------------------------------------------------------------------
class Heavy
{
    std::string m_label;
    int *m_data{};

public:
    explicit Heavy(const std::string &label)
        : m_label{label}, m_data{new int(0)}
    {
        std::cout << "  [Ctor]      \"" << m_label << "\"\n";
    }

    // Copy constructor
    Heavy(const Heavy &src)
        : m_label{src.m_label + " (copy)"}, m_data{new int(*src.m_data)}
    {
        std::cout << "  [Copy ctor] \"" << m_label << "\"\n";
    }

    // Move constructor - MUST be noexcept for vector optimization
    Heavy(Heavy &&src) noexcept
        : m_label{std::move(src.m_label)}, m_data{src.m_data}
    {
        src.m_data = nullptr;
        std::cout << "  [Move ctor] \"" << m_label << "\"\n";
    }

    // Copy assignment
    Heavy &operator=(const Heavy &src)
    {
        if (this != &src)
        {
            delete m_data;
            m_label = src.m_label;
            m_data = new int(*src.m_data);
        }
        std::cout << "  [Copy =]    \"" << m_label << "\"\n";
        return *this;
    }

    // Move assignment - noexcept
    Heavy &operator=(Heavy &&src) noexcept
    {
        if (this != &src)
        {
            delete m_data;
            m_label = std::move(src.m_label);
            m_data = src.m_data;
            src.m_data = nullptr;
        }
        std::cout << "  [Move =]    \"" << m_label << "\"\n";
        return *this;
    }

    ~Heavy()
    {
        delete m_data;
    }

    const std::string &label() const { return m_label; }

    bool operator<(const Heavy &rhs) const { return m_label < rhs.m_label; }
};

// -----------------------------------------------------------------------
// 1. push_back: copy vs move
// -----------------------------------------------------------------------
void pushBackDemo()
{
    std::cout << "=== 1. push_back: copy vs move ===\n";

    std::vector<Heavy> vec;
    vec.reserve(4); // Pre-allocate to avoid reallocation noise

    Heavy a("Item-A");
    std::cout << "\n  -- push_back (copy) --\n";
    vec.push_back(a); // COPY: a is an l-value

    std::cout << "\n  -- push_back (move) --\n";
    vec.push_back(std::move(a)); // MOVE: std::move casts to r-value

    std::cout << "\n  -- emplace_back --\n";
    vec.emplace_back("Item-B"); // Constructs in-place - no copy or move of Heavy
}

// -----------------------------------------------------------------------
// 2. Vector reallocation - noexcept matters
// -----------------------------------------------------------------------
void reallocationDemo()
{
    std::cout << "\n=== 2. Reallocation uses move (if noexcept) ===\n";

    std::vector<Heavy> vec;
    // Do NOT reserve - force reallocation

    std::cout << "  Adding 1st element:\n";
    vec.emplace_back("One");

    std::cout << "\n  Adding 2nd element (may trigger realloc):\n";
    vec.emplace_back("Two");
    // If Heavy's move ctor were NOT noexcept, vector would COPY here
    // for strong exception safety.  With noexcept, it MOVES - much faster.

    std::cout << "\n  Adding 3rd element (may trigger realloc):\n";
    vec.emplace_back("Three");
}

// -----------------------------------------------------------------------
// 3. std::sort uses move semantics
// -----------------------------------------------------------------------
void sortDemo()
{
    std::cout << "\n=== 3. std::sort uses moves ===\n";

    std::vector<Heavy> vec;
    vec.reserve(3);
    vec.emplace_back("Charlie");
    vec.emplace_back("Alice");
    vec.emplace_back("Bob");

    std::cout << "\n  Sorting...\n";
    std::sort(vec.begin(), vec.end());

    std::cout << "\n  Sorted order: ";
    for (const auto &h : vec)
        std::cout << '"' << h.label() << "\" ";
    std::cout << '\n';
}

// -----------------------------------------------------------------------
// 4. Returning a vector - move or RVO
// -----------------------------------------------------------------------
std::vector<std::string> buildList()
{
    std::vector<std::string> result;
    result.push_back("X");
    result.push_back("Y");
    result.push_back("Z");
    return result; // NRVO / move - no deep copy
}

void returnDemo()
{
    std::cout << "\n=== 4. Returning vector by value (RVO/move) ===\n";
    auto list = buildList();
    std::cout << "  Elements: ";
    for (const auto &s : list)
        std::cout << s << ' ';
    std::cout << '\n';
}

// -----------------------------------------------------------------------
int main()
{
    pushBackDemo();
    reallocationDemo();
    sortDemo();
    returnDemo();

    std::cout << "\nDone.\n";
    return 0;
}
