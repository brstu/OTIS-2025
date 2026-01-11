/**
 * @file pid_controller.h
 * @brief Заголовочный файл для класса регулятора пропорционально-интегрально-дифференциального типа
 */

#ifndef PID_REGULATOR_H
#define PID_REGULATOR_H

#include <vector>

/**
 * @class PIDRegulator
 * @brief Класс, реализующий цифровой ПИД-регулятор с дискретным временем
 * 
 * Класс обеспечивает вычисление управляющего сигнала на основе разностных уравнений
 * с применением рекуррентных формул для повышения вычислительной эффективности.
 */
class PIDRegulator {
private:
    double gain_factor;          ///< Коэффициент усиления регулятора
    double integration_const;    ///< Постоянная времени интегральной составляющей
    double differentiation_const; ///< Постоянная времени дифференциальной составляющей
    double discretization_step;  ///< Интервал дискретизации по времени
    
    double coeff_alpha;          ///< Коэффициент α рекуррентного алгоритма
    double coeff_beta;           ///< Коэффициент β рекуррентного алгоритма  
    double coeff_gamma;          ///< Коэффициент γ рекуррентного алгоритма
    
    std::vector<double> history_errors;  ///< Вектор предыдущих рассогласований e(k-1), e(k-2)
    double previous_control;     ///< Предыдущее значение управляющего воздействия u(k-1)

public:
    /**
     * @brief Инициализация ПИД-регулятора
     * @param gain_factor Коэффициент усиления регулятора
     * @param integration_const Постоянная времени интегральной составляющей
     * @param differentiation_const Постоянная времени дифференциальной составляющей
     * @param discretization_step Интервал дискретизации по времени
     */
    PIDRegulator(double gain_factor, double integration_const, 
                double differentiation_const, double discretization_step);
    
    /**
     * @brief Вычисляет величину управляющего воздействия
     * @param target_value Заданное (желаемое) значение регулируемой величины
     * @param measured_value Текущее измеренное значение процесса
     * @return Рассчитанное управляющее воздействие
     */
    double computeControl(double target_value, double measured_value);
    
    /**
     * @brief Выполняет сброс внутреннего состояния регулятора
     * 
     * Обнуляет историю ошибок и предыдущие выходные значения,
     * что эквивалентно началу работы с нулевыми начальными условиями
     */
    void clearState();
    
    /**
     * @brief Возвращает набор коэффициентов регулятора
     * @return Массив коэффициентов [α, β, γ] рекуррентного алгоритма
     */
    std::vector<double> obtainCoefficients() const;
};

#endif