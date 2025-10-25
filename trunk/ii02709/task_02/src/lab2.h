#ifndef LAB2_H
#define LAB2_H

#include <vector>

namespace lab2 {
constexpr long double a = 0.9L;
constexpr long double b = 0.5L;
constexpr long double c1 = 0.1L;
constexpr long double c2 = 0.05L;
long double next_linear(long double y_current, long double u);
long double next_nonlinear(long double y_current, long double u);
std::vector<long double> simulate_linear(int steps, long double y0, long double u);
std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u);

}

#endif