<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студентка 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Маковей Е. В.</p>
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

double computeLinear(double state, double signal, double factorA, double factorB);
double computeNonlinear(double state, double signal, double factorA, double factorB, double factorC, double factorD);

int main()
{
    setlocale(LC_ALL, "RU");

    double signalInput;
    double startValue;
    cout << "Введите входной сигнал и начальное значение:" << endl;
    cin >> signalInput >> startValue;

    double alphaParam;
    double betaParam;
    double gammaParam;
    double deltaParam;
    cout << "Введите параметры alpha, beta, gamma, delta: " << endl;
    cin >> alphaParam >> betaParam >> gammaParam >> deltaParam;

    int stepsCount;
    cout << "Введите количество итераций: " << endl;
    cin >> stepsCount;

    double linearState = startValue;
    double nonlinearState = startValue;

    for (int step = 0; step < stepsCount; step++)
    {
        linearState = computeLinear(linearState, signalInput, alphaParam, betaParam);
        nonlinearState = computeNonlinear(nonlinearState, signalInput, alphaParam, betaParam, gammaParam, deltaParam);

        cout << "Итерация " << step + 1 << " - Линейная модель: " << linearState << endl;
        cout << "Итерация " << step + 1 << " - Нелинейная модель: " << nonlinearState << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}

double computeLinear(double state, double signal, double factorA, double factorB)
{
    return factorA * state + factorB * signal;
}

double computeNonlinear(double state, double signal, double factorA, double factorB, double factorC, double factorD)
{
    double quadraticPart = factorB * state * state;
    double sinusPart = factorD * sin(signal);
    return factorA * state - quadraticPart + factorC * signal + sinusPart;
}


```



