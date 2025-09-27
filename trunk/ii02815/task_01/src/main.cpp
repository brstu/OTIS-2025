#include <iostream>
#include <cmath>
using namespace std;

double linearModel(double y_current, double u_current, double a, double b) {
    return a * y_current + b * u_current;
}

double nonlinearModel(double y_current, double y_previous, double u_current, double u_previous, double a, double b, double c, double d) {
    return a * y_current - b * y_previous * y_previous + c * u_current + d * sin(u_previous);
}

int main() {
    setlocale(LC_ALL, "RU");

    double a, b, c, d;
    double y0, u0;
    int n;

    cout << "Введите константы a, b, c, d: ";
    cin >> a >> b >> c >> d;

    cout << "Введите начальное значение температуры y(0): ";
    cin >> y0;

    cout << "Введите начальное значение теплоты u(0): ";
    cin >> u0;

    cout << "Введите число шагов: ";
    cin >> n;

    double y_linear_current = y0;    
    double y_nonlinear_current = y0;   
    double u_current = u0;             

    double y_nonlinear_previous = y0; 
    double u_previous = u0;       

    cout << "Шаги\tЛинейная модель\tНелинейная модель\n";

    for (int step = 1; step <= n; ++step) {
        double linear_result = linearModel(y_linear_current, u_current, a, b);
        double nonlinear_result = nonlinearModel(y_nonlinear_current, y_nonlinear_previous, u_current, u_previous, a, b, c, d);

        cout << step << "\t" << linear_result << "\t\t" << nonlinear_result << "\n";

 
        y_linear_current = linear_result;
        y_nonlinear_previous = y_nonlinear_current; 
        y_nonlinear_current = nonlinear_result;   

        u_previous = u_current;

    }
    return 0;
}
