# Templates

- Templates are a powerfull tools for C++ that allows generic programming
- It consists in creating functions or classes with generic types (one or many type)
- The compiler will compile the created templates only if there are called by filling out the generic types with concrete types
- Compiler can sometimes perform deduction of the type during the template function / calls call, but it is better to always explicitly provide the type
- A template is compiled only when it is used by a caller object for specific type (a template class / function containing an error doesn't generate it unless it is called with given type)
