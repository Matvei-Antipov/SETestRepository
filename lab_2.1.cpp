#define TEST_MODE
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Function to count the number of characters in different types
int countCharacters(const string& str) {
    return str.size();
}

int countCharacters(int number) {
    return countCharacters(to_string(number));
}

int countCharacters(double number) {
    string str;

    // Special case for zero
    if (number == 0.0) {
        str = "0.0";  // Ensure 0.0 is represented with 3 characters
    } else {
        // Handle negative numbers
        if (number < 0) {
            str = "-" + to_string(-number);  // Add minus and convert the absolute value to string
        } else {
            str = to_string(number);
        }

        // Remove unnecessary trailing zeros and the decimal point if not needed
        str = str.substr(0, str.find_last_not_of('0') + 1);
        
        // If the number is an integer (e.g., 123.), remove the decimal point
        if (str.back() == '.') {
            str = str.substr(0, str.size() - 1);
        }
    }

    return str.size();  // Return the size including minus and decimal point
}

int countCharacters(const char* str) {
    return countCharacters(string(str));
}

// Function to get validated double input
double getValidatedDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (true) {
        try {
            cin >> value;
            if (cin.fail()) {
                throw invalid_argument("Incorrect input! Please enter a number.");
            }
            return value;
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, try again: " << prompt;
        }
    }
}

// Function to enter X and N values
void EnterTheNumbers(double& x, double& n) {
    try {
        cout << string(30, '=') << endl;
        cout << "|        Enter The Numbers     |" << endl;
        cout << string(30, '=') << endl;

        x = getValidatedDoubleInput("Enter X: ");
        
        while (true) {
            n = getValidatedDoubleInput("Enter N (N should be greater than I and (N + 2) greater than J): ");
            if ((x >= 0 && (n <= 0.0 || (n + 2) <= 1.0)) || (x < 0 && n < 3)) {
                throw invalid_argument("Incorrect input! N should be greater than I and (N + 2) greater than J!");
            } else {
                break;
            }
        }
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        EnterTheNumbers(x, n);  // Recursive call to handle invalid input
    }
}

// Function to enter the range and step values
void EnterTheRange(double& a, double& b, double& step) {
    try {
        cout << string(30, '=') << endl;
        cout << "|        Enter The Range       |" << endl;
        cout << string(30, '=') << endl;

        a = getValidatedDoubleInput("Enter A (lower range): ");
        b = getValidatedDoubleInput("Enter B (upper range): ");
        step = getValidatedDoubleInput("Enter step: ");
        
        while (a > b || step <= 0) {
            throw invalid_argument("Incorrect input! B must be greater than A and step must be positive!");
        }
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        EnterTheRange(a, b, step);  // Recursive call to handle invalid input
    }
}

// Function to pick the algorithm type (Simple or Extended)
void PickTheAlgorithm(string& algo) {
    cout << "Do you want to use simple or extended algorithm? (S/e): ";
    while (true) {
        try {
            cin >> algo;
            if (cin.fail() || (algo != "S" && algo != "s" && algo != "E" && algo != "e")) {
                throw invalid_argument("Incorrect input! You must enter 'S'/'s' or 'E'/'e'!");
            } else {
                break;
            }
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, try again: ";
        }
    }
}

// Function to calculate Y for the simple algorithm
double calculateY(double x, int n) {
    double result = 0.0;
    double sol = 1.0;
    
    try {
        if (x >= 0) {
            for (int i = 0; i <= n; ++i) {
                sol = 1.0;
                for (int j = 1; j <= n + 2; ++j) {
                    sol *= pow((9 * i - j + pow(j, 3)), 2);
                }
                result += sol;
            }
            return result;
        } else {
            sol = 0;
            for (int i = 3; i <= n; ++i) {
                sol += 1.0 / (2.0 * i) + 1.0 / x;
            }
            return (x + 3) * sol;
        }
    } catch (...) {
        cerr << "An error occurred during calculation." << endl;
        return NAN;
    }
}

// Function to calculate extended Y with the range and step
void CalculateExtendedY(double n, double y, double a, double b, double step) {
    try {
        int maxXWidth = 0;
        int maxYWidth = 0;
        double x = a;

        for (; x <= b;) {
            y = calculateY(x, n);
            maxXWidth = max(maxXWidth, countCharacters(x));
            maxYWidth = max(maxYWidth, countCharacters(y));
            x = x + step;
        }

        x = a;
        int widthX = maxXWidth + 8;
        int widthY = maxYWidth + 10;

        cout << string(widthX + widthY + 3, '=') << endl;
        cout << "|" << setw(widthX) << "X" << "|" << setw(widthY) << "Y" << "|" << endl;
        cout << string(widthX + widthY + 3, '=') << endl;

        for (; x <= b;) {
            y = calculateY(x, n);
            cout << "|" << setw(widthX) << fixed << setprecision(2) << x << "|" << setw(widthY) << fixed << setprecision(2) << y << "|" << endl;
            cout << string(widthX + widthY + 3, '=') << endl;
            x = x + step;
        }
    } catch (...) {
        cerr << "An error occurred during extended calculation." << endl;
    }
}

#ifndef TEST_MODE
int main() {
    double x = NAN, n, a = NAN, b = NAN, step = NAN, y;
    string answer, algo;

    do {
        PickTheAlgorithm(algo);

        if (algo == "S" || algo == "s") {
            EnterTheNumbers(x, n);
            y = calculateY(x, n);

            int width = 25;
            cout << string(50 + countCharacters(y), '=') << endl;
            cout << "|" << setw(width) << "Solution is:" << setw(25 + countCharacters(y)) << "|" << endl;
            cout << string(50 + countCharacters(y), '=') << endl;
            cout << "|" << setw(width) << fixed << y << setw(25 + countCharacters(y)) << " |" << endl;
            cout << string(50 + countCharacters(y), '=') << endl;
        } else {
            EnterTheRange(a, b, step);
            CalculateExtendedY(n, y, a, b, step);
        }

        cout << "Do you want to run the program again? (yes/no): ";
        cin >> answer;

    } while (answer == "yes" || answer == "Yes");

    cout << string(30, '=') << endl;
    cout << "|         Goodbye!            |" << endl;
    cout << string(30, '=') << endl;

    return 0;
}
#endif