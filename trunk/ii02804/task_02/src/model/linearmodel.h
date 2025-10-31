#pragma once
#include <vector>

class LinearModel {
public:
    LinearModel(double a, double b)
        : m_a(a), m_b(b) {}

    std::vector<double> simulate(int n, double u0, double y0) const {
        std::vector<double> result;
        double y = y0;
        for (int i = 0; i < n; ++i) {
            result.push_back(y);
            y = m_a * y + m_b * u0;
        }
        return result;
    }

private:
    double m_a;
    double m_b;
};
