# Back to Exceptions

(Slides 80–81)

- `std::exception` is the base class defined in the standard library to manage exceptions. Many derived exceptions are used, for example:
  - `std::logic_error`
    - `std::invalid_argument`
    - `std::out_of_range`
    - ....
  - `std::runtime_error`
    - `std::range_error`
    - `std::overflow_error`
    - ...
- Other standard exceptions are defined and can be used, please refer to documentation
- Otherwise, the user can define their own exception by creating a new class inheriting from `std::exception` and overriding the `what()` function to provide their own exception message

*(No dedicated Module 3 example file maps to this section specifically; exception handling/custom exceptions are covered by the Module 1 examples `examples/01-cpp-basics/07-flow-control-and-error-handling/07_error_handling.cpp`, `examples/01-cpp-basics/08-exceptions/08_exceptions.cpp` and `examples/01-cpp-basics/08-exceptions/11_stack_unwinding.cpp` — outside the scope of this module 3 deck.)*

---

