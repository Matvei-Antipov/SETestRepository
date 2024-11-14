#define TEST_MODE
#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <limits>
#include "lab_2.1.h" // Replace with the correct header file if necessary

#define ASSERT_EQUAL(actual, expected) \
    do { \
        if ((actual) != (expected)) { \
            std::cerr << "Assertion failed: " << #actual << " == " << #expected \
                      << " (actual: " << (actual) << ", expected: " << (expected) << ")\n"; \
            assert(false); \
        } \
    } while (false)

#define ASSERT_NEAR(actual, expected, tolerance) \
    do { \
        if (std::abs((actual) - (expected)) > (tolerance)) { \
            std::cerr << "Assertion failed: " << #actual << " ≈ " << #expected \
                      << " (actual: " << (actual) << ", expected: " << (expected) \
                      << ", tolerance: " << (tolerance) << ")\n"; \
            assert(false); \
        } \
    } while (false)

// Test countCharacters for strings
void testCountCharacters() {
    ASSERT_EQUAL(countCharacters("hello"), 5);  // Normal string
    ASSERT_EQUAL(countCharacters(""), 0);       // Empty string
    ASSERT_EQUAL(countCharacters("12345"), 5);  // Numeric string
}

// Test countCharacters for integers
void testCountCharactersInt() {
    ASSERT_EQUAL(countCharacters(12345), 5);  // Normal integer
    ASSERT_EQUAL(countCharacters(0), 1);      // Single digit integer
    ASSERT_EQUAL(countCharacters(-98765), 6); // Negative integer
}

// Test countCharacters for doubles
void testCountCharactersDouble() {
    ASSERT_EQUAL(countCharacters(123.456), 7); // Standard double
    ASSERT_EQUAL(countCharacters(0.0), 3);     // Zero as a double
    ASSERT_EQUAL(countCharacters(-123.0), 4);  // Negative double without trailing zeros
    ASSERT_EQUAL(countCharacters(123.000), 3); // Double with trailing zeros (should be trimmed)
}

// Test for getValidatedDoubleInput (mocking user input)
void testGetValidatedDoubleInput() {
    std::string input_data = "42.5\n";  // Simulated user input
    std::istringstream input_stream(input_data);
    std::cin.rdbuf(input_stream.rdbuf());

    double result = getValidatedDoubleInput("Enter a number: ");
    ASSERT_NEAR(result, 42.5, 0.01);  // Check the returned value
}

// Test EnterTheNumbers (mocking user input)
void testEnterTheNumbers() {
    double x, n;
    std::string input_data = "5\n3\n";  // Valid inputs
    std::istringstream input_stream(input_data);
    std::cin.rdbuf(input_stream.rdbuf());

    EnterTheNumbers(x, n);
    ASSERT_EQUAL(x, 5.0);  // Check if the correct X is entered
    ASSERT_EQUAL(n, 3.0);  // Check if the correct N is entered
}

// Test EnterTheRange (mocking user input)
void testEnterTheRange() {
    double a, b, step;
    std::string input_data = "1\n10\n1\n";  // Valid inputs
    std::istringstream input_stream(input_data);
    std::cin.rdbuf(input_stream.rdbuf());

    EnterTheRange(a, b, step);
    ASSERT_EQUAL(a, 1.0);  // Check if A is correct
    ASSERT_EQUAL(b, 10.0); // Check if B is correct
    ASSERT_EQUAL(step, 1.0); // Check if step is correct
}

// Test PickTheAlgorithm (mocking user input)
void testPickTheAlgorithm() {
    std::string algo;
    std::string input_data = "S\n";  // Valid input for simple algorithm
    std::istringstream input_stream(input_data);
    std::cin.rdbuf(input_stream.rdbuf());

    PickTheAlgorithm(algo);
    ASSERT_EQUAL(algo, "S");  // Check if the correct algorithm is picked
}

// Test calculateY function
void testCalculateY() {
    ASSERT_NEAR(calculateY(2.0, 3), 3.77445e+17, 1e+14);  // Check simple calculation
    ASSERT_NEAR(calculateY(-1.0, 3), -1.66667, 0.01);          // Check negative x handling
}

// Main function to execute all tests
int main() {
    testCountCharacters();
    testCountCharactersInt();
    testCountCharactersDouble();
    testGetValidatedDoubleInput();
    testEnterTheNumbers();
    testEnterTheRange();
    testPickTheAlgorithm();
    testCalculateY();

    std::cout << "\n\nAll tests passed successfully!" << std::endl;
    return 0;
}