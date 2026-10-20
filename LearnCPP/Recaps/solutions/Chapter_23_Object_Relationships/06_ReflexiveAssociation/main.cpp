// Chapter 23 - Project 06: Reflexive Association
// ==================================================
//
// A reflexive association is a relationship where an object
// has a relationship with another object of the SAME type.
//
// Examples:
//   - A university course that has a prerequisite (also a course)
//   - An employee who has a manager (also an employee)
//   - A linked list node that points to the next node
//
// This is a special case of association, not a new relationship type.

#include <iostream>
#include <string>
#include <vector>

class Employee
{
private:
    std::string m_name;
    std::string m_title;
    Employee *m_manager{};             // Reflexive: points to same type
    std::vector<Employee *> m_reports; // Direct reports (also same type)

public:
    Employee(std::string_view name, std::string_view title)
        : m_name{name}, m_title{title}
    {
    }

    const std::string &getName() const { return m_name; }
    const std::string &getTitle() const { return m_title; }

    void setManager(Employee &manager)
    {
        m_manager = &manager;
        manager.m_reports.push_back(this);
    }

    void printChain() const
    {
        std::cout << m_name << " (" << m_title << ")";
        if (m_manager)
        {
            std::cout << " -> reports to ";
            m_manager->printChain(); // Recursive up the chain
        }
        else
        {
            std::cout << " [TOP]";
        }
    }

    void printDirectReports() const
    {
        std::cout << m_name << "'s direct reports:\n";
        if (m_reports.empty())
        {
            std::cout << "  (none)\n";
            return;
        }
        for (const auto *r : m_reports)
            std::cout << "  - " << r->getName() << " (" << r->getTitle() << ")\n";
    }
};

int main()
{
    Employee ceo{"Alice", "CEO"};
    Employee vp{"Bob", "VP Engineering"};
    Employee lead{"Carol", "Tech Lead"};
    Employee dev1{"Dave", "Developer"};
    Employee dev2{"Eve", "Developer"};

    // Build the reporting hierarchy (reflexive associations)
    vp.setManager(ceo);
    lead.setManager(vp);
    dev1.setManager(lead);
    dev2.setManager(lead);

    std::cout << "=== Reflexive Association: Employee Hierarchy ===\n\n";

    // Print reporting chain from bottom up
    std::cout << "Reporting chain for Dave:\n  ";
    dev1.printChain();
    std::cout << "\n\n";

    std::cout << "Reporting chain for Eve:\n  ";
    dev2.printChain();
    std::cout << "\n\n";

    // Print direct reports
    ceo.printDirectReports();
    std::cout << '\n';
    lead.printDirectReports();
    std::cout << '\n';
    dev1.printDirectReports();

    std::cout << "\nNote: Every pointer in this hierarchy is Employee* ->\n"
              << "an object relating to another object of the same type.\n";

    return 0;
}
