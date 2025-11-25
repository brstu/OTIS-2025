#ifndef LIN_MODEL_H
#define LIN_MODEL_H

/**
 * @brief Линейная динамическая модель.
 *
 * Вычисляет новое состояние объекта по формуле:
 * y(k) = a * y(k-1) + b * u(k)
 *
 * @param y_prev Предыдущее состояние объекта.
 * @param u Управляющее воздействие.
 * @param a Коэффициент влияния предыдущего состояния.
 * @param b Коэффициент влияния управляющего воздействия.
 * @return Новое состояние объекта.
 */
double linear_model(double y_prev, double u, double a, double b);

#endif // LIN_MODEL_H
