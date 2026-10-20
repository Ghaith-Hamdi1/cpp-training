// Chapter 14 - Project 05: Encapsulation and Data Hiding
// ========================================================
// Key concepts:
//   - Encapsulation = making data members private, exposing a public interface.
//   - Separates WHAT users can do (the public API) from HOW it's implemented.
//   - Benefits:
//       1. Reduces complexity for users (they only see the interface).
//       2. Enforces class invariants (data is always valid).
//       3. Allows error detection inside setters.
//       4. Implementation can change without breaking user code.
//       5. Simplifies debugging (only member functions touch data).
//   - Prefer meaningful behaviors (e.g., kill()) over generic setters
//     (e.g., setAlive(false)).
//   - Only expose getters/setters when the public genuinely needs them.

#include <iostream>
#include <string>

class Player
{
public:
    Player(std::string_view name, int maxHP)
        : m_name{name}, m_maxHP{maxHP}, m_currentHP{maxHP} // start at full health
    {
    }

    // --- Meaningful behaviors instead of raw setters ---

    void takeDamage(int amount)
    {
        if (amount <= 0)
            return; // invariant: damage must be positive
        m_currentHP -= amount;
        if (m_currentHP < 0)
            m_currentHP = 0; // invariant: HP >= 0
        std::cout << m_name << " takes " << amount
                  << " damage! HP: " << m_currentHP << "/" << m_maxHP << '\n';
    }

    void heal(int amount)
    {
        if (amount <= 0)
            return;
        if (!isAlive())
        {
            std::cout << m_name << " is dead and cannot be healed.\n";
            return;
        }
        m_currentHP += amount;
        if (m_currentHP > m_maxHP)
            m_currentHP = m_maxHP; // invariant: HP <= maxHP
        std::cout << m_name << " heals " << amount
                  << " HP! HP: " << m_currentHP << "/" << m_maxHP << '\n';
    }

    // Meaningful behavior: kill() is clearer than setAlive(false)
    void kill()
    {
        m_currentHP = 0;
        std::cout << m_name << " has been slain!\n";
    }

    // --- Getters - only ones the public genuinely needs ---

    bool isAlive() const { return m_currentHP > 0; }
    std::string_view getName() const { return m_name; }
    int getHP() const { return m_currentHP; }

    // Note: there is NO setHP() - we force users to use takeDamage() and heal(),
    // which enforce our invariants.

    void print() const
    {
        std::cout << m_name << " [HP: " << m_currentHP << "/" << m_maxHP
                  << (isAlive() ? " ALIVE" : " DEAD") << "]\n";
    }

private:
    std::string m_name{};
    int m_maxHP{};
    int m_currentHP{};
};

int main()
{
    Player hero{"Warrior", 100};
    hero.print();

    // Users interact through meaningful behaviors - NOT raw data access
    hero.takeDamage(30);
    hero.heal(15);
    hero.takeDamage(200); // HP clamps to 0 - invariant enforced
    hero.heal(50);        // dead players can't heal - invariant enforced

    hero.print();

    // If implementation changes (e.g., adding armor, resistances),
    // the public interface stays the same - user code doesn't break.

    std::cout << "\n-- Takeaway --\n"
              << "Prefer meaningful behaviors (takeDamage, heal, kill)\n"
              << "over raw setters (setHP, setAlive). This enforces invariants.\n";

    return 0;
}
