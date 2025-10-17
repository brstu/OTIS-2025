#ifndef LAB2_H
#define LAB2_H

#include <vector>

namespace lab2 {

// Параметры модели (constexpr — доступны на этапе компиляции)
constexpr long double a = 0.9L;
constexpr long double b = 0.5L;
constexpr long double c1 = 0.1L;
constexpr long double c2 = 0.05L;

// Вычисляет следующее значение линейной модели: next = a*y + b*u
long double next_linear(long double y_current, long double u);

// Вычисляет следующее значение нелинейной модели:
// next = a*y - b*y*y + c1*u + c2*sinh(u)
long double next_nonlinear(long double y_current, long double u);

// Симуляция n шагов для линейной модели.
// Возвращает вектор значений size = steps, где каждый элемент — next для шага t.
std::vector<long double> simulate_linear(int steps, long double y0, long double u);

// Симуляция n шагов для нелинейной модели.
std::vector<long double> simulate_nonlinear(int steps, long double y0, long double u);

} // namespace lab2

#endif // LAB2_H