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
<p align="right">Люкевич В.Д.</p>
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
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.
<hr>

# Выполнение задания #

Код программы:
```C++
#include <iostream>
#include <vector>
#include <cmath>

class TemperatureModel {
private:
    double a;
    double b;
    double c;
    double d;
    double y_prev = 0;  
    double y_curr = 0;  
    double u_prev = 0;  
    double u_curr = 0;  

public:
    TemperatureModel(double a, double b, double c, double d)
        : a(a), b(b), c(c), d(d) {
    }

    void setInitialState(double y0, double y1, double u0, double u1) {
        y_prev = y0;
        y_curr = y1;
        u_prev = u0;
        u_curr = u1;
    }

    void updateControl(double u_new) {
        u_prev = u_curr;
        u_curr = u_new;
    }

    std::vector<double> simulateLinear(int time_steps) const {
        std::vector<double> temperatures(time_steps);

        if (time_steps >= 1) temperatures[0] = y_prev;
        if (time_steps >= 2) temperatures[1] = y_curr;

        for (int t = 2; t < time_steps; t++) {
            temperatures[t] = a * temperatures[t - 1] + b * u_curr;
        }

        return temperatures;
    }

    std::vector<double> simulateNonlinear(int time_steps) const {
        std::vector<double> temperatures(time_steps);

        if (time_steps >= 1) temperatures[0] = y_prev;
        if (time_steps >= 2) temperatures[1] = y_curr;

        for (int t = 2; t < time_steps; t++) {
            temperatures[t] = a * temperatures[t - 1]
                - b * std::pow(temperatures[t - 2], 2)
                + c * u_curr
                + d * std::sin(u_prev);
        }

        return temperatures;
    }
};

int main() {
    double a = 0.2;
    double b = 0.3;
    double c = 0.4;
    double d = 0.5;
    TemperatureModel model(a, b, c, d);
    model.setInitialState(20.0, 21.0, 1.0, 1.5);

    int simulation_time;
    std::cout << "Enter simulation time steps: ";
    std::cin >> simulation_time;

    std::cout << "Model parameters: a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;

    std::cout << "\nLinear Model Simulation:" << std::endl;
    auto linear_results = model.simulateLinear(simulation_time);
    for (int t = 0; t < linear_results.size(); t++) {
        std::cout << "Time t=" << t << ": y(t) = " << linear_results[t] << std::endl;
    }

    std::cout << "\nNonlinear Model Simulation:" << std::endl;
    auto nonlinear_results = model.simulateNonlinear(simulation_time);
    for (int t = 0; t < nonlinear_results.size(); t++) {
        std::cout << "Time t=" << t << ": y(t) = " << nonlinear_results[t] << std::endl;
    }

    return 0;
}
```