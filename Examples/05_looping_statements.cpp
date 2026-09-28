#include <iostream>

int main()
{
    int i{0};
    
    // while loop
    while (i == 0) {
        std::cout << "While loop" << std::endl;
        i = 1;
    }

    // do .. while
    do {
        std::cout << "Do .. While loop" << std::endl;
    }
    while (i == 0);

    // for loop
    for (i = 0; i < 10; i = i + 2) {
        std::cout << "For loop with counter " << i << std::endl;
    }
        
    std::cout << "For loop exited, counter value is " << i << std::endl;

    return 0;
}