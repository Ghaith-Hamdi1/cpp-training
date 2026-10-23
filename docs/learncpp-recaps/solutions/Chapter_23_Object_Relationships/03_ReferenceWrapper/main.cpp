// Chapter 23 - Project 03: std::reference_wrapper
// ==================================================
//
// std::vector (and other standard containers) cannot store raw
// references because references are not assignable/copyable in
// the way containers require.
//
// std::reference_wrapper<T> (from <functional>) solves this:
//   - It wraps a reference into a copyable, assignable object.
//   - Use .get() or implicit conversion to access the underlying object.
//   - std::ref() / std::cref() are convenience helpers to create them.
//
// This is essential for aggregation when you want to store
// references (not pointers) in standard containers.

#include <functional> // std::reference_wrapper, std::ref, std::cref
#include <iostream>
#include <string>
#include <vector>

class Student
{
private:
    std::string m_name;
    int m_grade{};

public:
    Student(std::string_view name, int grade)
        : m_name{name}, m_grade{grade}
    {
    }

    const std::string &getName() const { return m_name; }
    int getGrade() const { return m_grade; }
    void setGrade(int grade) { m_grade = grade; }
};

// A Classroom holds references to students (aggregation).
// Uses std::reference_wrapper so we can store them in a vector.
class Classroom
{
private:
    std::string m_room;
    std::vector<std::reference_wrapper<Student>> m_students;

public:
    Classroom(std::string_view room) : m_room{room} {}

    void addStudent(Student &student)
    {
        m_students.push_back(std::ref(student));
    }

    void printRoll() const
    {
        std::cout << "Classroom " << m_room << ":\n";
        for (const auto &sRef : m_students)
        {
            // .get() returns the underlying Student&
            const Student &s = sRef.get();
            std::cout << "  " << s.getName() << " - Grade: " << s.getGrade() << '\n';
        }
    }

    // Demonstrate that modifying via the wrapper modifies the original
    void boostAllGrades(int bonus)
    {
        for (auto &sRef : m_students)
        {
            Student &s = sRef.get();
            s.setGrade(s.getGrade() + bonus);
        }
    }
};

int main()
{
    Student alice{"Alice", 85};
    Student bob{"Bob", 72};
    Student carol{"Carol", 91};

    Classroom room101{"101"};
    room101.addStudent(alice);
    room101.addStudent(bob);
    room101.addStudent(carol);

    std::cout << "=== Before grade boost ===\n";
    room101.printRoll();

    // Boost grades through the classroom (modifies originals!)
    room101.boostAllGrades(5);

    std::cout << "\n=== After +5 grade boost via Classroom ===\n";
    room101.printRoll();

    // Verify the original objects were modified
    std::cout << "\nDirect check: Alice's grade = " << alice.getGrade() << '\n';
    std::cout << "(Proves std::reference_wrapper refers to the original object)\n";

    // -----------------------------------------------------------------
    // Quick demo: std::ref vs std::cref
    // -----------------------------------------------------------------
    std::cout << "\n=== std::ref / std::cref demo ===\n";

    std::vector<std::reference_wrapper<const Student>> constRefs;
    constRefs.push_back(std::cref(alice)); // const reference
    constRefs.push_back(std::cref(bob));

    for (const auto &cr : constRefs)
    {
        std::cout << cr.get().getName() << '\n'; // read-only access
    }

    return 0;
}
