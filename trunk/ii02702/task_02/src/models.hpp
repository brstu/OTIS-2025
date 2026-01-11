#pragma once
#include <vector>

// Функция симуляции линейной модели
std::vector<double> simulateLinearModel(double y, double u, int t, double a, double b);
// Функция симуляции нелинейной модели
std::vector<double> simulateNonLinearModel(double y, double u, int t, double a, double b, double c, double d);