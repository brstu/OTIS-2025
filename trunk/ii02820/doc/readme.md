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
#include <cmath>
using namespace std;

int main() {
    double a = 0.95;
    double b = 0.002;
    double c = 0.05;
    double d = 0.1;

    double y_linear = 23;
    double y_nonlinear = 23;
    double y_nonlinear_prev = 23;

    double u[] = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };
    int steps = 10;

    cout << "Model :" << endl;
    cout << "Time\tu\tLinear\tNonlinear" << endl;
    cout << "0\t0\t" << y_linear << "\t" << y_nonlinear << endl;

    double u_prev = 0;

    for (int i = 0; i < steps; i++) {
        double power = u[i];

        y_linear = a * y_linear + b * power;

        double no = a * y_nonlinear;
        double ss = b * y_nonlinear_prev * y_nonlinear_prev;
        double co = c * power;
        double si = d * sin(u_prev);

        y_nonlinear_prev = y_nonlinear;
        y_nonlinear = no - ss + co + si;
        u_prev = power;

        cout << i + 1 << "\t" << power << "\t" << y_linear << "\t" << y_nonlinear << endl;
    }

    return 0;
}
```

## Результат программы:
| Time | u     | Linear  | Nonlinear |
|------|-------|---------|-----------|
| 0    | 0     | 23      | 23        |
| 1    | 10    | 21.87   | 21.292    |
| 2    | 15    | 20.8065 | 19.865    |
| 3    | 20    | 19.8062 | 19.0301   |
| 4    | 25    | 18.8659 | 18.6306   |
| 5    | 30    | 17.9826 | 18.4616   |
| 6    | 25    | 17.1334 | 17.9955   |
| 7    | 20    | 16.3168 | 17.4008   |
| 8    | 15    | 15.5309 | 16.7244   |
| 9    | 10    | 14.7744 | 15.8476   |
| 10   | 5     | 14.0457 | 14.6914   |


