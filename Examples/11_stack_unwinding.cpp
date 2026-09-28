#include <iostream>

void D() // called by C()
{
    std::cout << "Start D" << std::endl;
    std::cout << "D throwing int exception" << std::endl;

    throw - 1;

    std::cout << "End D" << std::endl; // skipped over
}

void C() // called by B()
{
    std::cout << "Start C" << std::endl;
    D();
    std::cout << "End C" << std::endl;
}

void B() // called by A()
{
    std::cout << "Start B" << std::endl;

    try
    {
        C();
    }
    catch (double) // not caught: exception type mismatch
    {
        std::cerr << "B caught double exception" << std::endl;
    }

    try
    {
    }
    catch (int) // not caught: exception not thrown within try
    {
        std::cerr << "B caught int exception" << std::endl;
    }

    std::cout << "End B" << std::endl;
}

void A() // called by main()
{
    std::cout << "Start A" << std::endl;

    try
    {
        B();
    }
    catch (int) // exception caught here and handled
                // can change int by char and see that stack is unwound
    {
        std::cerr << "A caught int exception" << std::endl;
    }

    std::cout << "End A" << std::endl;
}

int main()
{
    std::cout << "Start main" << std::endl;

    try
    {
        A();
    }
    catch (int) // not called because exception was handled by A
                // can change int by char and see that stack is unwound
    {
        std::cerr << "main caught int exception" << std::endl;
    }
    std::cout << "End main" << std::endl;

    return 0;
}