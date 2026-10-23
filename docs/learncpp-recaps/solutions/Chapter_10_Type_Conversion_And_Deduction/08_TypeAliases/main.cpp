// Chapter 10 - Project 08: Type Aliases (using) and Typedef
//
// Type aliases create a new NAME for an existing type.
// Modern C++ syntax:  using NewName = ExistingType;
// Older syntax:       typedef ExistingType NewName;
//
// Use cases:
//   1. Platform-independent coding (e.g., using int32_t = int;)
//   2. Simplifying complex types
//   3. Documenting the purpose of a type (e.g., using StudentId = int;)
//
// IMPORTANT: Aliases are NOT new distinct types! The compiler treats them
// as interchangeable with the original type. They provide NO type safety.
//
// BEST PRACTICE:
//   - Prefer 'using' over 'typedef'
//   - Name aliases starting with a capital letter
//   - Don't overuse aliases - they can obscure code if overdone

#include <iostream>
#include <string>
#include <vector>

// =============================================================
// 1. Basic type aliases with 'using'
// =============================================================
using Distance = double;  // Alias for double, represents a distance
using StudentId = int;    // Alias for int, represents a student ID
using Name = std::string; // Alias for std::string

// =============================================================
// 2. Old-style typedef (prefer 'using' in modern C++)
// =============================================================
typedef int Score;          // Same as: using Score = int;
typedef double Temperature; // Same as: using Temperature = double;

// =============================================================
// 3. Simplifying complex types
// =============================================================
using StringList = std::vector<std::string>;
// Without alias, you'd write std::vector<std::string> everywhere

// =============================================================
// 4. Functions using aliases for documentation
// =============================================================
Distance calculateDistance(Distance speed, double time)
{
    return speed * time;
}

void printStudent(StudentId id, const Name &name, Score score)
{
    std::cout << "  Student " << id << ": " << name
              << " (score: " << score << ")\n";
}

int main()
{
    // Using the aliases
    std::cout << "=== Using type aliases ===\n";

    Distance d{calculateDistance(60.0, 2.5)};
    std::cout << "  Distance: " << d << " units\n";

    StudentId id{12345};
    Name studentName{"Alice"};
    Score studentScore{95};
    printStudent(id, studentName, studentScore);

    // =============================================================
    // 5. Simplifying complex types
    // =============================================================
    std::cout << "\n=== Aliases simplify complex types ===\n";

    StringList names{"Alice", "Bob", "Charlie"};
    std::cout << "  Names: ";
    for (const auto &name : names)
        std::cout << name << ' ';
    std::cout << '\n';

    // =============================================================
    // 6. PITFALL: Aliases are NOT new distinct types
    // =============================================================
    std::cout << "\n=== Aliases are NOT type-safe ===\n";

    using Miles = long;
    using Speed = long;

    Miles distance{100};
    Speed velocity{60};

    // This compiles without complaint! Miles and Speed are both just 'long'.
    // No type safety - you can freely mix them.
    distance = velocity; // Oops! Assigning speed to distance - no error!
    std::cout << "  Miles = Speed compiles fine (both are 'long'): "
              << distance << '\n';
    std::cout << "  Aliases do NOT create distinct types.\n";

    // =============================================================
    // 7. 'using' vs 'typedef' syntax comparison
    // =============================================================
    std::cout << "\n=== 'using' vs 'typedef' ===\n";

    // using is clearer, especially for complex types:
    // using FuncPtr = int(*)(double, double);     // Easy to read
    // typedef int(*FuncPtr)(double, double);       // Harder to read

    std::cout << "  Prefer 'using' over 'typedef' for readability.\n";
    std::cout << "  'typedef' is legacy syntax kept for compatibility.\n";

    return 0;
}
