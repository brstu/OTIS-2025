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
<p align="right">Деркач Е.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">2025</p>
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

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:
2. Исходный код программы разместить в каталоге:  
   `trunk/ii0xxyy/task_01/src`.

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)
---

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.
## Task 1. Modeling controlled object

After transformation, we get these linear (2) and nonlinear (3) models:
Дано уравнение температуры объекта:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)
$$
\frac{dy(\tau)}{d\tau} = \frac{u(\tau)}{C} + \frac{Y_0 - y(\tau)}{RC}
$$

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.
где:  
- \(\tau\) — время;  
- \(y(\tau)\) — температура;  
- \(u(\tau)\) — входное тепло;  
- \(Y_0\) — температура помещения;  
- \(C, R\) — постоянные.

Task is to write program (**C++**), which simulates this object temperature.
Линейная (2) и нелинейная (3) модели:

<hr>
$$
y_{\tau+1} = a y_{\tau} + b u_{\tau}
$$

$$
y_{\tau+1} = a y_{\tau} - b y_{\tau-1}^2 + c u_{\tau} + d \sin(u_{\tau-1})
$$

Задача — написать программу на **C++**, моделирующую температуру объекта.

---

# Выполнение задания

# Выполнение задания #

## Код программы

```cpp 
#include <iostream>
#include <cmath>
#include <locale>
#include <stdexcept>

double nextLinear(double a, double b, double u, double y)
{
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps)
{
    if (steps <= 0) {
        throw std::invalid_argument("Number of steps must be positive");
    }
    
    std::cout << "Линейная модель" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << y << std::endl;
        y = nextLinear(a, b, u, y);
    }
}

double nextNonlinear(double a, double b, double c, double d, double u, double uPrev, double y, double yPrev)
{
    return a * y - b * (yPrev * yPrev) + c * u + d * sin(uPrev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps)
{
    if (steps <= 0) {
        throw std::invalid_argument("Number of steps must be positive");
    }
    
    std::cout << "Нелинейная модель" << std::endl;
    double y = 0.0;
    double yPrev = 0.0;
    double uPrev = u;

    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << y << std::endl;
        double yNext = nextNonlinear(a, b, c, d, u, uPrev, y, yPrev);

        yPrev = y;
        y = yNext;
    }
}

int main()
{
    try
    {
        std::locale rus_locale("ru_RU.UTF-8");
        std::cout.imbue(rus_locale);
    }
    catch (const std::runtime_error &)
    {
        std::cerr << "Russian locale ru_RU.UTF-8 not available, using default locale." << std::endl;
    }

    try {
        double a1 = 0.3, b1 = 0.3, u1 = 0.9;
        int n1 = 10;
        simulateLinear(a1, b1, u1, n1);

        std::cout << std::endl;

        double a2 = 0.1, b2 = 0.2, c2 = 0.4, d2 = 0.2, u2 = 0.8;
        int n2 = 10;
        simulateNonlinear(a2, b2, c2, d2, u2, n2);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```
```