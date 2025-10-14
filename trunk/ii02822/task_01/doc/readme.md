<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Олексюк И.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование (review, checklist) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

# Выполнение задания #
Код программы:
```
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    double u, y, a, b, c, d;
    int count_steps;

    cout << "Введите u(входящую теплоту) и y(входящую температуру): " << endl;
    cin >> u >> y;
    cout << "Введите константы a, b, c, d: " << endl;
    cin >> a >> b >> c >> d;
    cout << "Введите количество шагов: " << endl;
    cin >> count_steps;
    double yl = y, ynl = y;
    for (int i = 0; i < count_steps; i++)
    {
        yl = a * yl + b * u;
        ynl = a * ynl - b * ynl * ynl + c * u + d * sin(u);
        cout << "Результат " << i + 1 << " шага линейной функции: " << yl << ";\n";
        cout << "Результат " << i + 1 << " шага НЕлинейной функции: " << ynl << ";\n";
    }
    return 0;
}
```
Вывод программы:
```Введите u(входящую теплоту) и y(входящую температуру):
2
4.33
Введите константы a, b, c, d:
1.1
0.5
0.88
1.4
Введите количество шагов:
10
Результат 1 шага линейной функции: 5.763;
Результат 1 шага НЕлинейной функции: -1.57843;
Результат 2 шага линейной функции: 7.3393;
Результат 2 шага НЕлинейной функции: 0.0510131;
Результат 3 шага линейной функции: 9.07323;
Результат 3 шага НЕлинейной функции: 3.08783;
Результат 4 шага линейной функции: 10.9806;
Результат 4 шага НЕлинейной функции: 1.66228;
Результат 5 шага линейной функции: 13.0786;
Результат 5 шага НЕлинейной функции: 3.47994;
Результат 6 шага линейной функции: 15.3865;
Результат 6 шага НЕлинейной функции: 0.80597;
Результат 7 шага линейной функции: 17.9251;
Результат 7 шага НЕлинейной функции: 3.59479;
Результат 8 шага линейной функции: 20.7176;
Результат 8 шага НЕлинейной функции: 0.526029;
Результат 9 шага линейной функции: 23.7894;
Результат 9 шага НЕлинейной функции: 3.47329;
Результат 10 шага линейной функции: 27.1683;
Результат 10 шага НЕлинейной функции: 0.821752;
```