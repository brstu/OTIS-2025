/**
 * @file lin_model.h
 * @brief Заголовочный файл с объявлением линейной модели объекта управления.
 *
 * Линейная модель описывает поведение системы по формуле:
 * \f[
 *     y(k) = a \cdot y(k-1) + b \cdot u(k)
 * \f]
 */
#ifndef LIN_MODEL_H
#define LIN_MODEL_H
 /**
  * @brief Линейная модель динамического объекта.
  *
  * @param y_prev Предыдущее значение выхода системы.
  * @param u Управляющее воздействие.
  * @param a Коэффициент обратной связи.
  * @param b Коэффициент усиления по управляющему сигналу.
  * @return Новое значение выхода системы.
  */
double linear_model(double y_prev, double u, double a, double b);

#endif
