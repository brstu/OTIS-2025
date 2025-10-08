#include <iostream>
#include <memory>
#include <cmath>

// Интерфейс модели
class IModel
{
public:
    virtual void runSimulation(double state, const double input, int steps) const = 0;
    virtual ~IModel() = default;
};

// Линейная модель
class LinearSystem : public IModel
{
public:
    LinearSystem(double coeffA, double coeffB) : a(coeffA), b(coeffB) {}
    ~LinearSystem() override = default;

    void runSimulation(double state, const double input, int steps) const override
    {
        std::cout << "Step\tState" << std::endl;
        for (int i = 0; i <= steps; ++i)
        {
            std::cout << i << "\t" << state << std::endl;
            state = a * state + b * input;
        }
    }

private:
    const double a;
    const double b;
};

// Нелинейная модель
class NonLinearSystem : public IModel
{
public:
    NonLinearSystem(double a, double b, double c, double d)
        : a(a), b(b), c(c), d(d) {}
    ~NonLinearSystem() override = default;

    void runSimulation(double state, const double input, int steps) const override
    {
        std::cout << "Step\tState" << std::endl;
        double prevState = state;
        double prevInput = input;
        for (int i = 0; i <= steps; ++i)
        {
            std::cout << i << "\t" << state << std::endl;
            prevState = state;
            double nextState = a * state - b * prevState * prevState + c * input + d * std::sin(prevInput);
            prevInput += inputIncrement;
            state = nextState;
        }
    }

private:
    const double a, b, c, d;
    const double inputIncrement { 0.5 };
};

// Интерфейс фабрики
class IModelFactory
{
public:
    virtual std::unique_ptr<IModel> createModel() const = 0;
    virtual ~IModelFactory() = default;
};

// Фабрика линейной модели
class LinearFactory : public IModelFactory
{
public:
    std::unique_ptr<IModel> createModel() const override
    {
        return std::make_unique<LinearSystem>(a, b);
    }

private:
    const double a { 0.5 };
    const double b { 0.5 };
};

// Фабрика нелинейной модели
class NonLinearFactory : public IModelFactory
{
public:
    std::unique_ptr<IModel> createModel() const override
    {
        return std::make_unique<NonLinearSystem>(a, b, c, d);
    }

private:
    const double a { 0.5 };
    const double b { 0.5 };
    const double c { 0.5 };
    const double d { 0.5 };
};

int main()
{
    std::unique_ptr<IModelFactory> factory;
    std::unique_ptr<IModel> model;

    const double initialState = 0.0;
    const double inputSignal = 1.0;
    const int totalSteps = 25;

    std::cout << "=== Linear System Simulation ===" << std::endl;
    factory = std::make_unique<LinearFactory>();
    model = factory->createModel();
    model->runSimulation(initialState, inputSignal, totalSteps);

    std::cout << "\n=== Nonlinear System Simulation ===" << std::endl;
    factory = std::make_unique<NonLinearFactory>();
    model = factory->createModel();
    model->runSimulation(initialState, inputSignal, totalSteps);

    return 0;
}
