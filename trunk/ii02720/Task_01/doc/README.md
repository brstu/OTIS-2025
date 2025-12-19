<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Моделирования температуры объекта"</p>
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
<p align="right">Степанюк И.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование ([review](https://linearb.io/blog/code-review-on-github), [checklist](https://linearb.io/blog/code-review-checklist)) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке.
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
```cpp
#include <iostream>
#include <cmath>
#include <vector>

class TempSimulator {
    double coefA, coefB, coefC, coefD;
    double prevY, prevPrevY, prevU;

public:
    TempSimulator(double a, double b, double c, double d, double startTemp)
        : coefA(a), coefB(b), coefC(c), coefD(d), 
          prevY(startTemp), prevPrevY(startTemp), prevU(0) {}

    double computeLinear(double u) {
        prevY = coefA * prevY + coefB * u;
        return prevY;
    }

    double computeNonLinear(double u) {
        double result = coefA * prevY - coefB * prevPrevY * prevPrevY 
                      + coefC * u + coefD * std::sin(prevU);
        prevPrevY = prevY;
        prevY = result;
        prevU = u;
        return result;

## Код программы:
C++
#include <iostream>
#include <cmath>

using namespace std;

class TemperatureModel {
private:
    double a, b, c, d;
    double y_prev, y_prev2, u_prev;

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val, double Y0) {
        a = a_val;
        b = b_val;
        c = c_val;
        d = d_val;
        y_prev = Y0;
        y_prev2 = Y0;
        u_prev = 0;
    }

    double linear_step(double u) {
        double y = a * y_prev + b * u;
        y_prev = y;
        return y;
    }

    double nonlinear_step(double u) {
        double y = a * y_prev - b * y_prev2 * y_prev2 + c * u + d * sin(u_prev);
        y_prev2 = y_prev;
        y_prev = y;
        u_prev = u;
        return y;
    }
};

int main() {
    const double A = 0.8, B_LIN = 0.3, B_NLIN = 0.01;
    const double C = 0.4, D = 0.1, START_TEMP = 20.0;
    
    std::vector<double> inputs = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    
    TempSimulator linSim(A, B_LIN, 0, 0, START_TEMP);
    TempSimulator nlinSim(A, B_NLIN, C, D, START_TEMP);
    
    std::cout << "Step\tLinear\tNonLinear\n";
    
    for (size_t i = 0; i < inputs.size(); ++i) {
        double lin = linSim.computeLinear(inputs[i]);
        double nlin = nlinSim.computeNonLinear(inputs[i]);
        std::cout << i << "\t" << lin << "\t" << nlin << "\n";
    double a = 0.8;
    double b_linear = 0.3;
    double b_nonlinear = 0.01;
    double c = 0.4;
    double d = 0.1;
    double Y0 = 20.0;
    
    double u[] = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    int n = 10;
    
    TemperatureModel linear_model(a, b_linear, 0, 0, Y0);
    TemperatureModel nonlinear_model(a, b_nonlinear, c, d, Y0);
    
    cout << "Time\tLinear\tNonlinear" << endl;
    
    for (int tau = 0; tau < n; tau++) {
        double y_linear = linear_model.linear_step(u[tau]);
        double y_nonlinear = nonlinear_model.nonlinear_step(u[tau]);
        
        cout << tau << "\t" << y_linear << "\t" << y_nonlinear << endl;
    }
    
    return 0;
}
```

## Результаты
Программа выводит значения температуры для линейной и нелинейной моделей на каждом шаге моделирования.

## Вывод программы:
<br> 
![Output:](Output.jpg)


## Reviews:
<br>
Ревью1:
<br>
![Review1:](review1.jpg)
<br>
Ревью2:
<br>
![Review2:](review2.jpg)

