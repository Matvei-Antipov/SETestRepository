#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

int countCharacters(const string& str) {
    return str.size();
}

int countCharacters(int number) {
    return countCharacters(to_string(number));
}

int countCharacters(double number) {
    return countCharacters(to_string(number));
}

int countCharacters(const char* str) {
    return countCharacters(string(str));
}

double getValidatedDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (true) {
        try {
            cin >> value;
            if (cin.fail()) {
                throw invalid_argument("Incorrect input! Here must be a number!");
            }
            return value;
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, try again: " << prompt;
        }
    }
}

void EnterTheNumbers(double &x, double &n) {
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
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        EnterTheNumbers(x, n);
    }
}

void EnterTheN(double &n) {
    try {
        while (true) {
            n = getValidatedDoubleInput("Enter N: ");
            if (n < 3) {
                throw invalid_argument("Incorrect input! N should be greater than 3!");
            } else {
                break;
            }
        }
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        EnterTheN(n);
    }
}

void EnterTheRange(double &a, double &b, double &step) {
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
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        EnterTheRange(a, b, step);
    }
}

void PickTheAlgorithm(string &algo) {
    cout << "Do you want to use simple or extended algorithm? (S/e): ";
    while (true) {
        try {
            cin >> algo;
            if (cin.fail() || (algo != "S" && algo != "s" && algo != "E" && algo != "e")) {
                throw invalid_argument("Incorrect input! You must enter 'S'/'s' or 'E'/'e'!");
            } else {
                break;
            }
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, try again: ";
        }
    }
}

double calculateY(double x, int n) {
    double res = 0;
    double sol = 1.0;
    
    try {
        if (x >= 0) {
            for (int i = 0; i <= n; ++i) {
                sol = 1.0;
                for (int j = 1; j <= n + 2; ++j) {
                    sol *= pow((9 * i - j + pow(j, 3)), 2);
                }
                res += sol;
            }
            return res;
        } 
        else {
            sol = 0;
            for (int i = 3; i <= n; ++i) {
                sol += 1.0 / (2.0 * i) + 1.0 / x;
            }
            return (x + 3) * sol;
        }
    }
    catch (...) {
        cerr << "An error occurred during calculation." << endl;
        return NAN;
    }
}

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
    }
    catch (...) {
        cerr << "An error occurred during extended calculation." << endl;
    }
}

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
        } 
        else {
            EnterTheN(n);
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