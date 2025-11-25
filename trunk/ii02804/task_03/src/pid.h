#ifndef PID_H
#define PID_H

/**
 * @class PID
 * @brief Класс дискретного PID-регулятора.
 *
 * Параметры конструктора: K, T, Td, T0 .
 */
class PID {
private:
    double K;   ///< Коэффициент усиления.
    double T;   ///< Время интегрирования.
    double Td;  ///< Время дифференцирования.
    double T0;  ///< Период дискретизации.

    double q0{0.0};  ///< Дискретный коэффициент q0.
    double q1{0.0};  ///< Дискретный коэффициент q1.
    double q2{0.0};  ///< Дискретный коэффициент q2.

    double u_prev{0.0};   ///< Предыдущее значение управляющего воздействия.
    double e_prev_1{0.0}; ///< Ошибка предыдущего шага.
    double e_prev_2{0.0}; ///< Ошибка шага k-2.
    bool valid{false};    ///< Флаг корректности состояния.

public:
    PID(double in_K, double in_T, double in_Td, double in_T0);

    /**
     * @brief Вычисляет управляющее воздействие по текущей ошибке.
     * @param e Ошибка регулирования.
     * @return Новое значение управляющего сигнала.
     */
    double u_calc(double e);

    /** Делает коэффициенты недействительными (для тестов). */
    void invalidate() { valid = false; }

    ~PID() = default;
};

#endif // PID_H
