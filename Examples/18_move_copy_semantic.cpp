#include <iostream>
#include <string>

class Copy {
private:
    // Declaring the raw pointer as
    // the data member of the class
    int* data;
 
public:
    // Constructor
    Copy(int d)
    {
        // Declare object in the heap
        data = new int;
        *data = d;
 
        std::cout << "Copy Constructor is called for "
             << d << std::endl;
    };
 
    // Copy Constructor to delegated
    // Copy constructor
    Copy(const Copy& source)
        : Copy{ *source.data }
    {
 
        // Copying constructor copying
        // the data by making deep copy
        std::cout << "Copy Copy Constructor is called - "
             << "Deep copy for "
             << *source.data
             << std::endl;
    }
 
    // Destructor
    ~Copy()
    {
        if (data != nullptr)
 
            // If the pointer is not
            // pointing to nullptr
            std::cout << "Copy Destructor is called for "
                 << *data << std::endl;
        else
 
            // If the pointer is
            // pointing to nullptr
            std::cout << "Copy Destructor is called"
                 << " for nullptr"
                 << std::endl;
 
        // Free the memory assigned to
        // data member of the object
        delete data;
    }
};

class Move {
private:
    // Declare the raw pointer as
    // the data member of class
    int* data;
 
public:
   
    // Constructor
    Move(int d)
    {
        // Declare object in the heap
        data = new int;
        *data = d;
        std::cout << "Move Constructor is called for "
             << d << std::endl;
    };
 
    // Copy Constructor
    Move(const Move& source)
        : Move{ *source.data }
    {
 
        // Copying the data by making
        // deep copy
        std::cout << "Move Copy Constructor is called -"
             << "Deep copy for "
             << *source.data
             << std::endl;
    }
 
    // Move Constructor
    Move(Move&& source)
        : data{ source.data }
    {
 
        std::cout << "Move Move Constructor for "
             << *source.data << std::endl;
        source.data = nullptr;
    }
 
    // Destructor
    ~Move()
    {
        if (data != nullptr)
 
            // If pointer is not pointing
            // to nullptr
            std::cout << "Move Destructor is called for "
                 << *data << std::endl;
        else
 
            // If pointer is pointing
            // to nullptr
            std::cout << "Move Destructor is called"
                 << " for nullptr "
                 << std::endl;
 
        // Free up the memory assigned to
        // The data member of the object
        delete data;
    }
};

void testMove1( Move& a)
{
    Move mv{std::move(a)};
}

void testMove2(Move&& a)
{
    Move mv{a};
}

void testCopy1(Copy&& a)
{
    Copy mv{std::move(a)};
}

void testCopy2(Copy&& a)
{
    Copy mv{a};
}

int main()
{
    Move mv(0);
    testMove1(mv);
    testMove2(Move(0));

    testCopy1(Copy(0));
    testCopy2(Copy(0));
    // -> std::move is just a cast, we have to implement the
    // move semantics behind

    return 0;
}