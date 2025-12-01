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


/**
 * @brief Нелинейная динамическая модель.
 *
 * Вычисляет новое состояние объекта по формуле:
 * y(k+1) = a * y(k) - b * y^2(k-1) + c * u(k) + d * sin(u(k-1))
 *
 *
 * @param y Текущее состояние объекта y(k).
 * @param y_prev Предыдущее состояние объекта y(k-1).
 * @param u Текущее управляющее воздействие u(k).
 * @param u_prev Предыдущее управляющее воздействие u(k-1).
 * @param a Коэффициент влияния текущего состояния.
 * @param b Коэффициент нелинейной обратной связи.
 * @param c Коэффициент влияния управляющего воздействия.
 * @param d Коэффициент синусоидальной составляющей.
 *
 * @return Новое состояние объекта y(k+1).
 */
double nonlinear_model(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d);

#endif // LIN_MODEL_H
