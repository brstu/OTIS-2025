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
<p align="right">Гойшик Т.Д.</p>
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
C++
#include <iostream>
#include <cmath>

using namespace std;


void simulateLinearModel(int n, double a, double b, double u0, double y0) {
    double y = y0;

    cout << "\n--- Linear Model ---\n";
    for (int tau = 0; tau < n; ++tau) {
        cout << "Time " << tau + 1 << ": " << y << endl;
        y = a * y + b * u0;
    }
}


void simulateNonlinearModel(int n, double a, double b, double c, double d, double u0, double y0) {
    double y = y0;
    double y_prev = y0;
    double u_prev = u0;  

    cout << "\n--- Nonlinear Model ---\n";
    for (int tau = 0; tau < n; ++tau) {
        cout << "Time " << tau + 1 << ": " << y << endl;

        // Prompt user for heat input at each time step
        double u;
        cout << "Enter heat input at time " << tau + 1 << ": ";
        cin >> u;

        
        double y_next = a * y - b * pow(y_prev, 2) + c * u + d * sin(u_prev);

        y_prev = y;
        y = y_next;
        u_prev = u;  
    }
}

int main() {
    int n;
    double u0;
    double y0;

    cout << "Enter number of time steps n: ";
    cin >> n;

    cout << "Enter initial heat input u0: ";
    cin >> u0;

    cout << "Enter initial temperature y0: ";
    cin >> y0;

    double a = 0.9;
    double b = 0.1;
    double c = 0.05;
    double d = 0.02;

    simulateLinearModel(n, a, b, u0, y0);
    simulateNonlinearModel(n, a, b, c, d, u0, y0);

    return 0;
}


## Результат программы:
Ввод данных:
<br>
![Ввод:](input.png)
<br>
Вывод линейной симуляции:
<br>
![Вывод линейной симуляции:](output_linear_simulation.png)
<br>
Вывод нелинейной симуляции:
<br>
![Вывод нелинейной симуляции:](output_nonlinear_simulation.png)




