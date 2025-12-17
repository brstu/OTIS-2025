<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа N1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Рыжов И.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
## Требования к размещению файлов
1. Подготовить результат выполнения лабораторной работы №1 в виде отчёта, оформленного с использованием разметки **Markdown** (файл `README.md`), и разместить его в каталоге:  
   `trunk\ii02718\task_01\doc`.
2. Реализацию программы, включая все файлы с исходным кодом, расположить в директории:  
   `trunk\ii02718\task_01\src`.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**Julia**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    const int n = 12;
    const double y0 = 25.0;
    const double a = 0.93;
    const double b = 0.15;
    const double c = 0.10;
    const double d = 0.35;

    vector<double> u(n);
    for (int t = 0; t < n; ++t) {
        u[t] = 1.0 + 0.3 * sin(0.7 * (t + 1)) + 0.1 * cos(0.2 * (t + 1));
    }

    cout << "--- LINEAR MODEL ---\n";
    cout << "y(t+1) = a*y(t) + b*u(t)\n";

    double y = y0;
    for (int t = 0; t < n; ++t) {
        double yNext = a * y + b * u[t];
        cout << "Step " << (t + 1) << " | u=" << u[t] << " | y=" << yNext << "\n";
        y = yNext;
    }

    cout << "\n--- NONLINEAR MODEL ---\n";
    cout << "y(t+1) = a*y(t) - b*y(t-1)^2 + c*u(t) + d*sin(u(t-1))\n";

    double yCur = y0;
    double yPrev = 0.0;
    double uPrev = u[0];

    for (int t = 0; t < n; ++t) {
        double yNext = a * yCur
                     - b * (yPrev * yPrev)
                     + c * u[t]
                     + d * sin(uPrev);

        cout << "Step " << (t + 1) << " | u=" << u[t] << " | y=" << yNext << "\n";

        yPrev = yCur;
        yCur = yNext;
        uPrev = u[t];
    }

    return 0;
}

```

## Вывод программы

### Линейная модель

Результаты моделирования:
Step 1 | u=1.29127 | y=23.4437
Step 2 | u=1.38774 | y=22.0108
Step 3 | u=1.3415 | y=20.6713
Step 4 | u=1.17017 | y=19.3998
Step 5 | u=0.948795 | y=18.1841
Step 6 | u=0.774763 | y=17.0275
Step 7 | u=0.722261 | y=15.9439
Step 8 | u=0.8077 | y=14.949
Step 9 | u=0.982324 | y=14.0499
Step 10 | u=1.15548 | y=13.2397
Step 11 | u=1.2376 | y=12.4986
Step 12 | u=1.18264 | y=11.8011


### Нелинейная модель

Результаты моделирования:
Step 1 | u=1.29127 | y=23.7155
Step 2 | u=1.38774 | y=-71.2194
Step 3 | u=1.3415 | y=-150.12
Step 4 | u=1.17017 | y=-899.983
Step 5 | u=0.948795 | y=-4216.96
Step 6 | u=0.774763 | y=-125417
Step 7 | u=0.722261 | y=-2.78405e+06
Step 8 | u=0.8077 | y=-2.362e+09
Step 9 | u=0.982324 | y=-1.16483e+12
Step 10 | u=1.15548 | y=-8.36855e+17
Step 11 | u=1.2376 | y=-2.03527e+23
Step 12 | u=1.18264 | y=-1.05049e+35