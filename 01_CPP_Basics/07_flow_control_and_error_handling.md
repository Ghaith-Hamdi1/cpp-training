# Flow control and error handling

## Conditional statement: "if"

```cpp
if (boolean_condition) {
    // true_statement(s)
} else {
    // false_statement(s)
}
```

## Conditional statement: "switch"

```cpp
switch (value) {
    case value1:
        // processing here if value equals value1
        break; (return;)
    case value2:
        // processing here if value equals value2
        break; (return;)
    default:
        // default processing here
        break; (return;)
}
```

[Diagram — extracted labels: "equals" / "value1", "equals" / "value2" — a flowchart showing the value being compared against `value1` and `value2` in turn]

## Conditional statement: "conditional operator"

```cpp
condition ? true_statement : false_statement;
```

## Looping statement: "while"

```cpp
while (boolean_condition) {
    // code to be repeated
    [break;]
    [continue;]
}
```

- "boolean_condition" must be true to enter the loop

## Looping statement: "do .. while"

```cpp
do {
    // code to be repeated
    [break;]
    [continue;]
} while (boolean_condition);
```

- "boolean_condition" can be not true to enter the loop (the body always runs at least once)

## Looping statement: "for"

```cpp
for (init_statement; boolean_condition; expression) {
    // code to be repeated
    [break;]
    [continue;]
}
```

- "init_statement" is executed before entering the loop
- "boolean_condition" must be [true] to enter the loop
- "expression" is executed each time after the code to be repeated

## Reference example: conditionals and loops

`Examples/01_CPP_Basics/07_flow_control_and_error_handling/04_conditional_statements.cpp`:

```cpp
#include <iostream>

int main()
{
    int i{0};
    int j{0};

    // switch statement
    switch (i) {
        case 0:
        case 2:
            std::cout << "Switch: i eqauls " << i << std::endl;
            break;
        case 1:
            std::cout << "Switch: i eqauls 1" << std::endl;
            break;
        case 3:
        default:
            std::cout << "Switch: i different from 0, 1 and 2 and maybe equal to 3" << std::endl;
            break;
    }

    // if / else statement
    if (i != 0) {
        std::cout << "If: i different from 0" << std::endl;
    }
    else if (j != 0) {
        std::cout << "If: j equals 0" << std::endl;
    }
    else {
        std::cout << "If: all conditions are false" << std::endl;
    }

    // conditional operator
    i == 0 ? (std::cout << "i equals 0" << std::endl) : (std::cout << "i different from 0" << std::endl);

    return 0;
}
```

`Examples/01_CPP_Basics/07_flow_control_and_error_handling/05_looping_statements.cpp`:

```cpp
#include <iostream>

int main()
{
    int i{0};

    // while loop
    while (i == 0) {
        std::cout << "While loop" << std::endl;
        i = 1;
    }

    // do .. while
    do {
        std::cout << "Do .. While loop" << std::endl;
    }
    while (i == 0);

    // for loop
    for (i = 0; i < 10; i = i + 2) {
        std::cout << "For loop with counter " << i << std::endl;
    }

    std::cout << "For loop exited, counter value is " << i << std::endl;

    return 0;
}
```

## Exercise

- Write a function that displays the elements of a vector in separate lines using `std::cout`, and use lambdas to multiply elements at even index by 2 and elements at odd index by 3. Use the same processing with `for`, `do..while` and `while`.

```cpp
std::vector<int> vect{3, 40, 10, 56, 2, 4};
int vect[]{3, 40, 10, 56, 2, 4};
```

## Error handling strategies

- Handle error within the function
- Return error to the caller
- Throw Exception
- Halt the program

Reference example, `Examples/01_CPP_Basics/07_flow_control_and_error_handling/07_error_handling.cpp`:

```cpp
#include <iostream>
#include <cassert>
#include <exception>

void manageWithinFunction()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation) {
        case '+':
        case '-':
        case '*':
        case '/':
            std::cout << "Bravo, this is a good input" << std::endl;
            return; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cerr << "Oops, that input is invalid.  Please try again." << std::endl;
        }
    } // and try again
}

int returnToCaller(int input)
{
    // test if input is valid
    if (input < 0)
    {
        // we may log the error as well
        std::cerr << "We cannot accept negative value" << std::endl;
        return 1;
    }

    std::cout << "Processing is done with positive value" << std::endl;

    return 0; // return success
}

int main() {
    // manage within function
    manageWithinFunction();

    int ret{0};
    int input{-3};
    ret = returnToCaller(input);
    if (ret == 1) {
        // action to be performed by caller
    }
    else if (ret == 0) { // success
        // action on success
    }

    return 0;
}
```

## Assertion

- Used to verify a condition that is essential to program workflow
- Used at runtime
- If condition is not true, program will terminate

## Static assertion

- Used to verify a condition
- Used at compile time
- If condition is not true, compilation error

---

