/**
 * @file    model.h
 * @brief   Заголовочный файл класса Model
 * @details Описание класса модели (линейной и нелинейной)
 * @author  Vladimir
 * @date    2025-12-09
 * @version 1.0
 */

#ifndef MODEL_H
#define MODEL_H

/**
 * @class Model
 * @brief Класс, представляющий объект управления (модель)
 * 
 * Класс реализует линейную и нелинейную модели объекта управления.
 * Используется для тестирования ПИД-регулятора.
 */
class Model {
private:
    double a;        ///< Коэффициент A модели
    double b;        ///< Коэффициент B модели
    double c;        ///< Коэффициент C модели
    double d;        ///< Коэффициент D модели
    double y_prev1;  ///< Предыдущее значение выхода (y[k-1])
    double y_prev2;  ///< Значение выхода на два шага назад (y[k-2])
    double u_prev1;  ///< Предыдущее значение входа (u[k-1])
    double u_prev2;  ///< Значение входа на два шага назад (u[k-2])
    
public:
    /**
     * @brief Конструктор класса Model
     * @param a_val Коэффициент A (по умолчанию 0.2)
     * @param b_val Коэффициент B (по умолчанию 0.3)
     * @param c_val Коэффициент C (по умолчанию 0.4)
     * @param d_val Коэффициент D (по умолчанию 0.5)
     */
    explicit Model(double a_val = 0.2, double b_val = 0.3, 
                   double c_val = 0.4, double d_val = 0.5);
    
    /**
     * @brief Инициализация начальных условий модели
     * @param y0 Начальное значение y[k-2]
     * @param y1 Начальное значение y[k-1]
     * @param u0 Начальное значение u[k-2]
     * @param u1 Начальное значение u[k-1]
     */
    void init(double y0, double y1, double u0, double u1);
    
    /**
     * @brief Линейная модель объекта управления
     * @param u Текущее управляющее воздействие
     * @return Текущее значение выхода модели
     * 
     * Уравнение модели: y[k] = a*y[k-1] + b*u[k]
     */
    double linearModel(double u);
    
    /**
     * @brief Нелинейная модель объекта управления
     * @param u Текущее управляющее воздействие
     * @return Текущее значение выхода модели
     * 
     * Уравнение модели: y[k] = a*y[k-1] - b*y[k-2]*tanh(y[k-2]) + c*u[k] + d*sin(u[k-1])
     * @warning Включает ограничение выходных значений
     */
    double nonlinearModel(double u);
    
    /**
     * @brief Получение текущего значения модели
     * @return Текущее значение выхода (y[k-1])
     */
    double getCurrentValue() const { return y_prev1; }
    
    /**
     * @brief Установка текущего значения модели
     * @param value Новое значение выхода
     */
    void setCurrentValue(double value) { y_prev1 = value; }
};

#endif