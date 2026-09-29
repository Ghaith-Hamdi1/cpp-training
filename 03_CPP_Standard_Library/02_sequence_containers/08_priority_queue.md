# std::priority_queue

- `std::priority_queue` is a queue that guarantees that the first element is always the greatest or smallest element
- By default, the greatest element is the first element
- Only the first element can be accessed
- The type held by `priority_queue` must implement the `operator<` or define its own comparer

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/02_sequence_containers/36_priority_queue.cpp
#include <iostream>
#include <queue>

class A
{
public:
    explicit A(int x): m_x{x} {}
    friend std::ostream& operator<<(std::ostream& out, const A& a)
    {
        out << "x=" << a.m_x;
        return out;
    }
    bool operator<(const A& a) const
    {
        return m_x < a.m_x;
    }
private:
    int m_x;
};

class B
{
public:
    explicit B(int x): m_x{x} {}
    friend std::ostream& operator<<(std::ostream& out, const B& b)
    {
        out << "x=" << b.m_x;
        return out;
    }
    int getX() const
    {
        return m_x;
    }
private:
    int m_x;
};

class Comparer
{
public:
    bool operator() (const B& b1, const B& b2)
    {
        return b1.getX() > b2.getX();
    }
};

int main()
{
    std::priority_queue<A> queue_of_A; // default: uses operator< of A, greatest first

    queue_of_A.push(A(0));
    queue_of_A.emplace(A(1));
    queue_of_A.emplace(2);

    std::cout << "Element on top " << queue_of_A.top() << std::endl;

    queue_of_A.pop(); // remove element on top
    std::cout << "Element on top after pop " << queue_of_A.top() << std::endl;

    std::cout << "****** B with custom comparer ******" << std::endl;
    std::priority_queue<B, std::deque<B>, Comparer> queue_of_BC;
    queue_of_BC.push(B(0));
    queue_of_BC.emplace(2);
    queue_of_BC.emplace(B(1));

    std::cout << "Element on top " << queue_of_BC.top() << std::endl;

    queue_of_BC.pop(); // remove element on top
    std::cout << "Element on top after pop " << queue_of_BC.top() << std::endl;

    return 0;
}
```

---

