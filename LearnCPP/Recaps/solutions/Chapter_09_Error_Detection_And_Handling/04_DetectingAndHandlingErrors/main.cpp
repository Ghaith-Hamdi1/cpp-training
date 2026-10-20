// Project 04 - Detecting and Handling Errors
// Chapter 9: Error Detection and Handling
//
// Four strategies for handling errors inside functions:
//   1. Handle the error in the function itself (retry / ignore)
//   2. Pass the error back to the caller (return code / sentinel value)
//   3. Halt the program for fatal errors (std::exit / std::abort)
//   4. Throw an exception (covered later in Chapter 27)
//
// Also shows:
//   - std::cerr for diagnostic output (unbuffered, goes to stderr)
//   - Sentinel values (e.g., returning -1 to signal failure)

#include <cstdlib> // std::exit, EXIT_FAILURE
#include <iostream>
#include <string>

// ============================================================================
// Strategy 1 - Handle the error inside the function
// ============================================================================

// Divides a by b. If b is 0, prints a warning and returns 0.0.
// The function handles the error internally - the caller doesn't need to check.
double safeDivide(double a, double b)
{
    if (b == 0.0)
    {
        // Use std::cerr for error/diagnostic messages (unbuffered, goes to stderr).
        std::cerr << "  [Warning] safeDivide: division by zero, returning 0.0\n";
        return 0.0;
    }
    return a / b;
}

// ============================================================================
// Strategy 2 - Pass the error back to the caller via a sentinel value
// ============================================================================

// Finds the index of 'target' in 'arr'. Returns -1 (sentinel) if not found.
// The caller must check for the sentinel before using the result.
int findIndex(const int *arr, int size, int target)
{
    for (int i{0}; i < size; ++i)
    {
        if (arr[i] == target)
            return i;
    }
    return -1; // Sentinel value: "not found"
}

// ============================================================================
// Strategy 2b - Pass the error back via a bool out-parameter
// ============================================================================

// Parses a simple positive integer from a string.
// Returns the parsed value; sets 'success' to false on failure.
int parsePositiveInt(const std::string &str, bool &success)
{
    if (str.empty())
    {
        success = false;
        return 0;
    }

    int result{0};
    for (char ch : str)
    {
        if (ch < '0' || ch > '9') // Non-digit found
        {
            success = false;
            return 0;
        }
        result = result * 10 + (ch - '0');
    }

    success = true;
    return result;
}

// ============================================================================
// Strategy 3 - Halt the program on fatal errors
// ============================================================================

// Initializes a critical subsystem. If it fails, the program cannot continue.
void initSubsystem(bool simulate_failure)
{
    if (simulate_failure)
    {
        std::cerr << "  [Fatal] initSubsystem: critical failure. Terminating.\n";
        // std::exit(EXIT_FAILURE);  // Would terminate - commented out for demo
        std::cout << "  (In a real program, std::exit(EXIT_FAILURE) would run here.)\n";
        return;
    }
    std::cout << "  Subsystem initialized successfully.\n";
}

// ============================================================================
// Main
// ============================================================================

int main()
{
    std::cout << "=== Detecting and Handling Errors Demo ===\n\n";

    // --- Strategy 1: handle internally ---
    std::cout << "Strategy 1 - Handle error inside the function:\n";
    std::cout << "  10 / 3 = " << safeDivide(10.0, 3.0) << '\n';
    std::cout << "  10 / 0 = " << safeDivide(10.0, 0.0) << '\n';
    std::cout << '\n';

    // --- Strategy 2: sentinel value ---
    std::cout << "Strategy 2 - Sentinel value (-1 = not found):\n";
    int data[]{10, 20, 30, 40, 50};
    int idx1{findIndex(data, 5, 30)};
    int idx2{findIndex(data, 5, 99)};
    std::cout << "  findIndex(30) = " << idx1 << (idx1 == -1 ? " (not found)" : " (found)") << '\n';
    std::cout << "  findIndex(99) = " << idx2 << (idx2 == -1 ? " (not found)" : " (found)") << '\n';
    std::cout << '\n';

    // --- Strategy 2b: bool out-parameter ---
    std::cout << "Strategy 2b - Bool out-parameter:\n";
    bool ok{};
    int val1{parsePositiveInt("123", ok)};
    std::cout << "  parsePositiveInt(\"123\") = " << val1 << ", success = " << std::boolalpha << ok << '\n';

    int val2{parsePositiveInt("12x", ok)};
    std::cout << "  parsePositiveInt(\"12x\") = " << val2 << ", success = " << ok << '\n';

    int val3{parsePositiveInt("", ok)};
    std::cout << "  parsePositiveInt(\"\")    = " << val3 << ", success = " << ok << '\n';
    std::cout << '\n';

    // --- Strategy 3: halt on fatal error ---
    std::cout << "Strategy 3 - Halt on fatal error:\n";
    initSubsystem(false); // Success
    initSubsystem(true);  // Simulated failure
    std::cout << '\n';

    std::cout << "Key takeaway: Use std::cout for user output, std::cerr for errors.\n";
    return 0;
}
