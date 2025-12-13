# Лабораторная работа №1  
## Моделирование температуры управляемого объекта

**Студент:** Вабищевич И.В.  
**Группа:** ИИ-28  
**Преподаватель:** Иванюк Д.С.  
**Год:** 2025  
**Университет:** БрГТУ, кафедра ИИТ

---

## Цель работы

Разработать программу на C++, моделирующую изменение температуры объекта
с использованием линейной и нелинейной математических моделей.

---

## Математическая модель  

Исходный процесс изменения температуры объекта можно представить
дифференциальным уравнением:

\[
\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC}
\]

где:

- \( y(\tau) \) — температура объекта,
- \( u(\tau) \) — входной нагрев,
- \( Y_0 \) — температура окружающей среды,
- \( C, R \) — параметры системы.

---

## Дискретные модели

Для вычислений используются две формы уравнений:

### Линейная модель:
\[
y_{\tau+1} = a y_\tau + b u_\tau
\]

### Нелинейная модель:
\[
y_{\tau+1}= a y_\tau - b y_\tau^2 + c u_\tau + d \sin(u_\tau)
\]

---

## Описание программы

Программа:

- запрашивает начальные данные и коэффициенты,
- выполняет расчёт температуры на заданном количестве шагов,
- выводит результаты для обеих моделей.

---

## Исходный код

```cpp
#include <iostream>
#include <cmath>

double linear(double y, double u, double a, double b);
double non_linear(double y, double u, double a, double b, double c, double d);

int main()
{
    double u;
    double y;
    std::cout << "Enter u(input warm) and y(input temperature): " << std::endl;
    std::cin >> u >> y;

    double a;
    double b;
    double c;
    double d;
    std::cout << "Enter a,b,c,d(some constants): " << std::endl;
    std::cin >> a >> b >> c >> d;

    int count;
    std::cout << "Enter the number of steps: " << std::endl;
    std::cin >> count;

    double yl = y;
    double ynl = y;

    for (int i = 0; i < count; i++)
    {
        yl = linear(yl, u, a, b);
        ynl = non_linear(ynl, u, a, b, c, d);

        std::cout << "Step " << i + 1
                  << ": Linear = " << yl
                  << ", Nonlinear = " << ynl << "\n";
    }

    return 0;
}

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double non_linear(double y, double u, double a, double b, double c, double d)
{
    return a * y - b * y * y + c * u + d * std::sin(u);
}
