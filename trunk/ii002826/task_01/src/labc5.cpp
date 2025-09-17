#include <iostream>
#include <cmath>

using namespace std;

double f(double x, double y, double z, int c) {
    return pow(x, 3) * pow(y, 2) * z - 2 * pow(x, 2) * y * z + 3 * x * y + c;
}

double dx(double x, double y, double z) {
    return 3 * pow(x, 2) * pow(y, 2) * z - 4 * x * y * z + 3 * y;
}

double dy(double x, double y, double z) {
    return 2 * pow(x, 3) * y * z - 2 * pow(x, 2) * z + 3 * x;
}

double dz(double x, double y, double z) {
    return pow(x, 3) * pow(y, 2) - 2 * pow(x, 2) * y;
}

int main() {
    int sn = 9;
    int fn = 6;
    int hn = 8;

    int cc;
    cout << "Введите c: ";
    cin >> cc;

    double a = 10, b = 7, c = 9;
    int iteration = 10;
    double adam = 0.000001;

    for (int i = 0; i < iteration; i++) {
        while (a >= (sn - 2) && a <= (sn + 2)) {
            double a1 = a - adam * dx(a, b, c);
            if (a1 < (sn - 2) || a1 > (sn + 2)) {
                break;
            } else {
                a = a1;
            }
        }

        while (b >= (fn - 2) && b <= (fn + 2)) {
            double b1 = b - adam * dy(a, b, c);
            if (b1 < (fn - 2) || b1 > (fn + 2)) {
                break;
            } else {
                b = b1;
            }
        }

        while (c >= (hn - 3) && c <= (hn + 3)) {
            double c1 = c - adam * dz(a, b, c);
            if (c1 < (hn - 3) || c1 > (hn + 3)) {
                break;
            } else {
                c = c1;
            }
        }
    }

    cout << "Координаты локального минимума [" << a << ", " << b << ", " << c << "], значение функции " << f(a, b, c, cc) << endl;

    return 0;
}