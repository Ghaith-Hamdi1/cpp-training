// Chapter 23 - Project 01: Composition ("part-of")
// ===================================================
//
// Composition is the strongest form of object relationship.
// Key properties:
//   1. The part can belong to only ONE object (whole) at a time.
//   2. The whole manages the lifetime of the part (creates/destroys it).
//   3. The part does not know about the whole (unidirectional).
//
// Implementation: Normal member variables (value semantics) or
// pointers where the class handles allocation and deallocation.
//
// Best practice: Favor composition over aggregation - it is simpler,
// safer, and self-cleaning.

#include <iostream>
#include <string>

// ---------------------------------------------------------------
// Example 1: Value-member composition
// A Heart is a part-of a Creature. The Creature creates and
// destroys the Heart automatically.
// ---------------------------------------------------------------
class Heart
{
private:
    double m_beatsPerMinute{};

public:
    Heart(double bpm = 72.0) : m_beatsPerMinute{bpm}
    {
        std::cout << "  Heart created (BPM: " << m_beatsPerMinute << ")\n";
    }

    ~Heart()
    {
        std::cout << "  Heart destroyed\n";
    }

    double getBPM() const { return m_beatsPerMinute; }
};

class Creature
{
private:
    std::string m_name;
    Heart m_heart; // Composition: Creature owns the Heart

public:
    Creature(std::string_view name, double bpm = 72.0)
        : m_name{name}, m_heart{bpm}
    {
        std::cout << "Creature \"" << m_name << "\" created\n";
    }

    ~Creature()
    {
        std::cout << "Creature \"" << m_name << "\" destroyed\n";
        // m_heart is automatically destroyed here - composition!
    }

    void printInfo() const
    {
        std::cout << m_name << " has a heart beating at "
                  << m_heart.getBPM() << " BPM\n";
    }
};

// ---------------------------------------------------------------
// Example 2: Pointer-member composition
// An Engine is dynamically allocated, but the Car still owns it
// and manages its lifetime (new/delete in constructor/destructor).
// ---------------------------------------------------------------
class Engine
{
private:
    int m_horsepower{};

public:
    Engine(int hp) : m_horsepower{hp}
    {
        std::cout << "  Engine created (" << m_horsepower << " HP)\n";
    }

    ~Engine()
    {
        std::cout << "  Engine destroyed\n";
    }

    int getHP() const { return m_horsepower; }
};

class Car
{
private:
    std::string m_model;
    Engine *m_engine{}; // Pointer-based composition - Car still owns Engine

public:
    Car(std::string_view model, int hp)
        : m_model{model}, m_engine{new Engine{hp}}
    {
        std::cout << "Car \"" << m_model << "\" created\n";
    }

    ~Car()
    {
        std::cout << "Car \"" << m_model << "\" destroyed\n";
        delete m_engine; // Car is responsible for cleanup
    }

    // Disable copy to keep ownership clear (Rule of Three)
    Car(const Car &) = delete;
    Car &operator=(const Car &) = delete;

    void printInfo() const
    {
        std::cout << m_model << " has a " << m_engine->getHP() << " HP engine\n";
    }
};

int main()
{
    std::cout << "=== Value-member composition ===\n";
    {
        Creature dog{"Rex", 100.0};
        dog.printInfo();
    } // Rex and its Heart are destroyed here
    std::cout << '\n';

    std::cout << "=== Pointer-member composition ===\n";
    {
        Car car{"Mustang", 450};
        car.printInfo();
    } // Car and its Engine are destroyed here

    return 0;
}
