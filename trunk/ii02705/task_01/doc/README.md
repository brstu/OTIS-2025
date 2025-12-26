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
<p align="right">Грищук Д.А.</p>
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

int main()
{
    double temperature;        // y(t)
    double temperature_prev;   // y(t-1)
    double temperature_next;   // y(t+1)

    double heat;               // u(t)
    double heat_prev;          // u(t-1)

    double a;
    double b;
    double c;
    double d;


    int steps;

    cout << "Введите начальную температуру и начальный нагрев: ";
    cin >> temperature >> heat;

    cout << "Введите коэффициенты a, b, c, d: ";
    cin >> a >> b >> c >> d;

    cout << "Введите количество шагов моделирования: ";
    cin >> steps;

    cout << "\nЛинейная модель:\n";

    double linear_temp = temperature;

    for (int k = 0; k < steps; k++)
    {
        linear_temp = a * linear_temp + b * heat;
        cout << "Шаг " << k + 1 << ", температура = " << linear_temp << endl;
    }

    
    cout << "\nНелинейная модель:\n";

    temperature_prev = temperature; // значение до первого шага
    heat_prev = heat;
    double current_temp = temperature;

    for (int k = 0; k < steps; k++)
    {
        temperature_next =
            a * current_temp
            - b * temperature_prev * temperature_prev
            + c * heat
            + d * sin(heat_prev);

        cout << "Шаг " << k + 1 << ", температура = " << temperature_next << endl;

        temperature_prev = current_temp;
        current_temp = temperature_next;
        heat_prev = heat;

        if (k < steps - 1)
        {
            cout << "Введите значение нагрева для следующего шага: ";
            cin >> heat;
        }
    }

    return 0;
}


```

## Результат программы:
Линейная модель:
Шаг 1, температура = 0.31
Шаг 2, температура = 0.3031
Шаг 3, температура = 0.303031
Шаг 4, температура = 0.30303
Шаг 5, температура = 0.30303
Шаг 6, температура = 0.30303
Шаг 7, температура = 0.30303