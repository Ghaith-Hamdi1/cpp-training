# Function template

- Function template: allows creating generic function. Make sure that the types to be applied satisfy the implementation of generic functions so that no compile error will be faced. For example, make sure that a member function of template type is existing. See example below:
  - Annotation on the example: *"U should have method `process()`"*
  - Annotation on the example: *"T should be the return of process function or compatible type"*
  - Function templates should always be defined in header files (".h") — *recovered from a character-interleaved fragment in the source text layer; see Conversion notes.*

  ```cpp
  // Representative example (examples/04-templates-and-design-patterns/01-templates/60_templates_functions.cpp)
  template<typename T, typename U>
  T function(const U& u)
  {
      std::cout << "Called template" << std::endl;
      T t;
      t = u.process();
      return t;
  }
  ```

- Function template: the template types can be used as function parameter, return type or simply in the function body
  - Return and parameters use the template type, we don't use "const T" because T may be const itself
  - Template type is used into the function implementation, the instantiation supposes that T has a constructor with an int as parameter
  - It is noted that the instantiation of template function is compile time operation

- Function template: template specialization means that we create a specialized version of function template for a specific type. It supposes then that the generic template exists and another one is created with same name and already specified type:
  - Annotation on the example: *"Template specialization is called when `function` is called with A type as parameter"*

  ```cpp
  // Function template specialization (examples/04-templates-and-design-patterns/01-templates/60_templates_functions.cpp)
  template<typename T, typename U>
  T function(const U& u)
  {
      std::cout << "Called template" << std::endl;
      T t;
      t = u.process();
      return t;
  }

  // template specialization for function
  template<>
  int function(const A& a)
  {
      std::cout << "Called template speicalization" << std::endl;
      return a.process2();
  }
  ```

- Function template: non-type template parameters: means that we can put a template parameter as non generic type, possible values:
  - Integral type (e.g. int, char, long, etc...)
  - Enumeration
  - Pointer or reference
