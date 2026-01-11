#include "model.h"
#include <iostream>
using namespace std;

int main() {
    float a, b, c, d, y, y0, u;
    int steps;
    std::cout << "Linemodel: Enter constants (a, b, y, u, steps): ";
    std::cin >> a >> b >> y >> u >> steps;
    auto linemodel_result = Linemodel(y, u, steps, a, b);
    std::cout << "Linemodel result: ";
    for (const auto& val : linemodel_result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "UnLinemodel: Enter constants (a, b, c, d, y, y0, u, steps): ";
    std::cin >> a >> b >> c >> d >> y >> y0 >> u >> steps;
    Params p{ a, b, c, d, u, steps };
    auto result = UnLinemodel(p, y, y0);
    std::cout << "UnLinemodel result: ";
    if (result.empty()) {
        cout << "[No output: UnLinemodel returned an empty result, possibly due to invalid 'steps' parameter]";
    }
    else {
        for (const auto& val : result) {
            cout << val << " ";
        }
    cout << endl;
    return 0;
}