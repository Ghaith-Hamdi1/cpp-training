# Type conversion

- Type conversion is converting from one type to another
- Implicit conversion: when the compiler converts a type when a mismatch is detected
- Explicit conversion: mentioned explicitly in code

[Diagram — extracted labels: "Implicit conversion from int to double", "Explicit conversion from int to double using static_cast"]

## Implicit type conversion

- Programmer is responsible for casting
- Promotion conversion is allowed (from narrow type to wider type)
- Narrowing conversion is risky:
  - Loose precision (`double` to `float`)
  - Wrong value (such as `int` to `char`)

## Explicit type conversion: overview

- Force the conversion type
- C-Style cast (must not be used in modern C++)
- Using casting operators:
  - `static_cast`
  - `dynamic_cast`
  - `const_cast`
  - `reinterpret_cast`

## Explicit type conversion: static_cast

- Used to convert one type to another
- Conversion during compile time (more safe)

```cpp
int a = static_cast<int>('R');
```

## Explicit type conversion: dynamic_cast

- Used to convert a mother (base) class to child classes
- Will be seen later, after the object oriented module

```cpp
Child * a = dynamic_cast<Child*>(parent*);
```

## Explicit type conversion: const_cast

- Used to cast away constness of variables
- Used to change non-const class members inside a const member function
- Remove and modify constness of a pointer that points to a non-constant value

```cpp
T a = const_cast<T>(const T);
```

## Explicit type conversion: reinterpret_cast

- Used to convert a pointer of one type to another pointer of another type
- Compiler doesn't perform any check
- Be careful using it

```cpp
T* a = reinterpret_cast<T*>(U*);
```

## Reference example, `examples/01-cpp-basics/12-type-conversion/12_casting.cpp`

```cpp
#include <iostream>
int fun(int* ptr)
{
    *ptr = *ptr + 10;
    return (*ptr);
}

class A {
public:
    A(){};
    virtual ~A() = default;
};

class B : public A
{
public:
    B(){}
    virtual ~B() = default;
};

class C : public A
{
public:
    C(){}
    virtual ~C() = default;
};

int main(){
    int a = static_cast<int>('R');
    auto c = static_cast<char>(a);

    std::cout << "Static cast " << a << " " << c << std::endl;

    int val = 10;
    const int *ptr {&val};
    int *ptr1 = const_cast <int *>(ptr);
    fun(ptr1);
    std::cout << "Const cast " << val << std::endl;

    A * ab = new B;
    A * ac = new C;

    B * bb = dynamic_cast<B*>(ab);
    B * bc = dynamic_cast<B*>(ac);

    std::cout << "Dynamic cast bb is B " << (bb != nullptr) << " bc is B " << (bc != nullptr) << std::endl;
    delete ab;
    delete ac;

    int intVal[4]{0, 1, 2, 3};
    char * charPtr {nullptr};

    std::cout << "Reinterprete cast: " << std::endl;
    charPtr = reinterpret_cast<char*>(&intVal[0]);
    // according to endianess
    for (int i = 0; i < sizeof(intVal); i++){
        std::cout << "i =" << std::dec << i << std::hex << " -> 0x" << static_cast<int>(charPtr[i]) << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
```

---

