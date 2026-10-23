# Singleton

- Singleton design pattern ensures that a class has only one instance, while providing access to this instance
- Used for objects that must be unique like a database for example
- source: https://refactoring.guru/design-patterns/singleton

```cpp
// Representative example (examples/course/04-templates-and-design-patterns/06-design-patterns/68_singleton.cpp)
class Singleton
{
public:
    static Singleton& instance()
    {
        static Singleton instance;
        return instance;
    }

    void setValue(const int & val) {
        m_val = val;
    }

    void print() {
        // print address of currrent object to
        // make sure that this is the same object
        std::cout << this << " Print value " << m_val << std::endl;
    }
    /* implement all needed functions */
private:
    Singleton() : m_val{0} {
        std::cout << "Call Singleton constructor" << std::endl;
    };
    int m_val;
};

int main(){
    Singleton::instance().print();
    Singleton::instance().setValue(10);
    Singleton::instance().print();
    return 0;
}
```
