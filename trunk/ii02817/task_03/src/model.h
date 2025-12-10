/**
 * @file model.h
 * @brief Модель объекта управления (растения)
 *
 * Этот класс представляет математическую модель объекта управления,
 * полученную в предыдущей лабораторной работе.
 */

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <cmath>

/**
 * @class PlantModel
 * @brief Модель объекта управления с линейной и нелинейной динамикой
 */
class PlantModel
{
private:
    double a = 1.0;      ///< Коэффициент a модели
    double b = 1.0;      ///< Коэффициент b модели
    double c = 1.0;      ///< Коэффициент c модели
    double d = 1.0;      ///< Коэффициент d модели
    double t = 10.0; ///< Предыдущее значение выходной переменной
    double u = 0.0;//< Предыдущее значение входной переменной

public:
    /**
     * @brief Конструктор по умолчанию
     */
    PlantModel() = default;

    /**
     * @brief Параметризованный конструктор
     * @param a Коэффициент a
     * @param b Коэффициент b
     * @param c Коэффициент c
     * @param d Коэффициент d
     */
    PlantModel(double a, double b, double c, double d);

    /**
     * @brief Установка параметров модели
     * @param a Коэффициент a
     * @param b Коэффициент b
     * @param c Коэффициент c
     * @param d Коэффициент d
     */
    void setParameters(double a, double b, double c, double d);

    /**
     * @brief Установка состояния модели
     * @param tcurr Текущее значение выходной переменной
     * @param tprev Предыдущее значение выходной переменной
     * @param ucurr Текущее значение входной переменной
     * @param uprev Предыдущее значение входной переменной
     */
    void setState(double t, double u);

    /**
     * @brief Получение текущего выхода модели
     * @return Текущее значение выходной переменной
     */
    double getOutput() const;

    /**
     * @brief Линейная модель на один шаг
     * @param u Входное воздействие
     * @return Новое значение выходной переменной
     */
    double linearStep(double u);

    /**
     * @brief Нелинейная модель на один шаг
     * @param u Входное воздействие
     * @return Новое значение выходной переменной
     */
    double nonlinearStep(double u);

    /**
     * @brief Линейная модель на несколько шагов
     * @param steps Количество шагов
     * @return Вектор значений выходной переменной
     */
    std::vector<double> linear(int steps) const;

    /**
     * @brief Нелинейная модель на несколько шагов
     * @param steps Количество шагов
     * @return Вектор значений выходной переменной
     */
    std::vector<double> nonlinear(int steps) const;
};

#endif // MODEL_H