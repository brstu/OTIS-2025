#include <iostream>
#include <cmath>
#include <limits> 
#include "LinearSystem.h"
#include "NonLinearSystem.h"
#include "Simulater.h"

using namespace std;


int main() {
    const int ITERATIONS = 10;
    double initialY1;

    cout << "Enter initial value y1 = ";

    while (!(cin >> initialY1)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    simulateSystem(initialY1, ITERATIONS);

    return 0;
}
