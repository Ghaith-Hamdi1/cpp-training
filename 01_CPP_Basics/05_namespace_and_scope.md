# Namespace and scope

## What is a namespace?

- Region where to declare names to remove ambiguities

## Why using namespaces?

- Remove ambiguities
- Organize source code

## Define a namespace

```cpp
namespace namespace_name {
    // code here
} // namespace namespace_name
```

## Namespace type

- User defined namespace
- Global namespace

## Access a name in a namespace

```cpp
namespace namespace_name {
    int i{5};
} // namespace namespace_name

namespace_name::i = 10;
```

## "using" directive

```cpp
namespace namespace_name {
    int i{5};
} // namespace namespace_name

using namespace namespace_name;
i = 10;
```

## Special namespace "std::"

- Do not use `using namespace std;`

## Unnamed (anonymous) namespace

- Used when you have a lot of content that you want to ensure stays local to a given file

## Inline namespace

- To manage versions of a function
- Just change `inline` to choose the version

## Scope

- Scope determines when an identifier can be seen and used

```cpp
{
    int i{0};
} // i is no longer available here (out of scope)

int add(int x, int y) {
    return x + y;
} // x and y are no longer available here (out of scope)
```

Reference example, `Examples/01_CPP_Basics/05_namespace_and_scope/03_scope.cpp`:

```cpp
#include <iostream>

int add(int x, int y) // add function x and y are created and enter scope here
{
    // add's x and y are visible/usable within this function only
    return x + y;
} // add's y and x go out of scope and are destroyed here

int main()
{
    int x{ 5 }; // main's x is created, initialized, and enters scope here
    int y{ 6 }; // main's y is created, initialized, and enters scope here

    // main's x and y are usable within this function only
    std::cout << add(x, y) << '\n'; // calls function add() with x=5 and y=6

    return 0;
} // main's y and x go out of scope and are destroyed here
```

Namespace usage reference, `Examples/01_CPP_Basics/05_namespace_and_scope/02_namespace.cpp`:

```cpp
#include <iostream>

namespace test {
    int i{5};

    void fn() {
        std::cout << "Test namespace";
    }
} // namespace test

void fn(){
    std::cout << "Global namespace";
}

using namespace test;

int main() {
    std::cout << "Before assigning new value " << i << std::endl;

    i = 10;

    std::cout << "After assigning new value " << i << std::endl;

    test::i = 20;

    std::cout << "After assigning new value with explicit namespace " << i << std::endl;
    int i{6};

    std::cout << "After assigning new value " << i << std::endl;
    std::cout << "After assigning new value " << test::i << std::endl;

    test::fn();
    ::fn();
    return 0;
}
```

---

