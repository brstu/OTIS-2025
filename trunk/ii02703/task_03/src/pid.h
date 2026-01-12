#ifndef PID_H
#define PID_H
#include <vector>

/**
 * @class PID
 * @brief PID регулятор температуры
 * 
 * Класс реализует дискретный ПИД алгоритм
 * с линейной моделью объекта первого порядка
 */
class PID {
private:
    std::vector<double> err;       ///< Ошибка регулирования
    std::vector<double> temp;      ///< Температура объекта
    std::vector<double> ctrl;      ///< Управляющее воздействие
    std::vector<double> d_ctrl;    ///< Приращение управления
    
    double Ti;      ///< Постоянная интегрирования
    double Ts;      ///< Время дискретизации
    double Td;      ///< Постоянная дифференцирования
    double Kp;      ///< Коэффициент усиления
    
    double q0;      ///< Коэффициент q0
    double q1;      ///< Коэффициент q1
    double q2;      ///< Коэффициент q2
    
    double target;  ///< Заданное значение температуры
    double limit;   ///< Максимальная температура
    
    double a;       ///< Коэффициент A модели объекта
    double b;       ///< Коэффициент B модели объекта

public:
    /**
     * @brief Конструктор PID регулятора
     * 
     * Запрашивает у пользователя начальные значения:
     * - Стартовая температура
     * - Максимальная температура
     * - Целевая температура
     */
    PID();
    
    /**
     * @brief Инициализация параметров регулятора
     */
    void setup();
    
    /**
     * @brief Расчет коэффициентов PID
     */
    void calcQs();
    
    /**
     * @brief Вычисление ошибки регулирования
     * @param idx Номер текущего шага
     */
    void calcErr(int idx);
    
    /**
     * @brief Расчет управляющего воздействия
     * @param idx Номер текущего шага
     */
    void calcCtrl(int idx);
    
    /**
     * @brief Моделирование объекта управления
     * @param idx Номер текущего шага
     */
    void modelPlant(int idx);
    
    /**
     * @brief Основной цикл моделирования
     */
    void simulate();
    
    /**
     * @brief Получение коэффициентов PID
     * @param r0 Коэффициент q0
     * @param r1 Коэффициент q1
     * @param r2 Коэффициент q2
     */
    void getQs(double& r0, double& r1, double& r2) const;
};

#endif