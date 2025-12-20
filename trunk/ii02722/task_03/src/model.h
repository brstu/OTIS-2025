#ifndef MODEL_H
#define MODEL_H

/**
 * @brief Простейшая линейная модель объекта управления.
 *
 * Модель описывается дифференциальным уравнением:
 * dx/dt = -a * x + u,
 * где x — состояние, a — коэффициент, u — управляющее воздействие.
 */
class Model {
public:
    /**
     * @brief Конструктор модели.
     * @param initial_state Начальное значение состояния x(0).
     * @param a Коэффициент затухания/усиления системы.
     */
    Model(double initial_state = 0.0, double a = 1.0);

    /**
     * @brief Обновить состояние модели.
     *
     * @param u Управляющее воздействие.
     * @param dt Шаг интегрирования (секунды).
     * @return Новое значение состояния.
     */
    double update(double u, double dt);

    /**
     * @brief Получить текущее состояние.
     * @return Текущее значение x.
     */
    double getState() const;

private:
    double x; ///< Состояние системы.
    double a; ///< Коэффициент модели.
};

#endif // MODEL_H
