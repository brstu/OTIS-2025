#include <iostream>
#include <cmath>
#include <vector>

class TempSimulator {
    double coefA, coefB, coefC, coefD;
    double prevY, prevPrevY, prevU;

public:
    TempSimulator(double a, double b, double c, double d, double startTemp)
        : coefA(a), coefB(b), coefC(c), coefD(d), 
          prevY(startTemp), prevPrevY(startTemp), prevU(0) {}

    double computeLinear(double u) {
        prevY = coefA * prevY + coefB * u;
        return prevY;
    }

    double computeNonLinear(double u) {
        double result = coefA * prevY - coefB * prevPrevY * prevPrevY 
                      + coefC * u + coefD * std::sin(prevU);
        prevPrevY = prevY;
        prevY = result;
        prevU = u;
        return result;
#include <array>

using namespace std;

class TemperatureModel {
private:
    double a;
    double b;
    double c; 
    double d;
    double y_prev;
    double y_prev2;
    double u_prev{0};

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val, double Y0) 
        : a(a_val), b(b_val), c(c_val), d(d_val), y_prev(Y0), y_prev2(Y0)
{
}

    double linear_step(double u) {
        double y = a * y_prev + b * u;
        y_prev = y;
        return y;
    }

    double nonlinear_step(double u) {
        double y = a * y_prev - b * y_prev2 * y_prev2 + c * u + d * sin(u_prev);
        y_prev2 = y_prev;
        y_prev = y;
        u_prev = u;
        return y;
    }
};

int main() {
    const double A = 0.8, B_LIN = 0.3, B_NLIN = 0.01;
    const double C = 0.4, D = 0.1, START_TEMP = 20.0;
    
    std::vector<double> inputs = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    
    TempSimulator linSim(A, B_LIN, 0, 0, START_TEMP);
    TempSimulator nlinSim(A, B_NLIN, C, D, START_TEMP);
    
    std::cout << "Step\tLinear\tNonLinear\n";
    
    for (size_t i = 0; i < inputs.size(); ++i) {
        double lin = linSim.computeLinear(inputs[i]);
        double nlin = nlinSim.computeNonLinear(inputs[i]);
        std::cout << i << "\t" << lin << "\t" << nlin << "\n";
    }
    
    return 0;
}
