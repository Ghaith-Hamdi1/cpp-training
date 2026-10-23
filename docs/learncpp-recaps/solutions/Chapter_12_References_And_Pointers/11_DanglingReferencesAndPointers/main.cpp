// Chapter 12 - Project 11: Dangling References and Pointers
// ===========================================================
// A dangling reference/pointer refers to a destroyed object.
// Accessing it is UNDEFINED BEHAVIOR - the #1 cause of C++ crashes.
//
// Common causes:
//   1. Returning a local variable by reference or address
//   2. Keeping a pointer/reference to a variable that goes out of scope
//   3. Deleting (or destroying) an object but keeping a pointer to it
//
// Prevention:
//   • Never return a local by reference/address
//   • Set pointers to nullptr after the pointed-to object is destroyed
//   • Prefer references over pointers (references can't be null or reseated)
//   • Keep object lifetimes clear and predictable

#include <iostream>

// ---------- Dangling pointer scenario (illustrated safely) ----------

void demonstrateDanglingPointer()
{
    int *ptr{nullptr};

    {
        int local{42};
        ptr = &local;
        std::cout << "Inside block: *ptr = " << *ptr << '\n'; // 42 - valid here
    }
    // 'local' is now destroyed - ptr is DANGLING
    // Accessing *ptr here would be UNDEFINED BEHAVIOR:
    // std::cout << *ptr;  // UB!

    // FIX: set to nullptr after the object is destroyed
    ptr = nullptr;
    std::cout << "After block:  ptr is " << (ptr ? "valid" : "null (safe)") << '\n';
}

// ---------- Dangling reference scenario (illustrated via comments) ----------

// WRONG: returning a reference to a local
// const int& makeRef()
// {
//     int val{ 100 };
//     return val;  // DANGLING: val dies here
// }

// CORRECT: return by value instead
int makeValue()
{
    int val{100};
    return val; // copy (or move) - safe
}

// ---------- Safe patterns ----------

// Returning a reference parameter is safe - the object outlives the function
int &maxRef(int &a, int &b)
{
    return (a > b) ? a : b;
}

int main()
{
    std::cout << "=== Dangling Pointer Demo ===\n";
    demonstrateDanglingPointer();

    std::cout << "\n=== Safe return by value ===\n";
    int result{makeValue()};
    std::cout << "makeValue() returned: " << result << '\n';

    std::cout << "\n=== Safe return by reference (reference param) ===\n";
    int x{10}, y{20};
    int &bigger{maxRef(x, y)};
    std::cout << "maxRef(10, 20) = " << bigger << '\n';

    // Modifying through the returned reference modifies y
    bigger = 99;
    std::cout << "After bigger = 99: y = " << y << '\n';

    // ---------- Pointer discipline: always valid or nullptr ----------
    std::cout << "\n=== Pointer discipline ===\n";
    int *p{nullptr}; // start null
    {
        int temp{55};
        p = &temp;
        std::cout << "p points to temp: *p = " << *p << '\n';
    }
    // temp is gone - set p to nullptr immediately
    p = nullptr;
    // Now safe: we won't accidentally dereference a dangling pointer
    if (p)
        std::cout << "*p = " << *p << '\n';
    else
        std::cout << "p is null - safe, no dangling access.\n";

    return 0;
}
