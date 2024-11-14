#ifndef LAB_2_1_H
#define LAB_2_1_H

#include <iostream>
#include <string>

// Function Prototypes
// Function to calculate Y based on input x and n
double calculateY(double x, int n);

// Function to pick the algorithm choice between simple and extended
void PickTheAlgorithm(std::string& choice);

// Function to get validated double input with error handling
double getValidatedDoubleInput(const std::string& prompt);

// Function to input X and N values with validation
void EnterTheNumbers(double& x, double& n);

// Function to input range A, B, and step values with validation
void EnterTheRange(double& a, double& b, double& step);

// Function to calculate Y values in an extended range using step
double CalculateExtendedY(double a, double b, double c, double d, double e);

// Function to count the number of characters in a string
int countCharacters(const std::string& str);
int countCharacters(int number);
int countCharacters(double number);
int countCharacters(const char* str);

// Class to handle input redirection for testing purposes
class InputRedirect {
public:
    // Constructor that initializes with a string (simulating input)
    InputRedirect(const std::string& input_data) : data(input_data) {}

    // Delete copy constructor and copy assignment operator to prevent copying
    InputRedirect(const InputRedirect&) = delete;
    InputRedirect& operator=(const InputRedirect&) = delete;

    // Move constructor and move assignment operator
    InputRedirect(InputRedirect&&) noexcept = default;
    InputRedirect& operator=(InputRedirect&&) noexcept = default;

    // Method to retrieve the redirected input data
    std::string getData() const {
        return data;
    }

private:
    // Internal storage for the simulated input data
    std::string data;
};

#endif // LAB_2_1_H