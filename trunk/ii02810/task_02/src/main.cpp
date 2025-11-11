#include "model.h"
using namespace std;

int main() {
    float a, b, c, d, y, y0, u;
    int steps;

    cout << "Linemodel: Enter constants (a, b, y, u, steps): ";
    cin >> a >> b >> y >> u >> steps;
    auto linemodel_result = Linemodel(y, u, steps, a, b);
    cout << "Linemodel result: ";
    for (const auto& val : linemodel_result) {
        cout << val << " ";
    }
    cout << endl;

    cout << "UnLinemodel: Enter constants (a, b, c, d, y, y0, u, steps): ";
    cin >> a >> b >> c >> d >> y >> y0 >> u >> steps;

    Params p{ a, b, c, d, u, steps };
    auto result = UnLinemodel(p, y, y0);
    cout << "UnLinemodel result: ";
    for (const auto& val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}