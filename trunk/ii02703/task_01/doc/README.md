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
<p align="right">Гинь Н.А.</p>
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

int main() {
    double y, y_prev, u, u_prev, a, b, c, d;
    int n;
    std::cout << "Enter start temperature and heat: ";
    std::cin >> y >> u;
    std::cout << "Enter a, b, c, d: ";
    std::cin >> a >> b >> c >> d;
    std::cout << "Steps: ";
    std::cin >> n;  
    double y_lin = y;
    std::cout << "\nLinear model:\n";
    for (int i = 0; i < n; i++) {
        y_lin = a * y_lin + b * u;
        std::cout << "Step " << i + 1 << ": " << y_lin << std::endl;
    }
    double y_curr = y;
    double y_prev_nl = y;
    double u_prev_nl = u;
    std::cout << "\nNonlinear model:\n";

    for (int i = 0; i < n; i++) {
        double y_next = a * y_curr - b * (y_prev_nl * y_prev_nl) + c * u + d * sin(u_prev_nl);

        y_prev_nl = y_curr;
        y_curr = y_next;
        u_prev_nl = u;

        std::cout << "Step " << i + 1 << ": " << y_curr << std::endl;

        if (i < n - 1) {
            std::cout << "Enter next heat: ";
            std::cin >> u;
        }
    }

    return 0;
}

```

## Результат программы:
Enter start temperature and heat:  10 3
Enter a, b, c, d (constants) values: 0.01 0.03 0.05 0.01
Enter number of steps n: 7
Steps: 5

Linear model:
Step 1: 0.19
Step 2: 0.0919
Step 3: 0.090919
Step 4: 0.0909092
Step 5: 0.0909091

Nonlinear model:
Step 1: -2.74859
Enter next heat: 10
Step 2: -2.52607
Enter next heat: 10
Step 3: 0.242657
Enter next heat: 10
Step 4: 0.305555
Enter next heat: 10
Step 5: 0.495849

![Рецензия работы пользователя JohnyDepp228](https://imgur.com/a/ipP9EQp)
![Рецензия работы пользователя suzorje](https://imgur.com/a/U5r7G80)