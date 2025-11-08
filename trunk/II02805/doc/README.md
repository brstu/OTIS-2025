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
<p align="right">Горщарик Н.А.</p>
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

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warmth; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.


## Код программы:
```C++
#include <iostream>
#include <cmath>

double linear_step(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_step(double y, double y_prev, double u, double u_prev, double a, double b, double c, double d) {
    return a * y - b * y_prev * y_prev + c * u + d * sin(u_prev);
}

int main() {
    double y, y_prev, y_next;
    double u, u_prev;
    double a, b, c, d;
    int steps;

    std::cout << "Введите начальное значение температуры y и начальное тепло u (через пробел): ";
    std::cin >> y >> u;

    std::cout << "Введите коэффициенты a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    std::cout << "Введите количество шагов моделирования: ";
    std::cin >> steps;

    y_prev = y;
    std::cout << "\n--- Линейная модель ---\n";
    for (int i = 1; i <= steps; ++i) {
        y = linear_step(y, u, a, b);
        std::cout << "Шаг " << i << ": y = " << y << '\n';
    }

    y_prev = 0;
    u_prev = u;
    std::cout << "\n--- Нелинейная модель ---\n";
    for (int i = 1; i <= steps; ++i) {
        y_next = nonlinear_step(y, y_prev, u, u_prev, a, b, c, d);
        y_prev = y;
        y = y_next;

        std::cout << "Шаг " << i << ": y = " << y << '\n';

        u_prev = u;
        std::cout << "Введите значение u для следующего шага: ";
        std::cin >> u;
    }

    return 0;
}
```

## Результат программы:
Введите начальное значение температуры y и начальное тепло u (через пробел): 1 10
Введите коэффициенты a, b, c, d: 0.01 0.03 0.05 0.01
Введите количество шагов моделирования: 7

--- Линейная модель ---
Шаг 1: y = 0.31
Шаг 2: y = 0.3031
Шаг 3: y = 0.303031
Шаг 4: y = 0.30303
Шаг 5: y = 0.30303
Шаг 6: y = 0.30303
Шаг 7: y = 0.30303

--- Нелинейная модель ---
Шаг 1: y = 1
Введите значение u для следующего шага: 10
Шаг 2: y = 0.50456
Введите значение u для следующего шага: 10
Шаг 3: y = 0.469605
Введите значение u для следующего шага: 10
Шаг 4: y = 0.491618
Введите значение u для следующего шага: 10
Шаг 5: y = 0.49286
Введите значение u для следующего шага: 10
Шаг 6: y = 0.492238
Введите значение u для следующего шага: 10
Шаг 7: y = 0.492195
