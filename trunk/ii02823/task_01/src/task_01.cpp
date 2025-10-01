#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double y, u;
    cout << "Enter y and u values:\n";
    cin >> y >> u;
    
    double a, b, c, d;
    cout << "Enter a, b, c, d values:\n";
    cin >> a >> b >> c >> d;

    int n;
    cout << "Enter number of steps n: ";
    cin >> n;

    double y1 = y, y2 = y;
    for (int i = 0; i < n; i++)
    {
        y1 = a * y1 + b * u;
        y2 = a * y2 - b * y2 * y2 + c * u + d * sin(u);
        cout << "Result of the " << i + 1 << "st step of linear model: " << y1 << ";\n";
        cout << "Result of the " << i + 1 << "st step of non-linear model: " << y2 << ";\n";
    }

    return 0;
}
