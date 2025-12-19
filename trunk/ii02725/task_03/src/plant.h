#ifndef II02725_PLANT_HPP
#define II02725_PLANT_HPP

class IPlant {
public:
    virtual ~IPlant() = default;
    virtual double step(double u) = 0;
    virtual void reset() = 0;
    virtual double y() const = 0;
};

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

class NonlinearPlant : public IPlant {
public:
    NonlinearPlant(double a, double b, double c, double alpha = 0.01, double y0 = 0.0);
    double step(double u) override;
    void reset() override;
    double y() const override { return yk; }

private:
    double a, b, c;
    double alpha;
    double yk;
};

#endif