#include <iostream>
#include <functional>

int func(std::function<bool (int, float)> test_fn)
{
    if (test_fn(2, 2.0f) == true)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void myInvoke(const std::function<void()>& fn){
    fn();
}
auto sayHello(const std::string& hello) {
    // Capture name by reference and return the lambda.
    int i{0};
    auto lambda = [&]() {
        std::cout << "Say " << hello << i << '\n'; // Undefined behavior
    };
    lambda();
    i = 10;
    lambda();
    return lambda;
}

int main(){

    int a{0};
    float b{2.0f};

    std::cout << "First lambda call " << func([=](int x, float y) -> bool {
        if (x == a || y == b) {
            return true;
        }
        else {
            return false;
        }
    }) << std::endl;

    auto lambda = [&a, b] (int x, float y) -> bool {

        if (x == a || y == b) {
            a++; // a can be modified
            return true;
        }
        else {
            return false;
        }
    };

    std:: cout << "Second call " << func(lambda) << " new a value " << a << std::endl;

    

    int i{ 0 };
    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable {  
        std::cout << ++i << '\n'; 
    } };

    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));

    auto sayHelloRet{ sayHello("Hello") };

    // Call the lambda function that sayHello returned.
    sayHelloRet();

    return 0;
}

