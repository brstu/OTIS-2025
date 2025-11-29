/**
 * @file plant.h
 * @brief Дискретные модели объекта управления.
 */

#ifndef II02709_PLANT_HPP
#define II02709_PLANT_HPP

/**
 * @brief Абстрактный интерфейс дискретной модели объекта.
 */
class IPlant {
public:
    virtual ~IPlant() = default;

    virtual double step(double u) = 0;
    virtual void reset() = 0;
    virtual double y() const = 0;
};

/**
 * @class LinearPlant
 * @brief Линейная модель первого порядка.
 */
class LinearPlant : public IPlant {
public:
    LinearPlant(double a, double b, double c, double y0 = 0.0);
    double step(double u) override;
    void reset() override;
    double y() const override { return yk; }

private:
    double a;
    double b;
    double c;
    double yk;
};

/**
 * @class NonlinearPlant
 * @brief Нелинейная модель: y(k+1)=a*y+b*u/(1+α|u|)+c.
 */
class NonlinearPlant : public IPlant {
public:
    NonlinearPlant(double a, double b, double c, double alpha = 0.01, double y0 = 0.0);
    double step(double u) override;
    void reset() override;
    double y() const override { return yk; }

private:
    double a;
    double b;
    double c;
    double alpha;
    double yk;
};

#endif
