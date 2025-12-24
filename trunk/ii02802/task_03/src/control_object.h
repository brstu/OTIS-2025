#ifndef CONTROL_OBJECT_H
#define CONTROL_OBJECT_H

/**
 * @class ControlObject
 * @brief Модель объекта управления второго порядка.
 *
 * Моделирует динамику с использованием метода Эйлера.
 */
class ControlObject {
private:
    double y = 0.0; ///< Выход y
    double dy = 0.0; ///< Производная dy/dt
    double K_obj; ///< Коэффициент усиления K
    double T_obj; ///< Постоянная времени T
    double xi; ///< Коэффициент демпфирования ξ

public:
    /**
     * @brief Конструктор объекта управления.
     * @param K Коэффициент усиления.
     * @param T Постоянная времени.
     * @param xi Коэффициент демпфирования.
     */
    ControlObject(double K, double T, double xi);

    /**
     * @brief Обновление состояния объекта.
     * @param u Входное управление.
     * @param dt Шаг времени.
     * @return Новый выход y.
     */
    double update(double u, double dt);

    /**
     * @brief Получение текущего выхода.
     * @return y
     */
    double getY() const;
};

#endif // CONTROL_OBJECT_H