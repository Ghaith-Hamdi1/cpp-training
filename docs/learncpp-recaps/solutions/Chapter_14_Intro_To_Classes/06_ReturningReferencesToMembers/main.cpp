// Chapter 14 - Project 06: Returning References to Data Members
// ===============================================================
// Key concepts:
//   - Returning data members by CONST reference avoids expensive copies
//     (useful for strings, containers, etc.).
//   - Safe because the implicit object outlives the function call.
//
// Pitfalls:
//   - NEVER return a non-const reference to a private data member - it
//     defeats the purpose of making the member private.
//   - If the object is a temporary (rvalue), the returned reference
//     becomes DANGLING after the full expression ends.

#include <iostream>
#include <string>

class Student
{
public:
    Student(std::string_view name, int age)
        : m_name{name}, m_age{age}
    {
    }

    // GOOD: return by const reference - avoids copy, prevents modification
    const std::string &getName() const { return m_name; }

    int getAge() const { return m_age; }

    void print() const
    {
        std::cout << "Student { " << m_name << ", age " << m_age << " }\n";
    }

    // BAD EXAMPLE (commented out) - returning non-const reference to private member:
    // std::string& getNameBad() { return m_name; }
    // This would let ANYONE modify m_name, defeating data hiding:
    //   student.getNameBad() = "Hacked";  // compiles!

private:
    std::string m_name{};
    int m_age{};
};

// A factory function that returns a Student by value (a temporary)
Student createStudent()
{
    return Student{"Temporary Tim", 20};
}

int main()
{
    // --- Safe: named object outlives the reference ---
    Student alice{"Alice", 21};

    const std::string &nameRef = alice.getName(); // safe - alice is alive
    std::cout << "Name via reference: " << nameRef << '\n';
    alice.print();

    // --- DANGEROUS: reference to a member of a temporary ---
    // The temporary Student is destroyed at the end of the full expression.

    // BAD (commented out to avoid undefined behavior):
    // const std::string& danglingRef = createStudent().getName();
    //   ^ The temporary Student dies at the semicolon.
    //     'danglingRef' is now DANGLING - using it is undefined behavior.

    // SAFE: use the returned reference within the same expression
    std::cout << "Temp name (safe): " << createStudent().getName() << '\n';
    //   ^ Here getName() is used immediately in the same expression,
    //     so the temporary is still alive.

    // SAFE: copy the value out of the temporary
    std::string copiedName = createStudent().getName(); // copies the string
    std::cout << "Copied name: " << copiedName << '\n'; // safe - it's a copy

    std::cout << "\n-- Takeaway --\n"
              << "Return by const ref to avoid copies, but watch out for temporaries.\n"
              << "Never return a non-const ref to a private member.\n";

    return 0;
}
