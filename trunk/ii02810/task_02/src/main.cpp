#include "model.h"
using namespace std;

int main() {
    float a, b, c, d, y, u;
    int steps;

    cout << "Linemodel: Enter constants (a, b, y, u, steps): ";
    cin >> a >> b >> y >> u >> steps;
    Linemodel(y, u, steps, a, b);

    cout << "UnLinemodel: Enter constants (a, b, c, d, y, u, steps): ";
    cin >> a >> b >> c >> d >> y >> u >> steps;

    Params p{ a, b, c, d, u, steps };
    UnLinemodel(p, y, y);
}