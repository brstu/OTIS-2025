#ifndef PID_H
#define PID_H

#include <vector>

/**
 * @class PID
 * @brief Цифровой ПИД-регулятор
 */
class PID {
private:
    double K;        
    double Ti;       
    double Td;       
    double T0;       

    double q0 = 0.0;       
    double q1 = 0.0;       
    double q2 = 0.0;       

    double e_prev1 = 0.0;  
    double e_prev2 = 0.0;  
    double u_prev = 0.0;   

    double integral = 0.0; 
    double d_prev = 0.0;   

public:
    /**
     * @brief Конструктор ПИД-регулятора
     * @param K_val Коэффициент усиления
     * @param Ti_val Постоянная времени интегрирования
     * @param Td_val Постоянная времени дифференцирования
     * @param T0_val Период дискретизации (по умолчанию 1.0)
     */
    PID(double K_val, double Ti_val, double Td_val, double T0_val = 1.0);

    /**
     * @brief Вычисление управляющего воздействия
     * @param setpoint Заданное значение
     * @param current_value Текущее значение процесса
     * @return Управляющее воздействие u[k] (ограниченное 0-100%)
     */
    double calculate(double setpoint, double current_value);

    /**
     * @brief Сброс состояния регулятора
     */
    void reset();

    /**
     * @brief Получение коэффициентов рекуррентного алгоритма
     * @return Вектор коэффициентов [q0, q1, q2]
     */
    std::vector<double> getCoefficients() const;

    /**
     * @brief Получение параметров ПИД-регулятора
     * @param[out] K_param Коэффициент усиления
     * @param[out] Ti_param Постоянная времени интегрирования
     * @param[out] Td_param Постоянная времени дифференцирования
     */
    void getParameters(double& K_param, double& Ti_param, double& Td_param) const;
};

#endif