#include <iostream>


const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

const int* pcGetNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return &s_x; // and return a reference to it
}

int* pGetNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return &s_x; // and return a reference to it
}

int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    /********** Return by reference *********/
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << "Correct handling " << id1 << id2 << std::endl; // displays 22

    const int id3 { getNextId() }; // id3 is not a reference, will make a copy
    const int id4 { getNextId() }; // id4 is not a reference, will make a copy

    std::cout << "Wrong handling " << id3 << id4 << std::endl; // displays 34

    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7
    std::cout << "New b value " << b << std::endl;

    int& c = max(a, b);
    c = 8;
    std::cout << "New b value " << b << std::endl;

    /********** Return by address *********/
    int * ptr = pGetNextId();
    const int *cptr = pcGetNextId();

    std::cout << "Return by address " << *ptr << " " << *cptr << std::endl; // displays 1 1

    return 0;
}