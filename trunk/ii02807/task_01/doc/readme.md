# Министерство образования Республики Беларусь  
## Учреждение образования  
### Брестский Государственный технический университет  
#### Кафедра ИИТ  

---

# Лабораторная работа №1  
## По дисциплине «Общая теория интеллектуальных систем»  
### Тема: «Моделирование температуры объекта»  

---

### Выполнил:  
- Студент 2 курса  
- Группа ИИ-28  
- Деркач Е.В.  

### Проверил:  
- Иванюк Д.С.  

---

**2025**

---

# Цель работы

Разработка и реализация численной модели температурного процесса с использованием языка программирования **C++**.

---

# Общее задание

1. Написать отчет по выполненной лабораторной работе №1 в формате `.md` и через pull request разместить его в каталоге:  
   `trunk/ii0xxyy/task_01/doc` (где `xx` — номер группы, `yy` — номер студента, например `ii02102`).

2. Исходный код программы разместить в каталоге:  
   `trunk/ii0xxyy/task_01/src`.

---

## Task 1. Modeling controlled object

Дано уравнение температуры объекта:

$$
\frac{dy(\tau)}{d\tau} = \frac{u(\tau)}{C} + \frac{Y_0 - y(\tau)}{RC}
$$

где:  
- \(\tau\) — время;  
- \(y(\tau)\) — температура;  
- \(u(\tau)\) — входное тепло;  
- \(Y_0\) — температура помещения;  
- \(C, R\) — постоянные.

Линейная (2) и нелинейная (3) модели:

$$
y_{\tau+1} = a y_{\tau} + b u_{\tau}
$$

$$
y_{\tau+1} = a y_{\tau} - b y_{\tau-1}^2 + c u_{\tau} + d \sin(u_{\tau-1})
$$

Задача — написать программу на **C++**, моделирующую температуру объекта.

---

# Выполнение задания

## Код программы

```cpp
#include <iostream>
#include <cmath>

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Линейная модель" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++) {
        std::cout << "t = " << i << ", y = " << y << std::endl;
        y = nextLinear(a, b, u, y);
    }
}

double nextNonlinear(double a, double b, double c, double d, double u, double uPrev, double y, double yPrev) {
    return a * y - b * (yPrev * yPrev) + c * u + d * sin(uPrev);
}

void simulateNonlinear(double a, double b, double c, double d, double uInitial, int steps) {
    std::cout << "Нелинейная модель" << std::endl;
    double y = 0.0;
    double yPrev = 0.0;
    double u = uInitial;
    double uPrev = uInitial;

    for (int i = 0; i < steps; i++) {
        std::cout << "t = " << i << ", y = " << y << std::endl;
        double yNext = nextNonlinear(a, b, c, d, u, uPrev, y, yPrev);

        yPrev = y;
        y = yNext;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    double a1 = 0.3, b1 = 0.3, u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);

    std::cout << std::endl;

    double a2 = 0.1, b2 = 0.2, c2 = 0.4, d2 = 0.2, u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}
```
```
## Результаты программы

Линейная модель

t = 0, y = 0
t = 1, y = 0.27
t = 2, y = 0.351
t = 3, y = 0.3753
t = 4, y = 0.38259
t = 5, y = 0.384777
t = 6, y = 0.385433
t = 7, y = 0.38563
t = 8, y = 0.385689
t = 9, y = 0.385707
 
Нелинейная модель

t = 0, y = 0
t = 1, y = 0.463471
t = 2, y = 0.509818
t = 3, y = 0.471492
t = 4, y = 0.458637
t = 5, y = 0.464874
t = 6, y = 0.467889
t = 7, y = 0.467039
t = 8, y = 0.466391
t = 9, y = 0.466485