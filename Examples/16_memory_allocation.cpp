#include <iostream>

int main()
{
    int *ptr = new int[10];
    for (int i = 0; i < 10; i++)
    {
        *ptr++ = i; // set content and increment, see operator associativity table
    }


    for (int i = 0; i < 10; i++)
    {
        std::cout << "Ptr[" << 10 - 1 - i << "]" << *--ptr << std::endl; // decrement ptr and get its contents, see operator associativity table
    }

    delete[] ptr;

    return 0;
}