# std::stack

- `std::stack` (Last In First Out) — the so called LIFO stack
- Elements are added and removed only from top
- Stack cannot be parsed, we can only access element on top

```cpp
// Trimmed excerpt — full runnable example: examples/03-cpp-standard-library/02-sequence-containers/34_stack.cpp
#include <iostream>
#include <stack>

class A
{
public:
    explicit A(int x): m_x{x}
    {

    }
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
    std::stack<A> stack_of_A;

    stack_of_A.push(A(0));
    stack_of_A.emplace(A(1));
    stack_of_A.emplace(2);

    std::cout << "Size of stack " << stack_of_A.size() << std::endl;
    std::cout << "Element on top " << stack_of_A.top() << std::endl;

    stack_of_A.pop(); // remove element on top
    std::cout << "Element on top after removal " << stack_of_A.top() << std::endl;


    return 0;
}
```

