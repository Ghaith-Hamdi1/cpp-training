// Chapter 26 - Project 6: Full Class Template Specialization
// =============================================================
// You can fully specialize an ENTIRE class for a specific type.
// The specialization is treated as a completely independent class:
//   - It can have different data members.
//   - It can have a different interface.
//   - It can have a completely different implementation.
//
// Classic example: Storage8<bool> packs 8 booleans into a single byte
// using bit manipulation, instead of using an 8-element bool array.
//
// Important:
//   - Define the specialization in the SAME header as the primary template.
//     If the specialization header isn't included, the compiler silently
//     uses the non-specialized version - a subtle, hard-to-find bug.

#include <cstdint>
#include <iostream>

// ---------------------------------------------------------------------------
// Primary template: stores 8 values of type T in an array
// ---------------------------------------------------------------------------
template <typename T>
class Storage8
{
private:
    T m_data[8]{};

public:
    void set(int index, const T &value)
    {
        m_data[index] = value;
    }

    const T &get(int index) const
    {
        return m_data[index];
    }

    void print() const
    {
        for (int i{0}; i < 8; ++i)
            std::cout << "[" << i << "]=" << m_data[i] << "  ";
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
// Full specialization for bool - packs 8 bools into a single byte
// ---------------------------------------------------------------------------
// Note: `template <>` with the specific type after the class name.
//       This is an entirely new class definition.
template <>
class Storage8<bool>
{
private:
    std::uint8_t m_bits{}; // 1 byte holds all 8 booleans

public:
    void set(int index, bool value)
    {
        // Set or clear the bit at 'index'
        if (value)
            m_bits |= (1 << index); // set bit
        else
            m_bits &= ~(1 << index); // clear bit
    }

    bool get(int index) const
    {
        // Extract the bit at 'index'
        return (m_bits & (1 << index)) != 0;
    }

    void print() const
    {
        for (int i{0}; i < 8; ++i)
            std::cout << "[" << i << "]=" << (get(i) ? "true " : "false") << "  ";
        std::cout << '\n';
    }

    // Extra function only in the specialization - shows size savings
    void printRawByte() const
    {
        std::cout << "Raw bits: ";
        for (int i{7}; i >= 0; --i)
            std::cout << ((m_bits >> i) & 1);
        std::cout << '\n';
    }
};

// ---------------------------------------------------------------------------
int main()
{
    // Uses the primary template → 8 ints = 32 bytes (typically)
    Storage8<int> intStore;
    for (int i{0}; i < 8; ++i)
        intStore.set(i, (i + 1) * 10);

    std::cout << "Storage8<int>:  ";
    intStore.print();
    std::cout << "  sizeof = " << sizeof(intStore) << " bytes\n\n";

    // Uses the full specialization → 1 byte for 8 bools!
    Storage8<bool> boolStore;
    boolStore.set(0, true);
    boolStore.set(1, false);
    boolStore.set(2, true);
    boolStore.set(3, true);
    boolStore.set(4, false);
    boolStore.set(5, true);
    boolStore.set(6, false);
    boolStore.set(7, true);

    std::cout << "Storage8<bool>: ";
    boolStore.print();
    boolStore.printRawByte(); // shows the internal bit pattern
    std::cout << "  sizeof = " << sizeof(boolStore) << " byte(s)\n";

    return 0;
}
