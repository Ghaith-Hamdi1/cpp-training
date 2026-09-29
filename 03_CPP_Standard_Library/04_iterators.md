# Iterators

(Slides 23–28)

- Iterator is an object that allows parsing a container and provides access to the elements
- Iterator types:
  - Forward iterator
  - Reverse iterator
  - Constant forward iterator
  - Constant reverse iterator
- Advantage of iterators: can parse the container with standard way without caring about container implementation, `++` operator for incrementation and `*` for accessing elements

# Forward and reverse iterators

- Forward iterators
  - Iterator to get the container beginning: `begin` (non-const) and `cbegin` (constant)
  - Iterator to get the container end: `end` (non-const) and `cend` (constant)
- Reverse iterators
  - Iterator to get the container beginning: `rbegin` (non-const) and `crbegin` (constant)
  - Iterator to get the container end: `rend` (non-const) and `crend` (constant)
- Difference between forward and reverse iterators: `end` and `rend` are always not part of the container, but just give a reference to the container ending

# Range based loops and iterator invalidation

- Range based loops
  - [Code screenshot in source — not extractable as text; the visible caption reads: "type here is int"]
- Iterator invalidation: when an iterator is iterating on an element that has changed address or been destroyed, we say that the iterator has been invalidated. So, the iterator is dangling and accessing it causes undefined behavior. *(the accompanying code sample for this was also a screenshot in the source and could not be extracted as text)*

# Operators for iterators

- `operator*` — dereferencing the iterator returns the element value the iterator is pointing on
- `operator++` — move iterator to point on next element
- `operator--` — move iterator to point on next element (not always available for all containers)
- `operator==` and `operator!=`
- `operator=` — assigning an iterator to another

# Standard iteration pattern

- Generally, to iterate through a container, we use the following pattern:
  - [Code screenshot in source — "Forward iterator" pattern and "Reverse iterator" pattern shown side by side; not extractable as text. Recovered equivalent code below from `Examples/03_CPP_Standard_Library/04_iterators/45_iterators.cpp`]

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/04_iterators/45_iterators.cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>

int main()
{
    std::vector<int> vect {1, 2, 3, 4, 5};

    std::cout << "Forward vector iterator" << std::endl;
    std::vector<int>::iterator itf = vect.begin();
    while (itf != vect.end()) {
        std::cout << *itf << std::endl; // access element value
        (*itf)++; // increment value
        itf++; // increment iterator
    }
    std::cout << "Forward vector const iterator" << std::endl;
    for (auto citf = vect.cbegin(); citf != vect.cend(); ++citf) {
        std::cout << *citf << std::endl;
        // cannot change value since it is const iterator
        //(*citf)++;
    }

    std::cout << "Reverse vector iterator" << std::endl;
    std::vector<int>::reverse_iterator itr = vect.rbegin();
    while (itr != vect.rend()) {
        std::cout << *itr << std::endl; // access element value
        (*itr)++; // increment value
        itr++; // increment iterator
    }
    std::cout << "Reverse vector const iterator" << std::endl;
    for (auto citr = vect.crbegin(); citr != vect.crend(); ++citr) {
        std::cout << *citr << std::endl;
        // cannot change value since it is const iterator
        //(*citr)++;
    }

    // the same forward-iteration pattern works unchanged on other container types
    std::cout << "/**************  Map  ********/" << std::endl;
    std::map<int, std::string> mymap;
    mymap.insert(std::make_pair(2, "orange"));
    mymap.insert(std::make_pair(1, "banana"));

    auto itm{ mymap.cbegin() }; // declare a const iterator and assign to start of map
    while (itm != mymap.cend()) // while it hasn't reach the end
    {
        std::cout << (*itm).first << '=' << itm->second << ' '; // print the value of the element it points to
        ++itm; // and iterate to the next element
    }
    std::cout << std::endl;

    return 0;
}
```

---

