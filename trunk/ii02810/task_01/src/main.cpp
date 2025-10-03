#include <iostream>
#include <cmath>

using namespace std;

void Linemodel(float y, float u, float t, float a, float b, int i) {
    if (i <= t) {
        Linemodel(a * y + b * u, u, t, a, b, i + 1);
        cout << "y" << i << " = " << y << endl;
    }
    else cout << "end_Linemodel\n";
}

void UnLinemodel(float a, float b, float c, float d, float y, float y0, float u, int i, float t) {
    if (i <= t) {
        float y_next = a * y - b * y0 * y0 + c * u + d * sin(u);

        UnLinemodel(a, b, c, d, y_next, y, u, i + 1, t);

        cout << "y" << i << " = " << y << endl;
    }
    else {
        cout << "end_UnLinemodel" << endl;
    }
}

int main() {
    float a, b, c, d, y, u, t;
    int i = 1;
    cout << "Linemodel: Enter constants (a, b, y, u, t) separated by spaces:\n";
    cin >> a >> b >> y >> u >> t;
    Linemodel(y, u, t, a, b, i);
    cout << "UnLinemodel: Enter constants (a, b, c, d, y, u, t) separated by spaces:\n";
    cin >> a >> b >> c >> d >> y >> u >> t;
}