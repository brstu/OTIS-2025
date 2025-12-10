#ifndef FUNCTION_H
#define FUNCTION_H

#include <cmath>

/**
 * @class PID
 * @brief Класс для ПИД-регулятора.
 */
class PID {
private:
    double q0, q1, q2;
    double e_prev1, e_prev2;
    double u_prev;

public:
    /**
     * @brief Конструктор ПИД-регулятора.
     * @param K Коэффициент усиления.
     * @param T Постоянная интегрирования.
     * @param TD Постоянная дифференцирования.
     * @param T0 Шаг дискретизации.
     */
    PID(double K, double T, double TD, double T0);

    /**
     * @brief Вычисление управляющего воздействия.
     * @param e Текущая ошибка.
     * @return Управляющее воздействие u.
     */
    double compute(double e);
};

/**
 * @class Object
 * @brief Класс для модели объекта управления.
 */
class Object {
private:
    double a, b;
    double y_prev;

public:
    /**
     * @brief Конструктор объекта управления.
     * @param tau Постоянная времени.
     * @param K_obj Коэффициент усиления объекта.
     * @param T0 Шаг дискретизации.
     */
    Object(double tau, double K_obj, double T0);

    /**
     * @brief Обновление выхода объекта.
     * @param u Входное воздействие.
     * @return Выход y.
     */
    double update(double u);
};

#endif // FUNCTION_H