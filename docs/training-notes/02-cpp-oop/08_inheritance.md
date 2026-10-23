# Inheritance

- Inheritance represents the relationship "is-a"
- An object inherits from another one means that it take the attributes and behavior of the parent class (of course while respecting the access rules)
- We call "parent" or "base" the class that will be inherited
- We call "child" or "derived" the class that will inherit from "base"
- Inheritance declaration: `class ChildName : access_specifier ParentClassName`
- Inheritance allows regrouping common behavior and data in base class (avoid duplication)

- Inheritance access specifier: public

| Access specifier in base class | Access specifier when public inheritance |
|---|---|
| Public | Public |
| Protected | Protected |
| Private | Inaccessible |

  - Always use public inheritance unless other type needed

- Inheritance access specifier: protected

| Access specifier in base class | Access specifier when protected inheritance |
|---|---|
| Public | Protected |
| Protected | Protected |
| Private | Inaccessible |

  - Its usage is very rare

- Inheritance access specifier: private

| Access specifier in base class | Access specifier when private inheritance |
|---|---|
| Public | Private |
| Protected | Private |
| Private | Inaccessible |

  - Next hierarchy won't see any attribute of base class

- Order of construction of derived class
  - In case of chain of inheritance, the first base class constructor is called first and then derived constructors are called in the order, and last derived class constructor is called at the end.
  - [Diagram — extracted labels: "Base class constructor is called first" → ... → "Derived class constructor is called at the end"]
- Order of construction of derived class: call of specific constructor
  - If not explicitly specified, default constructor of base class is called automatically in the constructor of derived class
  - Do not try to initialize base class members from derived constructor, but call the base class custom constructor instead
  - The order of destruction will be in reverse of constructors calls
- Multiple inheritance is allowed in C++
  - Means that the derived class inherits from all base classes
  - [Diagram — In case of ambiguities, the origin base class should be specified]

```cpp
// Trimmed excerpt — full runnable example: examples/course/02-cpp-oop/08-inheritance/21_inheritance.cpp
#include <iostream>
#include <string>

class Person
{
public:
    Person() : m_name{""}, m_age{0} 
    {
        std::cout << "Person default constructor: name " << m_name << " age " << m_age << std::endl;
    }

    Person(const std::string& name, int age = 18) : m_name{name}, m_age{age} 
    {
        std::cout << "Person custom constructor: name " << m_name << " age " << m_age << std::endl;
    }
    virtual ~Person()
    {
        std::cout << "Person destructor" << std::endl;
    }

    std::string getName() const 
    {
        return m_name;
    }
protected:
    std::string m_name;
    int m_age;
};

// private inheritance: Person's public/protected members become private in Student
class Student : private Person
{
public:
    Student()
    {
        std::cout << "Student default constructor: name " << m_name << " age " << m_age << std::endl;
    }
    Student(const std::string& name) : Person(name) // , m_age{18} can't call it here
    {
        std::cout << "Student custom constructor: name " << m_name << " age " << m_age << std::endl;
        m_age = 20; // allowed to be called here
    }
    virtual ~Student()
    {
        std::cout << "Student destructor" << std::endl;
    }
};

class Employee
{
public:
    Employee(const std::string& name, int id) : m_name{name}, m_id{id}
    {
        std::cout << "Employee custom constructor: name " << m_name << " id " << m_id << std::endl;
    }
    virtual ~Employee()
    {
        std::cout << "Employee destructor" << std::endl;
    }
    std::string getName() const 
    {
        return m_name;
    }
protected:
    std::string m_name;
    int m_id;
};

class Engineer : public Person, public Employee
{
public:
    // declaring default constructor is mandatory since Person requires a 
    // default constructor if we don't call initialization of base constructors "Person(name, age), Employee(name, id)"
    Engineer(const std::string& name, int id, int age) : Person(name, age), Employee(name, id)
    {
        // if called m_name barely, it will be ambiguous, which m_name to take
        std::cout << "Engineer custom constructor: person name " << Person::m_name 
        << " Employee name " << Employee::m_name << " id " << m_id << " age " << m_age << std::endl;
    }
    virtual ~Engineer() 
    {
        std::cout << "Engineer destructor" << std::endl;
    }
};

int main()
{
    {
        // check order of call
        Student student("Joe");
    }
    {
        // multiple inheritance: qualify the ambiguous member with its base class
        Engineer engineer("Alex", 1, 28);
        std::cout << "Get engineer name from Employee " << engineer.Employee::getName() 
            << " from person " << engineer.Person::getName() << std::endl;
    }

    return 0;
}
```

---

## Addendum: Return to inheritance

- "final" specifier: used in Functions to prohibit overriding it
- "final" specifier: used in classes to prohibit inheriting from it
