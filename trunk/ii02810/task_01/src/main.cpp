#include <iostream>
#include <cmath>

using namespace std;

struct Params {
    float a;
    float b;
    float c;
    float d;
    float u;
    int t;
};

void Linemodel(float y, float u, int t, float a, float b, int i = 1) {
    if (i <= t) {
        Linemodel(a * y + b * u, u, t, a, b, i + 1);
        cout << "y" << i << " = " << y << endl;
    }
    else {
        cout << "end_Linemodel\n";
    }
}

void UnLinemodel(const Params& p, float y, float y0, int i = 1) {
    if (i <= p.t) {
        float y_next = p.a * y - p.b * y0 * y0 + p.c * p.u + p.d * sin(p.u);

        UnLinemodel(p, y_next, y, i + 1);

        cout << "y" << i << " = " << y << endl;
    }
    else {
        cout << "end_UnLinemodel" << endl;
    }
}

int main() {
    float a;
    float b;
    float c;
    float d;
    float y;
    float u;
    int t;

    cout << "Linemodel: Enter constants (a, b, y, u, t) separated by spaces:\n";
    cin >> a >> b >> y >> u >> t;
    Linemodel(y, u, t, a, b);

    cout << "UnLinemodel: Enter constants (a, b, c, d, y, u, t) separated by spaces:\n";
    cin >> a >> b >> c >> d >> y >> u >> t;

    Params p{ a, b, c, d, u, t };
    UnLinemodel(p, y, y);
}