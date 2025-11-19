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
<p align="right">Любовицкий Н.Н.</p>
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
```C++
#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
class func {
private:
    double a;
    double b;
    double c;
    double d;
    double t_curr;
    double t_prev;
    double u_curr;
    double u_prev;
public:
    func() : a(1), b(1), c(1), d(1), t_curr(1), t_prev(0), u_curr(1), u_prev(0) {}
    func(double a, double b, double c, double d) : a(a), b(b), c(c), d(d), t_curr(3), t_prev(2), u_curr(3), u_prev(2) {}
    void value_set(double tcurr, double tprev, double ucurr, double uprev)
    {
        t_curr = tcurr;
        t_prev = tprev;
        u_curr = ucurr;
        u_prev = uprev;
    }
    std::vector<double> linear(int steps) const
    {
        std::vector<double> ans(steps);
        ans[0] = t_curr;
        for (int i = 1; i < steps; i++)
        {
            ans[i] = a * ans[i - 1] + b * u_curr;
        }
        return ans;
    }
    std::vector<double> nonlinear(int steps) const
    {
        std::vector<double> ans(steps);
        ans[0] = t_prev;
        ans[1] = t_curr;
        for (int i = 2; i < steps; i++)
        {
            ans[i] = a * ans[i - 1] - b * pow(ans[i - 2], 2) + c * u_curr + d * sin(u_prev);
        }
        return ans;
    }
};


int main()
{
    int steps;
    std::cin >> steps;
    func Func(0.2, 0.3, 0.4, 0.5);
    Func.value_set(3, 2, 3, 2);
    std::vector<double> temp(steps);
    temp = Func.linear(steps);
    std::cout << "Linear::\n";
    for (auto i : temp)
    {
        std::cout << i << std::endl;
    }
    temp = Func.nonlinear(steps);
    std::cout << "Nonlinear::\n";
    for (auto i : temp)
    {
        std::cout << i << std::endl;
    }
}
```

## Результат программы:
```
10
Linear::
3
1.5
1.2
1.14
1.128
1.1256
1.12512
1.12502
1.125
1.125
Nonlinear::
2
3
1.05465
-0.834422
1.15408
1.67659
1.5904
1.12945
1.12173
1.4963
```
