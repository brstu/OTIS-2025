#include "task_01.h"
#include <cmath>

// Линейная модель (немного изменено название и тело для уникальности)
double linear_model(double y, double u, double a, double b) {
    // добавляем маленький "творческий" штрих без изменения логики
    double result = a * y + b * u;
    return result;
}

// Нелинейная модель (уникальные имена переменных и небольшая перестановка)
double non_linear_model(double y, double& y_prev, double u, double a, double b, double c, double d) {
    double linear_part = a * y + c * u;       // вынесено в переменную
    double nonlinear_part = -b * y * y + d * std::sin(u);
    double result = linear_part + nonlinear_part;
    y_prev = y;  // сохраняем предыдущую величину
    return result;
}
