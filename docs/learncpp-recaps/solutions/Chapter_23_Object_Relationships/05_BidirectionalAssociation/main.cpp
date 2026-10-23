// Chapter 23 - Project 05: Bidirectional Association
// =====================================================
//
// In a bidirectional association, BOTH objects know about each other.
// Classic example: Doctor ↔ Patient.
//
// Challenges:
//   - Requires forward declarations to resolve circular type references.
//   - Must keep both sides in sync (add/remove on both ends).
//   - More complex and error-prone than unidirectional associations.
//
// Best practice: Avoid bidirectional associations when unidirectional
// will suffice - they add complexity and error potential.

#include <iostream>
#include <string>
#include <vector>

// Forward declaration needed because Doctor and Patient refer to each other
class Patient;

class Doctor
{
private:
    std::string m_name;
    std::vector<Patient *> m_patients;

public:
    Doctor(std::string_view name) : m_name{name} {}

    const std::string &getName() const { return m_name; }

    // Defined after Patient is fully declared (see below)
    void addPatient(Patient &patient);
    void printPatients() const;
};

class Patient
{
private:
    std::string m_name;
    std::vector<Doctor *> m_doctors;

public:
    Patient(std::string_view name) : m_name{name} {}

    const std::string &getName() const { return m_name; }

    void addDoctor(Doctor &doctor)
    {
        m_doctors.push_back(&doctor);
    }

    void printDoctors() const
    {
        std::cout << "Patient " << m_name << " sees:\n";
        for (const auto *d : m_doctors)
            std::cout << "  Dr. " << d->getName() << '\n';
    }
};

// Now Patient is fully defined, so we can implement Doctor's methods
void Doctor::addPatient(Patient &patient)
{
    m_patients.push_back(&patient);
    // Keep the bidirectional link in sync
    patient.addDoctor(*this);
}

void Doctor::printPatients() const
{
    std::cout << "Dr. " << m_name << "'s patients:\n";
    for (const auto *p : m_patients)
        std::cout << "  " << p->getName() << '\n';
}

int main()
{
    Doctor drSmith{"Smith"};
    Doctor drJones{"Jones"};

    Patient alice{"Alice"};
    Patient bob{"Bob"};
    Patient carol{"Carol"};

    // addPatient updates BOTH sides of the relationship
    drSmith.addPatient(alice);
    drSmith.addPatient(bob);
    drJones.addPatient(bob); // Bob sees two doctors
    drJones.addPatient(carol);

    std::cout << "=== Bidirectional Association: Doctor ↔ Patient ===\n\n";

    drSmith.printPatients();
    std::cout << '\n';
    drJones.printPatients();
    std::cout << '\n';

    alice.printDoctors();
    std::cout << '\n';
    bob.printDoctors(); // Bob should list both doctors
    std::cout << '\n';
    carol.printDoctors();

    std::cout << "\nKey point: When Dr. Smith adds Alice, Alice's doctor\n"
              << "list is also updated - keeping both sides in sync.\n";

    return 0;
}
