# Class templates

- Class templates: like function templates, class templates define a type that will be applicable for the whole class (visible for all members variables and functions)
- Every class template called with a type represents a new type. For example, Test<A> has a different type from Test<B>.
- Template class should be declared and defined in header files as well
- [Diagram — two side-by-side code panels labeled "Declaration" and "Definition", shown as an image in the source and not text-extractable. Representative code below from `examples/04-templates-and-design-patterns/01-templates/61_templates_classes.cpp`:]

  ```cpp
  // Declaration
  template<typename T, typename U>
  class A
  {
  public:
      A(T& x);
      A(T&& x);
      virtual U process();
  protected:
      T m_x;
  };

  // Definition
  template<typename T, typename U>
  A<T, U>::A(T& x) : m_x(x)
  {
      std::cout << "Called A constructor with lvalue reference " << m_x << std::endl;
  }

  template<typename T, typename U>
  U A<T, U>::process()
  {
      return static_cast<U>(m_x);
  }
  ```

- Class templates: template specialization for particular type is possible for classes as well
  - The class has to be defined with specific type
  - [Diagram — code panel labeled "Specialization", shown as an image in the source. Representative code below from `examples/04-templates-and-design-patterns/01-templates/61_templates_classes.cpp`:]

  ```cpp
  template<>
  class A<char, char>
  {
  public:
      A(char& x) : m_x(x)
      {
          std::cout << "A template specialization char (& constructor)" << std::endl;
      }

      A(char&& x)
      {
          std::cout << "A template specialization char (&& constructor)" << std::endl;
      }

      virtual char process()
      {
          std::cout << "A template specialization char process" << std::endl;
          return 'X';
      }
  protected:
      char m_x;
  };
  ```

- Class templates: partial specialization means that we fix a type of class template for a well defined type and leave another one as template type
  - It has to be done for the totality of the class
  - If only one member function to be specialized, we may create a new class that inherit from specialized parent class
  - See example provided for demo

  ```cpp
  // Partial template specialization (examples/04-templates-and-design-patterns/01-templates/61_templates_classes.cpp)
  template<typename T>
  class DerivedA : public A<T, int>
  {
  public:
      DerivedA() : A<T, int>(0) {}
      int process()
      {
          std::cout << "DerivedA process function call" << std::endl;
          return 0;
      }
  };
  ```
