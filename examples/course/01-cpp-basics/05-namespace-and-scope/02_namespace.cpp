#include <iostream>

namespace test {
    int i{5};

    void fn() {
        std::cout << "Test namespace";
    }
} // namespace test 


// int main() {
//     std::cout << "Before assigning new value " << test::i << std::endl;

//     test::i = 10;

//     std::cout << "After assigning new value " << test::i << std::endl;
// }

void fn(){
    std::cout << "Global namespace";
}

using namespace test;

int main() {
    std::cout << "Before assigning new value " << i << std::endl;

    i = 10;

    std::cout << "After assigning new value " << i << std::endl;

    test::i = 20;

    std::cout << "After assigning new value with explicit namespace " << i << std::endl;
    int i{6};

    std::cout << "After assigning new value " << i << std::endl;
    std::cout << "After assigning new value " << test::i << std::endl;

    test::fn();
    ::fn();
    return 0;
}