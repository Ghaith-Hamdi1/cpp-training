#include <iostream>
#include <exception>
#include <string>

int main() {

    for (int i = 0; i < 5; i++) {
        try
        {
            // Statements that may throw exceptions you want to handle here
            switch (i)
            {
            case 0:
                throw 1;
            case 1:
            {
                double a{1.0};
                throw a;
            }
            case 2:
                throw std::string("Exception text");
            case 3:
                throw std::runtime_error("Runtime error special exception");
            case 4:
                throw 'a';
            default:
                break;
            }
        }
        catch (int x)
        {
            // Any exceptions of type exception_simple_type1 thrown within the above try block
            std::cerr << "We caught an int exception with value: " << x << std::endl;
        }
        catch (double) // no variable name since we don't use the exception itself in the catch block below
        {
            // Any exceptions of type double thrown within the above try block 
            std::cerr << "We caught an exception of type double" << std::endl;
        }
        catch (const std::string&) // catch classes by const reference
        {
            // Any exceptions of type class_name thrown within the above try block
            std::cerr << "We caught an exception of type std::string" << std::endl;
        }
        catch (const std::runtime_error& name) // catch classes by const reference
        {
            // Any exceptions of type class_name2 thrown within the above try block
            std::cerr << "We caught an exception of type runtime_error " << name.what() << std::endl;
        }
        catch (...)
        {
            // Any exceptions of a type not in the list
            std::cerr << "We caught an exception of non handled type" << std::endl;
        }
    }

    return 0;
}