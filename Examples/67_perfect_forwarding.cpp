#include <iostream>
#include <string>
#include <utility>
#include <type_traits>

template <typename T, typename ... Args,
        std::enable_if_t<!std::is_constructible<T, int>::value /*&&
                         !std::is_constructible<T, double>::value*/, bool> = true>
T create(Args&& ... args){
  return T(std::forward<Args>(args)...);
}

// int compatible with double
template <typename T, typename ... Args,
        std::enable_if_t<std::is_constructible<T, int>::value /*||
                         std::is_constructible<T, double>::value*/, bool> = true>
T create(Args&& ... args){
  std::cout << "Int/double constructor" << std::endl;
  return T(2.2);
}

struct MyStruct{
  MyStruct(int i, double d, std::string s){
    std::cout << "MyStruct parameters " << i << " " 
                << d << " " << s << std::endl;
  }
};

struct DoubleStruct
{
    DoubleStruct(int n) {
        std::cout << "N=" << n << std::endl;
    }
};


int main(){
    // Lvalues
    int five=5;
    int myFive= create<int>(five);
    std::cout << "myFive: "  << myFive << std::endl;

    std::string str{"Lvalue"};
    std::string str2= create<std::string>(str);
    std::cout << "str2: " << str2 << std::endl;

    // Rvalues
    int myFive2= create<int>(5);
    std::cout << "myFive2: " << myFive2 << std::endl;

    std::string str3= create<std::string>(std::string("Rvalue"));
    std::cout << "str3: " << str3 << std::endl;

    std::string str4= create<std::string>(std::move(str3));
    std::cout << "str4: " << str4 << std::endl;

    // Arbitrary number of arguments
    double doub= create<double>();
    std::cout << "doub: " << doub << std::endl;
    float fl= create<float>();
    std::cout << "float: " << fl << std::endl;
    DoubleStruct doublestr = create<DoubleStruct>(6);

    MyStruct myStr= create<MyStruct>(2011,3.14,str4);
    
    return 0;
}