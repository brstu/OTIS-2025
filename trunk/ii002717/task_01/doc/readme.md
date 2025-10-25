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
<p align="right">Группы ИИ-27</p>
<p align="right">Соловчук И.Г.</p>
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
#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::setlocale(LC_ALL, "rus");

    int N;
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> N;
    if (N >= 100) {
        std::cout << "Ошибка: выход за границу\n";
        return 0;
    }

    double a;
    double b;
    double c;
    double d;

    std::cout << "Введите константы a, b, c, d: ";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    std::vector<double> u(N);
    std::cout << "Введите значения u(t) для t = 0.." << N - 1 << ":\n";
    for (int t = 0; t < N; ++t) {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    std::vector<double> y_lin(N + 1);
    std::vector<double> y_nl(N + 1);

    std::cout << "Введите начальную температуру y[0]: ";
    std::cin >> y_lin[0];
    y_nl[0] = y_lin[0];

    std::cout << "Введите y[1] для нелинейной модели: ";
    std::cin >> y_nl[1];

    // Линейная модель
    for (int t = 0; t < N; ++t) {
        y_lin[t + 1] = a * y_lin[t] + b * u[t];
    }

    // Нелинейная модель
    for (int t = 1; t < N; ++t) {
        y_nl[t + 1] = a * y_nl[t]
            - b * y_nl[t - 1] * y_nl[t - 1]
                + c * u[t]
                + d * std::sin(u[t - 1]);
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t \ty_lin \ty_nl\n";
    for (int t = 0; t <= N; ++t) {
        std::cout << t << "\t" << y_lin[t] << "\t" << y_nl[t] << "\n";
    }

    return 0;
}
