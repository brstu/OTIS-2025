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
<p align="right">Малич А.В.</p>
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
#include <vector>
using namespace std;
int main() {
    const double a = 0.95;
    const double b = 0.05;
    const double y_initial = 23;

    vector<double> u = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };


    vector<double> y(u.size() + 1);
    y[0] = y_initial;


    cout << "Time\tu\ty" << endl;
    cout << "0\t" << "N/A\t" << y[0] << endl;

    for (int tau = 0; tau < u.size(); ++tau) {
        y[tau + 1] = a * y[tau] + b * u[tau];

        cout << tau + 1 << "\t" << u[tau] << "\t" << y[tau + 1] << endl;
    }

    return 0;
}

```

## Результат программы:
| Time |   u   |    y     |
|------|-------|----------|
|  0   |  N/A  | 23.0000  |
|  1   |  10   | 22.3500  |
|  2   |  15   | 21.9825  |
|  3   |  20   | 21.8834  |
|  4   |  25   | 22.0392  |
|  5   |  30   | 22.4372  |
|  6   |  25   | 22.5654  |
|  7   |  20   | 22.4371  |
|  8   |  15   | 22.0653  |
|  9   |  10   | 21.4620  |
|  10  |   5   | 20.6389  |
