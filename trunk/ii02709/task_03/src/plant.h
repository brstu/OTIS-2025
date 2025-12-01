/**
 * @file plant.h
 * @brief Модели дискретного объекта управления: линейная и простая нелинейная.
 */

#ifndef II02709_PLANT_HPP
#define II02709_PLANT_HPP

/**
 * @brief Абстрактный интерфейс дискретной модели объекта.
 */
class IPlant {
public:
    virtual ~IPlant() = default;

    /**
     * @brief Выполнить один шаг модели с управляющим воздействием u.
     * @param u Управляющее воздействие.
     * @return Значение выхода y(k).
     */
    virtual double step(double u) = 0;

    /**
     * @brief Сброс состояния модели.
     */
    virtual void reset() = 0;

    /**
     * @brief Возвращает текущее значение выхода.
     */
    virtual double y() const = 0;
};

/**
 * @class LinearPlant
 * @brief Линейная модель 1-го порядка: y(k+1) = a*y(k) + b*u(k) + c.
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
 * @brief Нелинейная модель с простым насыщением входа:
 * y(k+1) = a*y(k) + b * (u / (1 + alpha * |u|)) + c
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

#endif // II02709_PLANT_HPP
