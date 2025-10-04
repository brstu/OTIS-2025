<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Глаголева Е.В.</p>
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
#include <cmath>

// Функция симуляции линейной модели
void simulateLinearModel(double y, double u, int t, double a, double b) {
    for (int i = 0; i <= t; i++) {
        std::cout << i << ' ' << y << std::endl;
        y = a * y + b * u;
    }
}

// Функция симуляции нелинейной модели
void simulateNonLinearModel(double y, double u, int t, double a, double b, double c, double d, double u_step) {
    // Инициализируем предыдущие выходные и входные значения с помощью смещений.
    // Смещения (yOffset и uOffset) представляют собой разницу между начальным и предыдущим состояниями,
    // позволяя нелинейной модели начать с заданной истории для y и u.
    const double y_offset = 0.1;
    const double u_offset = 0.1;

    double prevY = y - y_offset;
    double prevU = u - u_offset;

    for (int i = 0; i <= t; i++) {
        std::cout << i << ' ' << y << std::endl;
        double nextY = a * y - b * prevY * prevY + c * u + d * sin(prevU);
        prevU += u_step;
        prevY = y;
        y = nextY;
    }
}

int main() {
    // Начальные условия системы
    const double y = 0;        // начальное значение выходной переменной (состояние системы)
    const double u = 1;        // входное воздействие (управляющий сигнал)
    const int t = 25;          // время симуляции (количество шагов)

    // Параметры для линейной модели
    double linear_a = 0.4;     // коэффициент при предыдущем значении y
    double linear_b = 0.5;     // коэффициент при входном воздействии u

    // Параметры для нелинейной модели
    double nonlinear_a = 0.5;  // линейный коэффициент при y
    double nonlinear_b = 0.5;  // коэффициент при квадрате предыдущего значения y (нелинейность)
    double nonlinear_c = 0.3;  // коэффициент при входном воздействии u
    double nonlinear_d = 0.5;  // коэффициент при синусоидальном члене
    double u_step = 0.5;       // шаг изменения для переменной u в нелинейной модели

    std::cout << "Linear simulation:" << std::endl;
    simulateLinearModel(y, u, t, linear_a, linear_b);
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl;
    simulateNonLinearModel(y, u, t, nonlinear_a, nonlinear_b, nonlinear_c, nonlinear_d, u_step);
    std::cout << std::endl;

    return 0;
}
```
## Результат программы:
Linear simulation:
0 0
1 0.5
2 0.7
3 0.78
4 0.812
5 0.8248
6 0.82992
7 0.831968
8 0.832787
9 0.833115
10 0.833246
11 0.833298
12 0.833319
13 0.833328
14 0.833331
15 0.833332
16 0.833333
17 0.833333
18 0.833333
19 0.833333
20 0.833333
21 0.833333
22 0.833333
23 0.833333
24 0.833333
25 0.833333
Nonlinear simulation:
0 0
1 0.686663
2 1.13606
3 1.10542
4 0.545132
5 0.0812084
6 0.0642493
7 -0.0150558
8 -0.185393
9 -0.284036
10 -0.245586
11 -0.0500694
12 0.303084
13 0.739508
14 1.07318
15 1.06262
16 0.682755
17 0.327304
18 0.242962
19 0.139149
20 -0.0738539
21 -0.244326
22 -0.284555
23 -0.181194
24 0.0861155
25 0.490379
## Reviews
suzorje
<br>
![Review for suzorje](comm1.png)
<br>
topg1616
<br>
![Review for topg1616:](comm2.png)