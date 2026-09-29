# Friend functions and classes

- Friend function is a function that can access even private members
  - It can be either a normal function or another class member function
- Multiple friends:
  - A function or a member function can be a friend to multiple classes
- Friend classes: same friend concept, but a friend class can access any private member at any part of the class

```cpp
// Examples/02_CPP_OOP/07_friend_functions_and_classes/20_friend.cpp
#include <iostream>

class Storage; // forward declaration for class Storage
class Screen;

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayItem(const Storage& storage); // forward declaration above needed for this declaration line

    void printToScreen(Screen& screen);
};

class Screen
{
private:
    int m_id;
public:
    Screen(int id) : m_id{id} {}
    friend class Display;
};

class Storage // full definition of Storage class
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayItem member function a friend of the Storage class (requires seeing the full definition of class Display, as above)
	friend void Display::displayItem(const Storage& storage);
};

// Now we can define Display::displayItem, which needs to have seen the full definition of class Storage
void Display::displayItem(const Storage& storage)
{
	if (m_displayIntFirst)
		std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
	else // display double first
		std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}

void Display::printToScreen(Screen& screen)
{
    std::cout << "Test acccess " << screen.m_id << std::endl;
}

int main()
{
    Storage storage(5, 6.7);
    Display display(false);

    display.displayItem(storage);

    return 0;
}
```
