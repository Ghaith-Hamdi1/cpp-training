// Chapter 23 - Project 02: Aggregation ("has-a")
// =================================================
//
// Aggregation is a weaker form of object composition.
// Key properties:
//   1. Parts can belong to multiple objects simultaneously.
//   2. The whole does NOT manage the lifetime of its parts.
//   3. The part does not know about the whole (unidirectional).
//
// Implementation: References or pointers to externally created objects.
//
// Pitfall: Since the aggregate doesn't destroy its parts,
// forgetting to clean them up externally causes memory leaks.

#include <iostream>
#include <string>
#include <vector>

// A Teacher exists independently of any Department.
class Teacher
{
private:
    std::string m_name;
    std::string m_subject;

public:
    Teacher(std::string_view name, std::string_view subject)
        : m_name{name}, m_subject{subject}
    {
    }

    const std::string &getName() const { return m_name; }
    const std::string &getSubject() const { return m_subject; }
};

// A Department aggregates (has) teachers, but does NOT own them.
// Teachers can exist in multiple departments and outlive the department.
class Department
{
private:
    std::string m_name;
    std::vector<const Teacher *> m_teachers; // Aggregation: pointers, NOT owned

public:
    Department(std::string_view name) : m_name{name} {}

    void addTeacher(const Teacher &teacher)
    {
        m_teachers.push_back(&teacher);
    }

    void printRoster() const
    {
        std::cout << "Department: " << m_name << '\n';
        for (const auto *t : m_teachers)
        {
            std::cout << "  - " << t->getName()
                      << " (teaches " << t->getSubject() << ")\n";
        }
    }
};

int main()
{
    // Teachers are created externally - the Department doesn't own them
    Teacher alice{"Alice", "Physics"};
    Teacher bob{"Bob", "Mathematics"};
    Teacher carol{"Carol", "Computer Science"};

    // A single teacher can be in multiple departments (aggregation!)
    Department science{"Science"};
    science.addTeacher(alice);
    science.addTeacher(carol);

    Department engineering{"Engineering"};
    engineering.addTeacher(bob);
    engineering.addTeacher(carol); // Carol is in both departments

    std::cout << "=== Aggregation: Teachers in Departments ===\n\n";
    science.printRoster();
    std::cout << '\n';
    engineering.printRoster();

    std::cout << "\nNote: Carol appears in both departments.\n";
    std::cout << "When the departments are destroyed, the teachers still exist.\n";

    // Teachers outlive the departments - no double-delete issues
    // because the Department never calls delete on them.

    return 0;
}
