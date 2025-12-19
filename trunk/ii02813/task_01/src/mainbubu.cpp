#include <iostream>
#include <memory>
#include <cmath>


class ModelSimulator 
{
public:
    virtual void runSimulation(double initialOutput, const double input, int steps) const = 0;
    virtual ~ModelSimulator() = default;
};

class LinearDynamicSystem : public ModelSimulator 
{
public:
    LinearDynamicSystem(const double coefficientA, const double coefficientB)
        : coeffA(coefficientA), coeffB(coefficientB) 
    {}
    
    ~LinearDynamicSystem() override = default;

    void runSimulation(double currentOutput, const double systemInput, int timeSteps) const override
    {   
        for(int step = 0; step <= timeSteps; step++)
        {
            std::cout << step << ' ' << currentOutput << std::endl;
            currentOutput = coeffA * currentOutput + coeffB * systemInput;
        } 
    }

private:
    const double coeffA;
    const double coeffB;
};


class NonlinearDynamicSystem : public ModelSimulator 
{
public:
    NonlinearDynamicSystem(const double a, const double b, const double c, const double d)
            : paramA(a), paramB(b), paramC(c), paramD(d) 
    {}
    
    ~NonlinearDynamicSystem() override = default;

    void runSimulation(double currentOutput, const double systemInput, int timeSteps) const override
    {
        double previousOutput = currentOutput;
        double previousInput = systemInput;
        for(int step = 0; step <= timeSteps; step++)
        {
            std::cout << step << ' ' << currentOutput << std::endl;
            previousOutput = currentOutput;
            double nextOutput = paramA * currentOutput - paramB * previousOutput * previousOutput 
                                + paramC * systemInput + paramD * sin(previousInput);
            previousInput += INPUT_INCREMENT;
            currentOutput = nextOutput;
        }
    }

private:
    const double paramA;
    const double paramB;
    const double paramC;
    const double paramD;

    static constexpr double INPUT_INCREMENT = 0.5;
};


class ModelFactory 
{
public:
    virtual std::unique_ptr<ModelSimulator> createModel() const = 0;
    virtual ~ModelFactory() = default;
};


class LinearModelFactory : public ModelFactory 
{
public:
    ~LinearModelFactory() override = default;

    std::unique_ptr<ModelSimulator> createModel() const override
    { 
        return std::make_unique<LinearDynamicSystem>(DEFAULT_COEFF_A, DEFAULT_COEFF_B); 
    }

private:
    static constexpr double DEFAULT_COEFF_A = 0.5;
    static constexpr double DEFAULT_COEFF_B = 0.5;
};

class NonlinearModelFactory : public ModelFactory 
{
public:
    ~NonlinearModelFactory() override = default;

    std::unique_ptr<ModelSimulator> createModel() const override
    { 
        return std::make_unique<NonlinearDynamicSystem>(
            DEFAULT_PARAM_A, DEFAULT_PARAM_B, DEFAULT_PARAM_C, DEFAULT_PARAM_D); 
    }

private:
    static constexpr double DEFAULT_PARAM_A = 0.5;
    static constexpr double DEFAULT_PARAM_B = 0.5;
    static constexpr double DEFAULT_PARAM_C = 0.5;
    static constexpr double DEFAULT_PARAM_D = 0.5;
};

int main() 
{
    std::unique_ptr<ModelFactory> factory;
    std::unique_ptr<ModelSimulator> simulator;
    
    const double INITIAL_OUTPUT = 0;
    const double SYSTEM_INPUT = 1;
    const int SIMULATION_STEPS = 25;

    std::cout << "Linear simulation:" << std::endl;
    factory = std::make_unique<LinearModelFactory>();
    simulator = factory->createModel();
    simulator->runSimulation(INITIAL_OUTPUT, SYSTEM_INPUT, SIMULATION_STEPS);
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl; 
    factory = std::make_unique<NonlinearModelFactory>();
    simulator = factory->createModel();
    simulator->runSimulation(INITIAL_OUTPUT, SYSTEM_INPUT, SIMULATION_STEPS);
    std::cout << std::endl;

    return 0;
}