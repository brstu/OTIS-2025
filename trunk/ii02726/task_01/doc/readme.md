<p style="text-align: center;">Министерство образования Республики Беларусь</p>
<p style="text-align: center;">Учреждение образования</p>
<p style="text-align: center;">“Брестский Государственный технический университет”</p>
<p style="text-align: center;">Кафедра ИИТ</p>
<div style="margin-bottom: 10em;"></div>
<p style="text-align: center;">Лабораторная работа №1</p>
<p style="text-align: center;">По дисциплине “Общая теория интеллектуальных систем”</p>
<p style="text-align: center;">Тема: “Моделирования температуры объекта”</p>
<div style="margin-bottom: 10em;"></div>
<p style="text-align: right;">Выполнил:</p>
<p style="text-align: right;">Студент 2 курса</p>
<p style="text-align: right;">Группы ИИ-27</p>
<p style="text-align: right;">Юшкевич А.Ю.</p>
<p style="text-align: right;">Проверил:</p>
<p style="text-align: right;">Иванюк Д. С.</p>
<div style="margin-bottom: 10em;"></div>
<p style="text-align: center;">Брест 2025</p>

---

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: trunk\ii0xxyy\task_01\doc (где xx - номер группы, yy - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program, which simulates this object temperature.

---

# Выполнение задания #

Код программы:

#include <iostream>
#include <cmath>

int main() {
    int max_steps= 100;
    int steps;
    double a, b, c, d;
    long double y[max_steps];
    double u[max_steps];

    std::cout << "enter steps: ";
    std::cin >> steps;
    if (steps > max_steps || steps < 2) {
        std::cout << "incorreect: \n";
        return 1;
    }

    std::cout << "enter a: \n";
    std::cin >> a;
    std::cout << "enter b: \n";
    std::cin >> b;
    std::cout << "enter c: \n";
    std::cin >> c;
    std::cout << "enter d: \n";
    std::cin >> d;
    std::cout << "enter y0: \n";
    std::cin >> y[0];
    std::cout << "entter y1: \n";
    std::cin >> y[1];

    std::cout << "enter u: \n";
    for (int t = 0; t < steps; ++t) {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    int model;
    std::cout << "choose model: 1-linear; 2-non-linear";
    std::cin >> model;

    for (int t = 1; t < steps; t++) {
        if (model == 1) {
            y[t + 1] = a * y[t] + b * u[t];
        } else {
            y[t + 1] = a * y[t] - b * y[t - 1] * y[t - 1] + c * u[t] + d * sin(u[t - 1]);
        }
    }

    for (int t = 0; t <= steps; t++) {
        std::cout << "step " << t << ": y = " << y[t] << "\n";
    }

    return 0;
}
    Вывод:
    Линейная модель

    step 0: y = 15
    step 1: y = 15.5
    step 2: y = 53.5
    step 3: y = 89.5
    step 4: y = 123.5
    step 5: y = 155.5
    step 6: y = 185.5
    step 7: y = 213.5
    step 8: y = 239.5
    step 9: y = 263.5
    step 10: y = 285.5
    step 11: y = 305.5
    step 12: y = 323.5
    step 13: y = 339.5
    step 14: y = 353.5
    step 15: y = 365.5
    step 16: y = 375.5
    step 17: y = 383.5
    step 18: y = 389.5
    step 19: y = 395.5
    step 20: y = 399.5
  
    *********************
    Нелинейная модель

    step 0: y = 15
    step 1: y = 15.5
    step 2: y = -373.848
    step 3: y = -799.749
    step 4: y = -280277
    step 5: y = -1.55943e+06
    step 6: y = -1.57112e+11
    step 7: y = -5.02075e+12
    step 8: y = -4.93681e+22
    step 9: y = -5.04652e+25
    step 10: y = -4.87443e+45
    step 11: y = -5.09347e+51
    step 12: y = -4.75201e+91
    step 13: y = -5.18869e+103
    step 14: y = -4.51632e+183
    step 15: y = -5.3845e+207
    step 16: y = -4.07942e+367
    step 17: y = -5.79856e+415
    step 18: y = -3.32834e+735
    step 19: y = -6.72465e+831
    step 20: y = -2.21557e+1471