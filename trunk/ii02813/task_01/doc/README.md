<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Ковалевич Е.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование ([review](https://linearb.io/blog/code-review-on-github), [checklist](https://linearb.io/blog/code-review-checklist)) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.


## Код программы:
```C++
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
```

## Результат программы:
Вывод линейной симуляции:
<br>
![Вывод линейной симуляции:](output_linear_simulation.png)
<br>
Вывод нелинейной симуляции:
<br>
![Вывод нелинейной симуляции:](output_nonlinear_simulation.png)



