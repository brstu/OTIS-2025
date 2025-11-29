#include <iostream>
#include <cmath>
#include "test.h"

using namespace std;

float a = 0.5,
      b = 0.2,
      c = 0.15,
      d = 0.3,
      u = 1.2;

int main()
{
    float y0, y1, y2, y_temp;
    cout << "y1 = ?";
    cin >> y_temp;
    y1 = y_temp;
    y0 = y1;

    int n = 10;

    cout << endl << "Linear" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "t" << i + 1 << " = ";
        y2 = linear_step(y1, u, a, b);
        cout << y2 << endl;
        y0 = y1;
        y1 = y2;
    }

    cout << endl << "Nonlinear:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "t" << i + 1 << " = ";
        y2 = nonlinear_step(y1, y0, u, a, b, c, d);
        cout << y2 << endl;
        y0 = y1;
        y1 = y2;
    }

    return 0;
}
