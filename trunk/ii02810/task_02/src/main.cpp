#include "model.h"
using namespace std;

int main() {
    float a, b, c, d, y, y0, u;
    int steps, linemodel_result, result;

    cout << "Linemodel: Enter constants (a, b, y, u, steps): ";
    cin >> a >> b >> y >> u >> steps;
    auto linemodel_result = Linemodel(y, u, steps, a, b);
    cout << "Linemodel result: "<< linemodel_result << endl;

    cout << "UnLinemodel: Enter constants (a, b, c, d, y, y0, u, steps): ";
    cin >> a >> b >> c >> d >> y >> y0 >> u >> steps;

    Params p{ a, b, c, d, u, steps };
    auto result = UnLinemodel(p, y, y0);
    cout << "UnLinemodel result: " << result << endl;
}