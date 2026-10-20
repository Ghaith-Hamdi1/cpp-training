// Chapter 16 - Project 09: Resizing and Capacity Management
// ===========================================================
// Demonstrates:
//   - resize() - changes length (and capacity if needed)
//   - reserve() - changes capacity only (length stays the same)
//   - shrink_to_fit() - requests reducing capacity to match length
//   - Reallocation: what happens when capacity is exceeded
//
// Key insight: Reallocation is EXPENSIVE (copies all elements to new memory).
// Minimize it by reserving capacity upfront when the approximate size is known.
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>

void printInfo(const std::vector<int> &v, const char *label)
{
    std::cout << label << ": size=" << v.size()
              << ", capacity=" << v.capacity();
    if (!v.empty())
    {
        std::cout << ", elements={ ";
        for (const auto &e : v)
            std::cout << e << ' ';
        std::cout << '}';
    }
    std::cout << '\n';
}

int main()
{
    // --- 1. resize() changes length ---
    std::cout << "=== resize() - changes length ===\n";
    std::vector<int> v{1, 2, 3};
    printInfo(v, "Initial");

    v.resize(6); // grow: new elements are value-initialized (zeros for int)
    printInfo(v, "After resize(6)");

    v.resize(2); // shrink: elements beyond new size are removed
    printInfo(v, "After resize(2)");
    // Note: capacity may NOT shrink - only length changes when shrinking

    // --- 2. reserve() changes capacity only ---
    std::cout << "\n=== reserve() - changes capacity only ===\n";
    std::vector<int> r;
    printInfo(r, "Empty");

    r.reserve(100); // allocate storage for 100 elements
    printInfo(r, "After reserve(100)");
    // size is still 0! No elements were added.
    // You CANNOT access r[0]..r[99] - they don't exist yet (UB).

    r.push_back(42);
    r.push_back(99);
    printInfo(r, "After 2 push_backs");
    // Now size=2, capacity=100. No reallocation occurred!

    // --- 3. shrink_to_fit() - requests reducing capacity ---
    std::cout << "\n=== shrink_to_fit() ===\n";
    std::vector<int> s(100, 5); // 100 elements, all value 5
    printInfo(s, "Initial (100 elements)");

    s.resize(3); // shrink length to 3
    printInfo(s, "After resize(3)");
    // capacity is still ~100

    s.shrink_to_fit(); // REQUEST to free unused capacity (non-binding)
    printInfo(s, "After shrink_to_fit()");
    // capacity should now be close to 3 (implementation may round up)

    // --- 4. Watching reallocation happen ---
    std::cout << "\n=== Reallocation in action ===\n";
    std::vector<int> growing;
    std::size_t prevCapacity{0};

    for (int i{0}; i < 20; ++i)
    {
        growing.push_back(i);
        if (growing.capacity() != prevCapacity)
        {
            std::cout << "REALLOCATED at size=" << growing.size()
                      << ", new capacity=" << growing.capacity() << '\n';
            prevCapacity = growing.capacity();
        }
    }
    std::cout << "Reallocation copies ALL existing elements to new memory.\n";
    std::cout << "This is why reserve() is important for performance!\n";

    // --- 5. PITFALL: resize() vs reserve() for stack usage ---
    std::cout << "\n=== PITFALL: resize() vs reserve() ===\n";
    std::vector<int> wrong;
    wrong.resize(5);     // Creates 5 zero-initialized elements!
    wrong.push_back(10); // Now size=6: { 0, 0, 0, 0, 0, 10 }
    printInfo(wrong, "resize(5) then push_back(10)");

    std::vector<int> correct;
    correct.reserve(5);    // Pre-allocates capacity - size stays 0
    correct.push_back(10); // Now size=1: { 10 }
    printInfo(correct, "reserve(5) then push_back(10)");

    std::cout << "\nUse reserve() before push_back, resize() before operator[].\n";

    return 0;
}
