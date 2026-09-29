# std::deque

- `std::deque` — double ended queue: used for fast insertion and deletion of elements at both ends of queue (this is the advantage of deque)
- Memory is not contiguous (unlike vector and array) and no capacity concept
- But can do almost same operations like vector (insertion, deletion at the middle, ...)
  ```cpp
  // with initialization
  std::deque<class_name> deque_object {obj1, obj2, .... };
  // without initialization
  std::deque<class_name> deque_object;
  ```

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/02_sequence_containers/31_deque.cpp
#include <iostream>
#include <deque>

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

std::ostream& operator<<(std::ostream& out, const std::deque<A>& a)
{
    out << "Deque print " << std::endl;
    for (int i = 0; i < a.size(); i++)
    {
        out << "\tindex=" << i << " -> " << a[i] << std::endl;
    }
    return out;
}

int main()
{
    std::deque<A> deque_of_A;

    deque_of_A.emplace_back(0); // works fine even constructor is explicit
    deque_of_A.emplace_front(0); // works fine even constructor is explicit
    for (size_t i = 1; i < 17; i++)
    {
        deque_of_A.push_back(A(i));
        deque_of_A.push_front(A(i));
    }
    std::cout << deque_of_A << std::endl;

    deque_of_A.pop_back();
    deque_of_A.pop_front();
    std::cout << "After one pop_back and pop_front " << deque_of_A << std::endl;

    deque_of_A.clear();
    std::cout << "After clear size=" << deque_of_A.size() << std::endl;

    deque_of_A.resize(10, A(5));
    std::cout << "After resize " << deque_of_A << std::endl;

    return 0;
}
```

