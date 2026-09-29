# Special methods

- C++ class define many special methods types:
  - Constructor
  - Destructor
  - Copy constructor
  - Move constructor
- Adding keywords "default" or "delete" in front of constructors (optionally) will either use default constructor implementation or delete that constructor
- Constructor: special method called automatically when object is instantiated
  - Must have same name as class name
  - Typically used to initialize member variables of the class to appropriate user-provided values, or to do any setup steps necessary for the class to be used
  - Two types of constructors:
    - Default
    - User defined
- Constructor
  - Default constructor: "default" keyword to indicate to compiler to use default implementation
  - User defined constructor: attributes initialization
  - If no constructor is defined, default constructor is created implicitly
- Constructor: constructor initialization list
  - [Code annotation: assigning a value in the constructor body is not an initialization, but assignment]
- Constructor: constructor initialization list
  - Default parameter value, should be always at the end of parameters
  - Can have many default parameters, but should be always kept at the end
  - Initialization list: initialise attributes ',' separated
  - Make sure to keep order of declaration within the initialization list
- Constructor: call of constructor
  - Default constructor (without parameters)
  - Call of corresponding defined constructor
  - May have as many constructors as needed (with different signature)
  - If a custom constructor is defined, default constructor can no longer be called unless defined
- Constructor: call of constructor
  - Class D has composition of both classes B and C
  - [Diagram — extracted labels, execution result order: "C default constructor" → "B constructor 1" → "D constructor"]
- Constructor: call of constructor
  - Different ways to call constructor

```cpp
// Examples/02_CPP_OOP/04_special_methods/17_constructors_destructors.cpp
#include <iostream>
#include <string>
#include <vector>

class A 
{
public:
    A();
    A(int x, int y = 1);
    A(const A& a);
    A(A&& a);
    virtual ~A();

    void setId(const std::string& id);

    std::string getId() const;    
private:
    std::string id;
};

class B
{
public:
    B(int x);
};

B::B(int x)
{
    std::cout << "B constructor " << x << std::endl;
}

class C
{
public:
    C();
};

C::C()
{
    std::cout << "C default constructor" << std::endl;
}


class D
{
public:
    D();
private:
    C c;
    B b;
};

D::D() : b(1)
{
    std::cout << "D default constructor" << std::endl;
}

A::A() : id("")
{
    std::cout << "A Default constructor" << std::endl;
}

A::A(int x, int y) : id{std::to_string(x)}
{
    std::cout << "A Constructor with int parameters " << x << ", " << y << std::endl;
}

A::A(const A& a) : id{ a.id }
{
    // have to define the copy processing
    std::cout << "A Copy constructor " << a.id << std::endl;
}

A::A(A&& a)
{
    // have to define the move processing
    std::cout << "A Move constructor " << a.id << std::endl;
    this->id = std::move(a.id);
}

A::~A() 
{
    std::cout << "A destructor called" << std::endl;
}

void A::setId(const std::string& id)
{
    this->id = id;
}

std::string A::getId() const 
{
    return id;
}

struct STR
{
    int a;
    int b;
    float c;
};

int main()
{

    // STR str(1, 2, 3.0f); // error no corresponding constructor
    STR str{1, 2, 3.0f}; // correct, init list
    std::cout << "STR members " << str.a << ", " << str.b << ", " << str.c << std::endl;

    A a1;
    a1.setId(std::string("a10"));
    std::cout << "a1 " << a1.getId() << std::endl;
    A a2 = a1;
    std::cout << "a2 " << a2.getId() << std::endl;

    A a3{a1};
    std::cout << "a3 " << a3.getId() << std::endl;

    A a4(std::move(a1));
    std::cout << "a4 " << a4.getId() << std::endl;
    
    a4.setId("a4");

    A a5{1, 2};
    A a6{5};

    A a7 = std::move(a6);
    a6.setId("30");
    std::cout << "After move " << a6.getId() << std::endl;

    std::string s1{"Test"};
    std::string s2{std::move(s1)};
    // move well managed s1 is invalid after move
    std::cout << "Move string " << s2 << " old string " << s1 << std::endl;
    
    // instantiation order of attributes checking
    D d;

    return 0;
}
```

- Copy Constructor: called during instantiation by copy or assigning an object to another
  - Declaration: `class_name(const class_name& rhs);`
  - If not defined, default copy constructor will be created implicitly (automatically copy all members values from class being copied, if no other constructors are defined)
  - If defined, initialization of members has to be done in the copy constructor definition
- Copy Constructor:
  - [Code annotation: the copy constructor is not called in one case shown (compiler elides/deletes the call of copy constructor), and is called in another case shown]
  - Can prevent copying an object by deleting copy constructor or declaring it as private
- Move Constructor: move ownership of the resources from one object to another (which is typically much less expensive than making a copy)
  - Declaration: `class_name(class_name&& rhs);`
  - If not defined, default move constructor will be created implicitly (automatically copy all members values from class being copied, if no other constructors are defined)
  - If defined, initialization of members has to be done in the move constructor definition
- Move Constructor:
  - [Code annotation: "The default constructor is called here" / "The move constructor is called here"]
  - Can prevent moving an object by deleting move constructor or declaring it as private

```cpp
// Examples/02_CPP_OOP/04_special_methods/18_move_copy_semantic.cpp
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
```

- Move semantic: `std::move` is a standard library function that casts (using `static_cast`) its argument into an r-value reference, so that move semantics can be invoked.
  - [Diagram — extracted labels: "3 copies (expensive in time and memory)" vs "3 moves (less expensive in time and memory)"]
- Move semantic: moved object are no longer valid (or in undefined state)
  - To avoid any issues: Moved objects shall be set to default / zero state and shall not be used
  - The value of moved-from objects will have an undefined value (may keep its value or have another arbitrary value)
- Destructor: special method called just before object is destructed
  - Destructor should be always virtual (will be explained later)
  - Should never throw exceptions
  - `virtual ~class_name();`
  - [Code annotation: "Destructor for pointer is called here" / "Destructor for object is called here"]
- RAII (Resource Acquisition Is Initialization)
  - It is a C++ programming technique to
    - Guarantees that the resource is available to any function that may access the object
    - Guarantees that all resources are released when the lifetime of their controlling object ends, in reverse order of acquisition
  - It means that the object resource is allocated in the constructor and freed in the destructor
  - Then, the resource can be used when object is alive
- Current object pointer "this"
  - It is pointing to the object being operated on
  - Each object has its own "this" pointer
- Current object pointer "this": chaining member functions
  - Return a reference to current object instance
  - Use it for another call with object instance updated
- Implicit and explicit constructor call
