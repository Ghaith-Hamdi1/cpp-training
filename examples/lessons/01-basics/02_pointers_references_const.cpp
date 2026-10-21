// Lesson 1: pointers, array decay, references (cannot be re-bound), const with pointers.
#pragma GCC diagnostic ignored "-Wsizeof-array-argument"   // deliberate: shows the decay
#include <cstddef>
#include <iostream>

void takesArray(int arr[]) {          // really `int* arr`: the size is lost
    std::cout << "sizeof(arr) inside the function = " << sizeof(arr) << " (a pointer)\n";
}

int main() {
    int x = 10;
    int* p = &x;                      // p holds the ADDRESS of x
    *p = 20;                          // write through the pointer
    int y = *p;                       // read through the pointer
    std::cout << "x = " << x << ", y = " << y << ", p points to x: " << (p == &x) << '\n';
    p = nullptr;
    if (!p) std::cout << "p is null: do not dereference it\n";

    int a[3] = {10, 20, 30};
    int* q = a;                       // the array name decays to &a[0]
    std::cout << *q << ' ' << *(q + 1) << ' ' << q[2] << "   (p + 1 moves one element)\n";
    std::cout << "sizeof(a) = " << sizeof(a) << " bytes here, ";
    takesArray(a);

    int r1 = 1, r2 = 2;
    int& r = r1;
    r = r2;                           // does NOT re-bind r: assigns r2's value into r1
    std::cout << "r1 = " << r1 << ", r2 = " << r2 << "   // r1 became 2\n";

    int m = 1, n = 2;
    const int* p1 = &m;               // pointer to const int: data locked, pointer may move
    p1 = &n;
    int* const p2 = &m;               // const pointer to int: pointer locked, data may change
    *p2 = 5;
    std::cout << "*p1 = " << *p1 << ", m = " << m << '\n';
    // *p1 = 9;                       // ERROR: cannot change the int through p1
    // p2 = &n;                       // ERROR: the pointer may not move

    int* heap = new int(42);          // heap object: you must delete it
    std::cout << "heap value " << *heap << '\n';
    delete heap;
    heap = nullptr;                   // avoid leaving a dangling pointer
}
