# std::vector

- `std::vector` is a dynamic (allocation) contiguous array, the size should NOT be fixed at declaration
  ```cpp
  // with initialization
  std::vector<class_name> vector_object {obj1, obj2, .... };
  // without initialization
  std::vector<class_name> vector_object;
  ```
- Refer to documentation for detailed features: https://en.cppreference.com/w/cpp/container/vector *(URL was interleaved with the footer legend in the source PDF text layer — reconstructed from context; see Conversion notes)*
- `std::vector`
  - vector capacity is the dynamically allocated memory
  - vector size is the number of elements in the vector
  - we can act on capacity by methods `reserve(x)` and `shrink_to_fit()`
  - we can act on size by methods `emplace`, `emplace_back`, `push_back`, `pop_back`, `clear`, `erase`, `resize`, `insert`

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/02_sequence_containers/30_vector.cpp
#include <iostream>
#include <vector>

class A
{
public:
    explicit A(int x): m_x{x} {}
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
private:
    int m_x;
};

int main()
{
    std::vector<A> vector_of_A;
    std::cout << "Initial state capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;

    vector_of_A.emplace_back(0); // works fine even constructor is explicit
    for (size_t i = 1; i < 17; i++)
    {
        vector_of_A.push_back(A(i));
    }
    std::cout << "After growth capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;

    vector_of_A.clear();
    vector_of_A.shrink_to_fit();
    std::cout << "After clear+shrink_to_fit capacity=" << vector_of_A.capacity() << " size=" << vector_of_A.size() << std::endl;

    //vector_of_A.resize(10); // doesn't work since A doesn't have default constructor
    vector_of_A.resize(10, A(5));
    std::cout << "After resize size=" << vector_of_A.size() << std::endl;

    vector_of_A.reserve(50);
    std::cout << "After reserve capacity=" << vector_of_A.capacity() << std::endl;

    vector_of_A.pop_back();
    std::cout << "After pop_back size=" << vector_of_A.size() << std::endl;

    return 0;
}
```

