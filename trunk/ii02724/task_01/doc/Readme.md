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
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Ханцевич Г.С.</p>
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
##include <iostream>
#include <math.h>

using namespace std;

int main()
{

    double current_temp1;
    double previous_temp;
    double next_temp;
    double current_heat;
    double previous_heat;
    double param_a;
    double param_b;
    double param_c;
    double param_d;
    int steps_count;


    cout << "Input initial temperature and heat (separated by space): ";
    cin >> current_temp1 >> current_heat;

    cout << "Input coefficients a, b, c, d: ";
    cin >> param_a >> param_b >> param_c >> param_d;

    cout << "Input simulation steps count: ";
    cin >> steps_count;


    double initial_temp = current_temp1;

    cout << "\n--- LINEAR TEMPERATURE MODEL ---" << endl;
    cout << "Formula: T_next = a * T_current + b * U_current" << endl;


    for (int step = 1; step <= steps_count; step++)
    {
        current_temp = param_a * current_temp1 + param_b * current_heat;
        cout << "Step " << step << " - Temperature: " << current_temp << endl;
    }


    current_temp1 = initial_temp;
    previous_temp = 0.0;
    previous_heat = current_heat;

    cout << "\n--- NON-LINEAR TEMPERATURE MODEL ---" << endl;
    cout << "Formula: T_next = a*T - b*T_prev² + c*U + d*sin(U_prev)" << endl;

    for (int step = 1; step <= steps_count; step++)
    {

        next_temp = param_a * current_temp1 -
                   param_b * previous_temp * previous_temp +
                   param_c * current_heat +
                   param_d * sin(previous_heat);


        previous_temp = current_temp1;
        current_temp1 = next_temp;

        cout << "Step " << step << " - Temperature: " << current_temp1 << endl;

        previous_heat = current_heat;

        if (step < steps_count) {
            cout << "Provide heat input for step " << step + 1 << ": ";
            cin >> current_heat;
        }
    }

    cout << "\nSimulation completed!" << endl;
    return 0;
}
```
Вывод программы:
```
Input initial temperature and heat (separated by space): 20 1
Input coefficients a, b, c, d: 0.8 0.1 0.3 0.4
Input simulation steps count: 7

--- LINEAR TEMPERATURE MODEL ---
Formula: T_next = a * T_current + b * U_current
Step 1 - Temperature: 16.1
Step 2 - Temperature: 12.98
Step 3 - Temperature: 10.484
Step 4 - Temperature: 8.4872
Step 5 - Temperature: 6.88976
Step 6 - Temperature: 5.61181
Step 7 - Temperature: 4.58945

--- NON-LINEAR TEMPERATURE MODEL ---
Formula: T_next = a*T - b*T_prev² + c*U + d*sin(U_prev)
Step 1 - Temperature: 16.6366
Provide heat input for step 2: 10
Step 2 - Temperature: -23.3541
Provide heat input for step 3: 10
Step 3 - Temperature: -43.5785
Provide heat input for step 4: 10
Step 4 - Temperature: -86.622
Provide heat input for step 5: 10
Step 5 - Temperature: -256.424
Provide heat input for step 6: 10
Step 6 - Temperature: -952.694
Provide heat input for step 7: 10
Step 7 - Temperature: -7334.7

Simulation completed!

```
## Рецензирование запросов других студентов ##
![Рецензия работы пользователя JohnyDepp228:](../src/pic/rev1.png)

![Рецензия работы пользователя humoristoff :](../src/pic/rev2.png)