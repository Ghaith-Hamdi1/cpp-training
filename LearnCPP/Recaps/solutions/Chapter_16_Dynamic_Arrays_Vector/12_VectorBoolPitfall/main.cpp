// Chapter 16 - Project 12: std::vector<bool> Pitfall
// ====================================================
// std::vector<bool> is a SPECIAL implementation that packs bools into bits.
// It is NOT a true container and has several problems:
//   - Elements are not actual bool values (they're proxy references)
//   - Memory is not contiguous (bit-packed)
//   - Incompatible with some standard library algorithms
//   - operator[] returns a proxy object, not a bool&
//
// Alternatives:
//   - std::vector<char>  - runtime-resizable, behaves like a real container
//   - std::bitset         - compile-time fixed size, efficient bit ops
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <bitset>

int main()
{
    // --- 1. std::vector<bool> works but has hidden problems ---
    std::cout << "=== std::vector<bool> - looks normal but isn't ===\n";
    std::vector<bool> flags{true, false, true, true, false};

    std::cout << "flags: ";
    for (auto f : flags)
        std::cout << f << ' ';
    std::cout << '\n';

    // This compiles and seems to work...
    flags[1] = true;
    std::cout << "After flags[1] = true: ";
    for (auto f : flags)
        std::cout << f << ' ';
    std::cout << '\n';

    // --- 2. The problem: operator[] returns a proxy, not a bool& ---
    std::cout << "\n=== The proxy reference problem ===\n";
    // For a normal vector<int>, this works:
    //   int& ref = myIntVec[0];  // OK - real reference
    //
    // For vector<bool>, this FAILS:
    //   bool& ref = flags[0];    // ERROR! operator[] returns a proxy object
    //
    // You can only use:
    auto proxyRef = flags[0]; // auto deduces the proxy type, not bool
    std::cout << "flags[0] via proxy: " << proxyRef << '\n';
    std::cout << "The return type of flags[0] is NOT bool& - it's a proxy.\n";

    // --- 3. Alternative: std::vector<char> ---
    std::cout << "\n=== Alternative: std::vector<char> ===\n";
    std::vector<char> charFlags{1, 0, 1, 1, 0}; // 0/1 instead of false/true

    // This is a REAL container with contiguous memory
    char &realRef = charFlags[0]; // This works - real reference!
    std::cout << "charFlags[0] via real reference: " << static_cast<int>(realRef) << '\n';

    charFlags.push_back(1);
    std::cout << "charFlags after push_back: ";
    for (auto f : charFlags)
        std::cout << static_cast<int>(f) << ' ';
    std::cout << "(size=" << charFlags.size() << ")\n";

    // --- 4. Alternative: std::bitset (fixed size at compile time) ---
    std::cout << "\n=== Alternative: std::bitset ===\n";
    std::bitset<8> bits{0b10110010}; // 8 bits, initialized with binary

    std::cout << "bits: " << bits << '\n';
    std::cout << "bits[0] = " << bits[0] << '\n'; // least significant bit
    std::cout << "bits[7] = " << bits[7] << '\n'; // most significant bit

    bits.set(0);   // set bit 0 to 1
    bits.reset(1); // set bit 1 to 0
    bits.flip(2);  // toggle bit 2
    std::cout << "After set(0), reset(1), flip(2): " << bits << '\n';
    std::cout << "Count of 1-bits: " << bits.count() << '\n';

    // --- Summary ---
    std::cout << "\n=== Summary ===\n";
    std::cout << "AVOID std::vector<bool> - it's not a real container.\n";
    std::cout << "Use std::vector<char>   - for runtime-sized bool arrays.\n";
    std::cout << "Use std::bitset<N>      - for compile-time-sized bit arrays.\n";

    return 0;
}
