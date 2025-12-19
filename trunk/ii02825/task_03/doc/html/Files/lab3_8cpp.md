---
title: src/lab3.cpp

---

# src/lab3.cpp



## Namespaces

| Name           |
| -------------- |
| **[std](Namespaces/namespacestd.md)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| int | **[main](Files/lab3_8cpp.md#function-main)**()<br>Точка входа в программу.  |


## Functions Documentation

### function main

```cpp
int main()
```

Точка входа в программу. 

**Return**: 0 — успешное завершение 

Программа моделирует работу PID-регулятора для двух моделей объекта:

* линейной: y(k+1) = a*y(k) + b*u(k)
* нелинейной: y(k+1) = a*y(k) − b*y²(k) + c*u(k) + d*sin(u(k))

Выводит на каждом шаге:

* ошибку e
* управляющее воздействие u
* состояние объекта для линейной модели
* состояние объекта для нелинейной модели


< Начальная температура объекта

< Коэффициенты линейной модели

< Целевая температура

< Количество шагов моделирования

< Состояние линейной модели

< Состояние нелинейной модели

< Ошибка управления

< Управляющее воздействие




## Source code

```cpp


#include <iostream>
#include <cmath>
#include "pid.h"
#include "model.h"

using namespace std;

int main() {
    double y0;  
    double a, b; 

    cout << "Enter initial temperature y: ";
    cin >> y0;

    cout << "Enter parameters a and b for linear model: ";
    cin >> a >> b;

    double w;  
    cout << "Enter target temperature w: ";
    cin >> w;

    int steps; 
    cout << "Enter number of simulation steps: ";
    cin >> steps;

    // Параметры PID-регулятора
    double K  = 0.4;
    double T  = 3.0;
    double Td = 0.1;
    double T0 = 1.0;

    PID pid(K, T, Td, T0);

    double y_lin = y0;   
    double y_non = y0;   

    // Коэффициенты нелинейной модели
    double c = 0.2;
    double d = 0.15;

    cout << "\n=== Simulation started ===\n";
    cout << "Step | e | u | y_linear | y_non_linear\n";

    for (int k = 0; k < steps; k++) {
        double e = w - y_lin;           
        double u = pid.compute(e);      

        // Модели
        y_lin = linear(y_lin, u, a, b);
        y_non = non_linear(y_non, u, a, b, c, d);

        cout << "Step " << k
             << "  e=" << e
             << "  u=" << u
             << "  y_lin=" << y_lin
             << "  y_non=" << y_non
             << endl;
    }

    return 0;
}
```


-------------------------------

Updated on 2025-11-26 at 11:50:51 +0300
