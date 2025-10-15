<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Вабищевич И.В</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}+by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

$$\Large y_{\tau+1}=ay_{\tau}+by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})+e u_{\tau-1}^2+f y_{\tau-2}+g$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d,e,f,g$ – some constants.

Код программы:
```C++
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



=== Linear System Simulation ===
Step    State
0       0
1       0.5
2       0.75
3       0.875
4       0.9375
5       0.96875
6       0.984375
7       0.992188
8       0.996094
9       0.998047
10      0.999023
11      0.999512
12      0.999756
13      0.999878
14      0.999939
15      0.999969
16      0.999985
17      0.999992
18      0.999996
19      0.999998
20      0.999999
21      1
22      1
23      1
24      1
25      1

=== Nonlinear System Simulation ===
Step    State
0       0
1       0.920735
2       1.03524
3       0.936409
4       0.82901
5       0.641436
6       0.439606
7       0.244775
8       0.103665
9       0.0669972
10      0.178484
11      0.433606
12      0.730356
13      0.926961
14      1.00285
15      0.993249
16      0.902596
17      0.750017
18      0.55617
19      0.351412
20      0.174113
21      0.0719037
22      0.0956407
23      0.27496
24      0.566518
25      0.832871
