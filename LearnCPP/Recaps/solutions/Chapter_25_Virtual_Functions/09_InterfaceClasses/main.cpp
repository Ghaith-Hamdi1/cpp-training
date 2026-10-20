// Chapter 25 - Project 09: Interface Classes
// =============================================
// An INTERFACE CLASS is a class that:
//   1. Has NO member variables.
//   2. Has ONLY pure virtual functions (plus a virtual destructor).
//
// It defines a CONTRACT that derived classes must implement.
// This is C++'s equivalent of Java/C# interfaces.
//
// Best practice: always give interface classes a virtual destructor
// (either defaulted or pure virtual with a body).

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ========== Interface: ISerializable ==========
// Any class implementing this can be converted to/from a string.
class ISerializable
{
public:
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string &data) = 0;
    virtual ~ISerializable() = default; // virtual destructor!
};

// ========== Interface: IPrintable ==========
// Any class implementing this can print itself to an ostream.
class IPrintable
{
public:
    virtual void print(std::ostream &out) const = 0;
    virtual ~IPrintable() = default;
};

// Helper: operator<< delegates to IPrintable::print().
std::ostream &operator<<(std::ostream &out, const IPrintable &obj)
{
    obj.print(out);
    return out;
}

// ========== Concrete class implementing BOTH interfaces ==========
class UserProfile : public ISerializable, public IPrintable
{
    std::string m_name;
    int m_age{};

public:
    UserProfile() = default;
    UserProfile(std::string_view name, int age)
        : m_name{name}, m_age{age} {}

    // ISerializable implementation
    std::string serialize() const override
    {
        return m_name + "," + std::to_string(m_age);
    }

    void deserialize(const std::string &data) override
    {
        auto pos = data.find(',');
        if (pos != std::string::npos)
        {
            m_name = data.substr(0, pos);
            m_age = std::stoi(data.substr(pos + 1));
        }
    }

    // IPrintable implementation
    void print(std::ostream &out) const override
    {
        out << "UserProfile{name=\"" << m_name << "\", age=" << m_age << "}";
    }
};

// ========== Another concrete class implementing IPrintable ==========
class LogEntry : public IPrintable
{
    std::string m_message;

public:
    explicit LogEntry(std::string_view msg) : m_message{msg} {}

    void print(std::ostream &out) const override
    {
        out << "[LOG] " << m_message;
    }
};

// ---------- Functions that work with interfaces ----------
void saveAll(const std::vector<const ISerializable *> &items)
{
    std::cout << "Serialized data:\n";
    for (const auto *item : items)
        std::cout << "  " << item->serialize() << '\n';
}

void printAll(const std::vector<const IPrintable *> &items)
{
    std::cout << "Printed items:\n";
    for (const auto *item : items)
        std::cout << "  " << *item << '\n';
}

// ---------- main ----------
int main()
{
    UserProfile alice{"Alice", 30};
    UserProfile bob{"Bob", 25};
    LogEntry log1{"Server started"};
    LogEntry log2{"Connection received"};

    std::cout << "=== Interface classes ===\n\n";

    // Use ISerializable interface
    std::vector<const ISerializable *> serializables = {&alice, &bob};
    saveAll(serializables);

    // Use IPrintable interface (UserProfile + LogEntry both implement it)
    std::cout << '\n';
    std::vector<const IPrintable *> printables = {&alice, &bob, &log1, &log2};
    printAll(printables);

    // Demonstrate deserialization round-trip
    std::cout << "\n=== Deserialization round-trip ===\n";
    UserProfile restored;
    restored.deserialize(alice.serialize());
    std::cout << "Restored: " << restored << '\n';

    std::cout << "\nInterface classes define contracts with no data - only pure virtuals.\n";

    return 0;
}
