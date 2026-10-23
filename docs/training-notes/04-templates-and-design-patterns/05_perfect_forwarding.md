# Perfect forwarding

- "Forwarding" is the process where one function forwards its parameter to another function
- When it is perfect, the function should receive the same object passed from the function that does the forwarding i.e. perfect forwarding means we do not just forward objects, we also forward their salient properties, whether they are lvalues or rvalues, const or volatile.
- The perfect forwarding is to be considered in template programming
- Let's see the problem of forwarding in relation with templates in steps...

- Consider the following: the compile error is due to `a` is an lvalue reference so it won't [garbled text in source, could not fully recover — see Conversion notes] **Possible solutions:**
  - Add const to `Arg`, but `a` then cannot be changed anymore in the function
  - Overload by adding a new version with const lvalue reference

- Now it compiles successfully, the solution works !
- However, if we have more parameters, we have to create more and more overloads ... (not so good)
- Also, we cannot move the parameter const reference even it accepts a rvalue at function call
- The solution is to use the "universal reference" for template argument

- "Universal reference" encodes information about the lvalueness and rvalueness of the arguments that are passed to them. Let's see example:
- We use `std::forward` to acheive the perfect forwarding
- It keeps the property of passed argument (rvalue or lvalue)

```cpp
// Perfect forwarding with universal references and std::forward (examples/course/04-templates-and-design-patterns/05-perfect-forwarding/67_perfect_forwarding.cpp)
template <typename T, typename ... Args,
        std::enable_if_t<!std::is_constructible<T, int>::value, bool> = true>
T create(Args&& ... args){
  return T(std::forward<Args>(args)...);
}

// int compatible with double
template <typename T, typename ... Args,
        std::enable_if_t<std::is_constructible<T, int>::value, bool> = true>
T create(Args&& ... args){
  std::cout << "Int/double constructor" << std::endl;
  return T(2.2);
}

int main(){
    // Lvalue
    int five=5;
    int myFive= create<int>(five);

    // Rvalue
    std::string str3= create<std::string>(std::string("Rvalue"));
    std::string str4= create<std::string>(std::move(str3));
    return 0;
}
```

- Extention to variadic templates:
  - It allows having a generic function that accepts all types of parameters even user defined types
