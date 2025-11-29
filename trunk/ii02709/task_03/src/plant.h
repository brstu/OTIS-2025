/**
 * @file plant.hpp
 * @brief Дискретные модели объекта управления (линейная и нелинейная).
 */

#ifndef II02709_PLANT_H
#define II02709_PLANT_H

/**
 * @brief Абстрактный интерфейс дискретной модели объекта управления.
 */
class IPlant {
public:
    virtual ~IPlant() = default;

    /**
     * @brief Выполнение одного шага модели.
     * @param u Управляющий сигнал
     * @return Выход y(k)
     */
    virtual double step(double u) = 0;

    /**
     * @brief Сброс состояния объекта.
     */
    virtual void reset() = 0;

    /**
     * @brief Текущее значение выхода объекта.
     */
    virtual double y() const = 0;
};

/**
 * @brief Линейная модель первого порядка:
 * y(k+1) = a*y(k) + b*u(k) + c
 */
class LinearPlant : public IPlant {
public:
    LinearPlant(double a, double b, double c, double y0 = 0.0);
    double step(double u) override;
    void reset() override;
    double y() const override { return yk; }

private:
    double a, b, c;
    double yk;
};

/**
 * @brief Нелинейная модель:
 * y(k+1) = a*y(k) + b*u(k)/(1+α|u|) + c
 */
class NonlinearPlant : public IPlant {
public:
    NonlinearPlant(double a, double b, double c, double alpha=0.01, double y0=0.0);
    double step(double u) override;
    void reset() override;
    double y() const override { return yk; }

private:
    double a, b, c, alpha;
    double yk;
};

#endif
