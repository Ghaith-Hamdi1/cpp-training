// Project 09: Overloading the Subscript Operator []
// ====================================================
// operator[] MUST be a member function. It should return a reference so the
// result can be used as an l-value for assignment. Provide BOTH a non-const
// version (returns T&) and a const version (returns const T&).
//
// PITFALL: Calling operator[] on a pointer to an object will index an array
// of objects, not call your overloaded operator. Dereference first: (*ptr)[i]
//
// PITFALL: Forgetting the const version means const objects can't use [].

#include <iostream>
#include <cassert>
#include <string>

class IntArray
{
private:
    int m_data[10]{}; // Fixed-size array for simplicity

public:
    // --- Non-const operator[] ---
    // Returns int& so the caller can both read AND write: arr[3] = 42;
    int &operator[](int index)
    {
        assert(index >= 0 && index < 10 && "Index out of bounds!");
        return m_data[index];
    }

    // --- Const operator[] ---
    // Returns const int& - used when the object is const (read-only access).
    // Without this, you couldn't use [] on a const IntArray at all!
    const int &operator[](int index) const
    {
        assert(index >= 0 && index < 10 && "Index out of bounds!");
        return m_data[index];
    }
};

// --- Example with non-integer subscript (std::string key) ---
// The parameter to operator[] doesn't have to be an integer!

class SimpleMap
{
private:
    static constexpr int maxSize{5};
    std::string m_keys[maxSize]{};
    int m_values[maxSize]{};
    int m_count{0};

    int findOrInsert(const std::string &key)
    {
        // Search for existing key
        for (int i = 0; i < m_count; ++i)
        {
            if (m_keys[i] == key)
                return i;
        }
        // Insert new key if space available
        assert(m_count < maxSize && "Map is full!");
        m_keys[m_count] = key;
        return m_count++;
    }

public:
    // operator[] with a string key - returns a reference to the value
    int &operator[](const std::string &key)
    {
        int index = findOrInsert(key);
        return m_values[index];
    }

    void print() const
    {
        for (int i = 0; i < m_count; ++i)
            std::cout << "  " << m_keys[i] << " => " << m_values[i] << '\n';
    }
};

// Helper to demonstrate the const version
void printElement(const IntArray &arr, int index)
{
    // This calls the CONST version of operator[]
    // because 'arr' is a const reference.
    std::cout << "arr[" << index << "] = " << arr[index] << '\n';
}

int main()
{
    // --- Basic integer subscript ---
    std::cout << "=== IntArray with operator[] ===\n";
    IntArray arr;
    arr[0] = 10; // Uses non-const operator[] - writing
    arr[1] = 20;
    arr[2] = 30;

    std::cout << "arr[0] = " << arr[0] << '\n'; // Uses non-const - reading
    std::cout << "arr[1] = " << arr[1] << '\n';
    std::cout << "arr[2] = " << arr[2] << '\n';

    // --- Const version is called here ---
    std::cout << "\nUsing const operator[]:\n";
    printElement(arr, 0);
    printElement(arr, 1);

    // --- String-keyed subscript ---
    std::cout << "\n=== SimpleMap with string operator[] ===\n";
    SimpleMap scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Eve"] = 92;
    scores["Alice"] = 98; // Update existing key

    scores.print();

    // --- PITFALL: pointer to object ---
    std::cout << "\n=== PITFALL: Pointer to object ===\n";
    IntArray *ptr = &arr;
    // ptr[2];       // WRONG! This indexes an array of IntArray objects!
    std::cout << "(*ptr)[2] = " << (*ptr)[2] << '\n'; // CORRECT: dereference first

    return 0;
}
