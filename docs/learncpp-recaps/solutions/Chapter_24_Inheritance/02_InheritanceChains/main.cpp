// Project 02 - Inheritance Chains
// =================================
// Demonstrates multi-level inheritance: Person → Employee → Manager.
// Each level inherits from the one above and adds its own members.

#include <iostream>
#include <string>
#include <string_view>

// Level 0 - most-base class
class Person
{
private:
    std::string m_name{};
    int m_age{};

public:
    Person(std::string_view name, int age)
        : m_name{name}, m_age{age}
    {
    }

    const std::string &getName() const { return m_name; }
    int getAge() const { return m_age; }

    void identify() const
    {
        std::cout << "Person: " << m_name << ", age " << m_age << '\n';
    }
};

// Level 1 - inherits from Person, adds company/employee ID
class Employee : public Person
{
private:
    std::string m_company{};
    int m_employeeId{};

public:
    Employee(std::string_view name, int age, std::string_view company, int employeeId)
        : Person{name, age} // delegate to Person constructor
          ,
          m_company{company}, m_employeeId{employeeId}
    {
    }

    const std::string &getCompany() const { return m_company; }
    int getEmployeeId() const { return m_employeeId; }

    void showEmployeeInfo() const
    {
        std::cout << "Employee #" << m_employeeId
                  << " at " << m_company << '\n';
    }
};

// Level 2 - inherits from Employee (which inherits from Person)
class Manager : public Employee
{
private:
    int m_directReports{}; // number of people managed

public:
    Manager(std::string_view name, int age, std::string_view company,
            int employeeId, int directReports)
        : Employee{name, age, company, employeeId} // delegate to Employee
          ,
          m_directReports{directReports}
    {
    }

    void showManagerInfo() const
    {
        // A Manager has access to all public/protected members
        // in the entire chain: Person → Employee → Manager
        std::cout << getName() << " manages " << m_directReports
                  << " people at " << getCompany() << '\n';
    }
};

int main()
{
    Manager mgr{"Alice", 40, "TechCorp", 1001, 12};

    // Functions inherited from Person (level 0):
    mgr.identify();

    // Functions inherited from Employee (level 1):
    mgr.showEmployeeInfo();

    // Functions defined in Manager (level 2):
    mgr.showManagerInfo();

    std::cout << '\n';

    // We can also create objects at intermediate levels
    Employee emp{"Bob", 30, "TechCorp", 1025};
    emp.identify();         // from Person
    emp.showEmployeeInfo(); // from Employee
    // emp.showManagerInfo();  // ERROR - Employee has no Manager members

    return 0;
}
