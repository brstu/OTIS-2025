#include <iostream>
#include <iomanip>
#include "model.h"  // ВАЖНО: двойные кавычки, не угловые скобки!

using namespace std;

int main() {
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;
    double y0 = 23.0;

    double u[] = {10, 15, 20, 25, 30, 25, 20, 15, 10, 5};
    int steps = 10;

    cout << "Model Comparison:" << endl;
    cout << "Time\tu\tLinear\tNonlinear" << endl;
    
    double y_linear = y0;
    double y_nl_prev = y0;
    double y_nl_curr = y0;
    
    cout << fixed << setprecision(4);
    cout << "0\t0\t" << y0 << "\t" << y0 << endl;

    for (int i = 0; i < steps; i++) {
        double power = u[i];
        
        // Линейная модель
        y_linear = linear_model(y_linear, power, a, b);
        
        // Нелинейная модель
        double y_nl_new = nonlinear_model(y_nl_curr, y_nl_prev, power, a, b, c, d);
        
        // Обновление состояний
        y_nl_prev = y_nl_curr;
        y_nl_curr = y_nl_new;
        
        cout << i + 1 << "\t" << power << "\t" 
             << y_linear << "\t" << y_nl_curr << endl;
    }

    return 0;
}