#include "model.h"
using namespace std;

void Linemodel(float y, float u, int steps, float a, float b, int i) {
    if (i <= steps) {
        Linemodel(a * y + b * u, u, steps, a, b, i + 1);
        cout << "y" << i << " = " << y << endl;
    }
    else {
        cout << "end_Linemodel\n";
    }
}

void UnLinemodel(const Params& p, float y, float y0, int i) {
    if (i <= p.steps) {
        float y_next = p.a * y - p.b * y0 * y0 + p.c * p.u + p.d * sin(p.u);
        UnLinemodel(p, y_next, y, i + 1);
        cout << "y" << i << " = " << y << endl;
    }
    else {
        cout << "end_UnLinemodel" << endl;
    }
}