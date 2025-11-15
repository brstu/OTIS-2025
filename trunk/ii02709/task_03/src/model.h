/**
 * @file model.h
 * @brief Математическая модель нелинейного объекта
 * @author ii02709
 * @date 2025
 */

#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

/**
 * @class NonlinearModel
 * @brief Нелинейная модель: y(k+1) = a*y - b*y² + c1*u + c2*sinh(u)
 */
class NonlinearModel {
public:
    /**
     * @brief Конструктор с параметрами
     * @param a Коэффициент линейной части
     * @param b Коэффициент квадратичной части
     * @param c1 Коэффициент линейного управления
     * @param c2 Коэффициент нелинейного управления
     */
    explicit NonlinearModel(double a = 0.9, double b = 0.1,
                            double c1 = 0.5, double c2 = 0.2);

    /**
     * @brief Вычисление следующего состояния
     * @param y_curr Текущее значение выхода
     * @param u Управляющее воздействие
     * @return Следующее значение y(k+1)
     */
    double next(double y_curr, double u) const;

    /**
     * @brief Симуляция на N шагов с постоянным u
     * @param steps Количество шагов
     * @param y0 Начальное состояние
     * @param u Постоянное управление
     * @return Вектор значений y
     */
    std::vector<double> simulate(int steps, double y0, double u) const;

private:
    double a_, b_, c1_, c2_;
};

#endif // MODEL_H