# Static and non-static member functions

- Static member variables: shared by all instances
  - Do not depend on class instances
  - [Diagram — extracted labels: numeric counter values shown across instances: 2, 2, 1, 2 — illustrating a shared static counter's value as seen from different objects; exact diagram layout not recoverable from text extraction]
- Static member variables initialization
  - Outside the class declaration (even if it is declared as private)
  - Inside the class declaration, if "static const" variable declaration (inline declaration)
  - Call of static member variable
  - Must be declared outside the class if to be used in-there
- Static member functions: like static member variables, they are not attached to instances
  - Shared by all instances
  - Do not need instantiation to be called
  - [Code annotation: "No need for instance to be called" / "Possible to call from instance since it is shared by all instances"]
- Static member functions rule: "this" pointer cannot be called from static member function
  - Example of use

```cpp
// examples/course/02-cpp-oop/06-static-and-non-static-member-functions/19_static_members.cpp
#include <iostream>

class IDGenerator
{
private:
    static int s_nextID; // Here's the declaration for a static member
public:
     static int getNextID(); // Here's the declaration for a static function
};

// Here's the definition of the static member outside the class.  Note we don't use the static keyword here.
// We'll start generating IDs at 1
int IDGenerator::s_nextID{ 1 };

// Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() 
{
    return s_nextID++;
}

int main()
{
    for (int count{ 0 }; count < 5; ++count)
    {
        std::cout << "The next ID is: " << IDGenerator::getNextID() << std::endl;
    }

    return 0;
}
```
