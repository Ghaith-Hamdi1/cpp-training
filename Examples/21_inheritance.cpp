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

class HighSchoolStudent : public Student
{
public:
    HighSchoolStudent()
    {
        // m_name for example is not accesible here
        std::cout << "HighSchoolStudent default constructor" << std::endl;
    }
    virtual ~HighSchoolStudent()
    {
        std::cout << "HighSchoolStudent destructor" << std::endl;
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
        Engineer engineer("Alex", 1, 28);
        std::cout << "Get engineer name from Employee " << engineer.Employee::getName() 
            << " from person " << engineer.Person::getName() << std::endl;
    }
    HighSchoolStudent st;

    return 0;
}