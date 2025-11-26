#include "sim.h"
#include <fstream>
#include <iomanip>

void save_csv(const std::string& path, const SimResult& r) {
    std::ofstream f(path);
    f << std::fixed << std::setprecision(6);
    f << "t,w,y,u,e\n";
    for (size_t i = 0; i < r.t.size(); ++i) {
        f << r.t[i] << "," << r.w[i] << "," << r.y[i] << "," << r.u[i] << "," << r.e[i] << "\n";
    }
}
