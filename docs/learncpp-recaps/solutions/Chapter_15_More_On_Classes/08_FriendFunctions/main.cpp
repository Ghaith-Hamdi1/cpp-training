// Chapter 15 - Project 08: Friend Non-Member Functions
// =====================================================
//
// A `friend` declaration inside a class grants a NON-MEMBER function
// full access to the class's private and protected members.
//
// Key rules:
//   - Friendship is always granted BY the class being accessed,
//     never requested by the outsider.
//   - A friend function defined inside the class body remains a
//     non-member function (it does not become a member).
//   - Prefer using the class's public interface inside friend
//     functions when possible.
//   - Prefer non-friend functions over friend functions when
//     the public interface is sufficient.

#include <iostream>
#include <string>

// -------------------------------------------------------
// Example 1: Friend function for printing private data
// -------------------------------------------------------
class Temperature
{
private:
    double m_celsius{};

public:
    Temperature(double celsius) : m_celsius{celsius} {}

    // Declare `printTemp` as a friend - it can access m_celsius directly.
    friend void printTemp(const Temperature &t);

    // Also declare operator<< as a friend for convenient output.
    friend std::ostream &operator<<(std::ostream &out, const Temperature &t);
};

// Friend function definition - not a member of Temperature, but has access.
void printTemp(const Temperature &t)
{
    // Direct access to private member m_celsius:
    std::cout << t.m_celsius << " °C ("
              << (t.m_celsius * 9.0 / 5.0 + 32.0) << " °F)\n";
}

// Friend operator<< - enables `std::cout << temp;`
std::ostream &operator<<(std::ostream &out, const Temperature &t)
{
    out << t.m_celsius << "°C";
    return out;
}

// -------------------------------------------------------
// Example 2: Friend function that accesses two different classes
// -------------------------------------------------------
class Humidity; // Forward declaration

class Weather
{
private:
    double m_tempC{};

public:
    Weather(double tempC) : m_tempC{tempC} {}

    // Friend function that needs access to both Weather and Humidity
    friend void printWeatherReport(const Weather &w, const Humidity &h);
};

class Humidity
{
private:
    double m_percentRH{};

public:
    Humidity(double rh) : m_percentRH{rh} {}

    // Same friend function - must be declared in BOTH classes
    friend void printWeatherReport(const Weather &w, const Humidity &h);
};

void printWeatherReport(const Weather &w, const Humidity &h)
{
    // Has access to private members of BOTH classes:
    std::cout << "Weather Report: "
              << w.m_tempC << "°C, "
              << h.m_percentRH << "% relative humidity\n";
}

// -------------------------------------------------------
// Example 3: Friend function defined INSIDE the class body
// -------------------------------------------------------
class Secret
{
private:
    std::string m_secret{"I love C++"};

public:
    // Friend defined inside the class body.
    // It is STILL a non-member function, despite being defined here.
    friend void reveal(const Secret &s)
    {
        std::cout << "The secret is: \"" << s.m_secret << "\"\n";
    }
};

int main()
{
    // --- Example 1: Friend function ---
    Temperature boiling{100.0};
    printTemp(boiling);
    std::cout << "Using operator<<: " << boiling << '\n';

    // --- Example 2: Friend accessing two classes ---
    Weather w{22.5};
    Humidity h{65.0};
    printWeatherReport(w, h);

    // --- Example 3: Friend defined inside the class ---
    Secret s{};
    reveal(s); // Free function, not s.reveal()

    return 0;
}
