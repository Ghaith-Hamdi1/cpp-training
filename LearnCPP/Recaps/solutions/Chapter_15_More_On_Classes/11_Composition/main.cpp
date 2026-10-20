// Chapter 15 - Project 11: Composition (Classes Containing Classes)
// ==================================================================
//
// Composition models a "has-a" relationship: one class contains objects
// of another class as data members.
//
// Examples:
//   - A Car HAS an Engine and Wheels
//   - A Computer HAS a CPU, RAM, and Storage
//   - A Person HAS a Name and an Address
//
// Key principles:
//   - The contained objects' lifetimes are managed by the container.
//   - Constructors initialize sub-objects via the member initializer list.
//   - Destructors are called in reverse order of construction.
//   - Composition enables code reuse without inheritance.

#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------
// Sub-component: Address
// -------------------------------------------------------
class Address
{
private:
    std::string m_street{};
    std::string m_city{};
    std::string m_country{};

public:
    Address(const std::string &street, const std::string &city, const std::string &country)
        : m_street{street}, m_city{city}, m_country{country}
    {
    }

    void print() const
    {
        std::cout << m_street << ", " << m_city << ", " << m_country;
    }

    const std::string &getCity() const { return m_city; }
};

// -------------------------------------------------------
// Sub-component: ContactInfo
// -------------------------------------------------------
class ContactInfo
{
private:
    std::string m_email{};
    std::string m_phone{};

public:
    ContactInfo(const std::string &email, const std::string &phone)
        : m_email{email}, m_phone{phone}
    {
    }

    void print() const
    {
        std::cout << "Email: " << m_email << ", Phone: " << m_phone;
    }
};

// -------------------------------------------------------
// Composite class: Person (HAS-A Address and ContactInfo)
// -------------------------------------------------------
class Person
{
private:
    std::string m_name{};
    int m_age{};
    Address m_address;     // Composition: Person HAS-A Address
    ContactInfo m_contact; // Composition: Person HAS-A ContactInfo

public:
    Person(const std::string &name, int age,
           const Address &address, const ContactInfo &contact)
        : m_name{name}, m_age{age}, m_address{address} // Initialize sub-object
          ,
          m_contact{contact} // Initialize sub-object
    {
    }

    void print() const
    {
        std::cout << "Person: " << m_name << " (age " << m_age << ")\n";
        std::cout << "  Address: ";
        m_address.print(); // Delegate to sub-object
        std::cout << '\n';
        std::cout << "  Contact: ";
        m_contact.print(); // Delegate to sub-object
        std::cout << '\n';
    }

    const std::string &getName() const { return m_name; }
    const Address &getAddress() const { return m_address; }
};

// -------------------------------------------------------
// Another composite: Computer
// -------------------------------------------------------
class CPU
{
private:
    std::string m_model{};
    int m_cores{};

public:
    CPU(const std::string &model, int cores)
        : m_model{model}, m_cores{cores}
    {
    }

    void print() const
    {
        std::cout << m_model << " (" << m_cores << " cores)";
    }
};

class RAM
{
private:
    int m_sizeGB{};

public:
    RAM(int sizeGB) : m_sizeGB{sizeGB} {}

    void print() const
    {
        std::cout << m_sizeGB << " GB";
    }
};

class Computer
{
private:
    std::string m_brand{};
    CPU m_cpu;
    RAM m_ram;

public:
    Computer(const std::string &brand, const CPU &cpu, const RAM &ram)
        : m_brand{brand}, m_cpu{cpu}, m_ram{ram}
    {
    }

    void print() const
    {
        std::cout << m_brand << " Computer\n";
        std::cout << "  CPU: ";
        m_cpu.print();
        std::cout << "\n  RAM: ";
        m_ram.print();
        std::cout << '\n';
    }
};

// -------------------------------------------------------
// Composition with collections
// -------------------------------------------------------
class Team
{
private:
    std::string m_teamName{};
    std::vector<Person> m_members{}; // A Team HAS many Persons

public:
    Team(const std::string &name) : m_teamName{name} {}

    void addMember(const Person &p)
    {
        m_members.push_back(p);
    }

    void printRoster() const
    {
        std::cout << "Team: " << m_teamName
                  << " (" << m_members.size() << " members)\n";
        for (const auto &member : m_members)
        {
            std::cout << "  - " << member.getName()
                      << " (" << member.getAddress().getCity() << ")\n";
        }
    }
};

int main()
{
    // --- Person composed of Address + ContactInfo ---
    std::cout << "=== Composition: Person ===\n";
    Address addr{"123 Main St", "Springfield", "USA"};
    ContactInfo contact{"alice@example.com", "555-1234"};
    Person alice{"Alice", 30, addr, contact};
    alice.print();

    // --- Computer composed of CPU + RAM ---
    std::cout << "\n=== Composition: Computer ===\n";
    CPU cpu{"Ryzen 9 7950X", 16};
    RAM ram{64};
    Computer pc{"Custom", cpu, ram};
    pc.print();

    // --- Team composed of multiple Persons ---
    std::cout << "\n=== Composition: Team ===\n";
    Person bob{"Bob", 25,
               Address{"456 Oak Ave", "Denver", "USA"},
               ContactInfo{"bob@example.com", "555-5678"}};
    Person carol{"Carol", 28,
                 Address{"789 Pine Rd", "Seattle", "USA"},
                 ContactInfo{"carol@example.com", "555-9012"}};

    Team devTeam{"Engineering"};
    devTeam.addMember(alice);
    devTeam.addMember(bob);
    devTeam.addMember(carol);
    devTeam.printRoster();

    return 0;
}
