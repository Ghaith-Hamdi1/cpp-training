// Chapter 23 - Project 04: Unidirectional Association ("uses-a")
// ================================================================
//
// An association is a relationship between otherwise UNRELATED objects.
// Unlike composition/aggregation, there is no whole/part hierarchy.
//
// Unidirectional: Only one side knows about the other.
//
// Properties:
//   - Neither object manages the other's lifetime.
//   - The relationship can be optional (pointer may be null).
//   - Implemented via pointers (or sometimes IDs for indirect association).

#include <iostream>
#include <string>
#include <vector>

class Course; // forward declaration

// A Student can be enrolled in a Course (unidirectional: Student → Course).
// The Course does NOT know about the Student in this design.
class Course
{
private:
    std::string m_name;
    int m_credits{};

public:
    Course(std::string_view name, int credits)
        : m_name{name}, m_credits{credits}
    {
    }

    const std::string &getName() const { return m_name; }
    int getCredits() const { return m_credits; }
};

class Student
{
private:
    std::string m_name;
    std::vector<const Course *> m_courses; // Association: Student uses Courses

public:
    Student(std::string_view name) : m_name{name} {}

    void enroll(const Course &course)
    {
        m_courses.push_back(&course);
    }

    void printSchedule() const
    {
        std::cout << m_name << "'s schedule:\n";
        if (m_courses.empty())
        {
            std::cout << "  (no courses)\n";
            return;
        }

        int totalCredits{0};
        for (const auto *c : m_courses)
        {
            std::cout << "  - " << c->getName()
                      << " (" << c->getCredits() << " credits)\n";
            totalCredits += c->getCredits();
        }
        std::cout << "  Total credits: " << totalCredits << '\n';
    }
};

int main()
{
    // Courses exist independently
    Course physics{"Physics 101", 4};
    Course calculus{"Calculus I", 3};
    Course cpp{"C++ Programming", 3};

    // Students associate with courses (unidirectional)
    Student alice{"Alice"};
    alice.enroll(physics);
    alice.enroll(calculus);

    Student bob{"Bob"};
    bob.enroll(calculus);
    bob.enroll(cpp);

    std::cout << "=== Unidirectional Association ===\n\n";
    alice.printSchedule();
    std::cout << '\n';
    bob.printSchedule();

    std::cout << "\nNote: Course objects have no knowledge of which students\n"
              << "are enrolled - only the Student knows about the Course.\n";

    return 0;
}
