#include <iostream>

int main()
{
    int i{0};
    int j{0};
    
    // switch statement
    switch (i) {
        case 0:
        case 2:
            std::cout << "Switch: i eqauls " << i << std::endl;
            break;
        case 1:
            std::cout << "Switch: i eqauls 1" << std::endl;
            break;
        case 3:
        default:
            std::cout << "Switch: i different from 0, 1 and 2 and maybe equal to 3" << std::endl;
            break;
    }

    // if / else statement
    if (i != 0) {
        std::cout << "If: i different from 0" << std::endl;
    }
    else if (j != 0) {
        std::cout << "If: j equals 0" << std::endl;
    }
    else {
        std::cout << "If: all conditions are false" << std::endl;
    }

    // conditional operator
    i == 0 ? (std::cout << "i equals 0" << std::endl) : (std::cout << "i different from 0" << std::endl);

    return 0;
}