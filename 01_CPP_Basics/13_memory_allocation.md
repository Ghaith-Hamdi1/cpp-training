# Memory Allocation

- C++ supports three memory allocation types:
  - Static memory allocation: happens for static and global variables.
  - Automatic memory allocation: happens for function parameters and local variables.
    - Size must be known at compile time
    - Allocation and free will be done automatically at instantiation / destruction
  - Dynamic memory allocation: happens on user demand to allocate and free memory
    - Size of memory can be determined at runtime

## Dynamic memory allocation: allocation and free

- Allocation, single variable:

```cpp
type_name* ptr_var { new type_name{init_value} };
```

- Allocation, many elements:

```cpp
type_name* ptr_var { new type_name[]{init_value1, init_value2, ...} };
```

- Free, single variable:

```cpp
delete ptr_var;
ptr_var = nullptr;
```

- Free, many elements:

```cpp
delete[] ptr_var;
ptr_var = nullptr;
```

- Always be sure to free allocated memory at every exit point (function, scope of pointer, ...)

## Dynamic memory allocation: dangling pointers

- Dangling pointer: do not use a pointer after it has been freed (may cause a crash)
  - Best practice is to set the pointer to `nullptr` right after `delete`
- Do not access a pointer value that overflows the allocated size (may cause a crash)

## Dynamic memory allocation: allocation failures

- `new` operator call may fail in rare cases (e.g. no memory space left)
  - Best practice is to check if the allocated pointer value is not `nullptr`
- Do not use an already-allocated pointer to allocate it again
  - We sometimes need to check if a pointer is `nullptr` before allocation

Reference example, `Examples/01_CPP_Basics/13_memory_allocation/16_memory_allocation.cpp`:

```cpp
#include <iostream>

int main()
{
    int *ptr = new int[10];
    for (int i = 0; i < 10; i++)
    {
        *ptr++ = i; // set content and increment, see operator associativity table
    }


    for (int i = 0; i < 10; i++)
    {
        std::cout << "Ptr[" << 10 - 1 - i << "]" << *--ptr << std::endl; // decrement ptr and get its contents, see operator associativity table
    }

    delete[] ptr;

    return 0;
}
```

---

