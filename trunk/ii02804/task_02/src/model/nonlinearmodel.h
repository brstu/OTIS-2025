#pragma once
#include <vector>
#include <cmath>

class NonlinearModel {
public:
    NonlinearModel(double a, double b, double c, double d)
        : m_a(a), m_b(b), m_c(c), m_d(d) {}

    std::vector<double> simulate(int n, double u0, double y0, const std::vector<double>& inputs) const {
        std::vector<double> result;
        double y = y0;
        double y_prev = y0;
        double u_prev = u0;

        for (int i = 0; i < n; ++i) {
            double u = inputs[i];
            double y_next = m_a * y - m_b * pow(y_prev, 2) + m_c * u + m_d * sin(u_prev);
            result.push_back(y_next);

            y_prev = y;
            y = y_next;
            u_prev = u;
        }

        return result;
    }

private:
    double m_a, m_b, m_c, m_d;
};
