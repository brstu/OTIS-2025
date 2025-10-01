#include <iostream>
#include <cmath>

double linearModel(double y_current, double u_current, double a, double b) {
    return a * y_current + b * u_current;
}

double nonlinearModel(double y_current, double y_previous, double u_current, double u_previous, double a, double b, double c, double d) {
    return a * y_current - b * y_previous * y_previous + c * u_current + d * sin(u_previous);
}

int main() {
    setlocale(LC_ALL, "Russian");

    double a, b, c, d;
    double y0, u0;
    int n;

    std::cout << "Input constants a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    std::cout << "Input initial value of temperature y(0): ";
    std::cin >> y0;

    std::cout << "Input initial value of warmth u(0): ";
    std::cin >> u0;

    std::cout << "Input number of steps: ";
    std::cin >> n;

    double y_linear_current = y0;    
    double y_nonlinear_current = y0;   
    double u_current = u0;             

    double y_nonlinear_previous = y0; 
    double u_previous = u0;       

    std::cout << "Steps\tLinear model\tNonlinear model\n";

    for (int step = 1; step <= n; ++step) {
        std::cout << "Input the value of u for step " << step << ": ";
        std::cin >> u_current;
        double linear_result = linearModel(y_linear_current, u_current, a, b);
        double nonlinear_result = nonlinearModel(y_nonlinear_current, y_nonlinear_previous, u_current, u_previous, a, b, c, d);
        std::cout << step << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";
        y_linear_current = linear_result;
        y_nonlinear_previous = y_nonlinear_current; 
        y_nonlinear_current = nonlinear_result;   

        u_previous = u_current;
    }
    return 0;
}