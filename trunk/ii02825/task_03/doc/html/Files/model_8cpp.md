---
title: src/model.cpp
summary: Реализация линейной и нелинейной динамической модели объекта управления. 

---

# src/model.cpp

Реализация линейной и нелинейной динамической модели объекта управления.  [More...](#detailed-description)

## Functions

|                | Name           |
| -------------- | -------------- |
| double | **[linear](Files/model_8cpp.md#function-linear)**(double y, double u, double a, double b)<br>Линейная модель объекта.  |
| double | **[non_linear](Files/model_8cpp.md#function-non-linear)**(double y, double u, double a, double b, double c, double d)<br>Нелинейная модель объекта.  |

## Detailed Description

Реализация линейной и нелинейной динамической модели объекта управления. 


# 
## Линейная модель

Линейная модель описывает поведение объекта по разностному уравнению:   \[    y(k+1) = a \cdot y(k) + b \cdot u(k)
\]


# 
## Нелинейная модель

Нелинейная модель учитывает квадратичный член и синусоиду:   \[    y(k+1) = a \cdot y(k) - b \cdot y(k)^2 + c \cdot u(k) + d \cdot \sin(u(k))
\]


## Functions Documentation

### function linear

```cpp
double linear(
    double y,
    double u,
    double a,
    double b
)
```

Линейная модель объекта. 

**Parameters**: 

  * **y** Текущее значение состояния объекта. 
  * **u** Управляющее воздействие. 
  * **a** Коэффициент влияния предыдущего состояния. 
  * **b** Коэффициент влияния управляющего воздействия.


**Return**: Новое значение параметра объекта. 

Линейная модель динамики объекта.

Функция рассчитывает новое состояние системы на основе текущего значения ( y ) и управляющего воздействия ( u ).


### function non_linear

```cpp
double non_linear(
    double y,
    double u,
    double a,
    double b,
    double c,
    double d
)
```

Нелинейная модель объекта. 

**Parameters**: 

  * **y** Текущее состояние объекта. 
  * **u** Управляющий сигнал. 
  * **a** Коэффициент сохранения состояния. 
  * **b** Коэффициент квадратичного влияния состояния. 
  * **c** Коэффициент влияния управляющего сигнала. 
  * **d** Коэффициент синусоидального влияния.


**Return**: Новое значение состояния системы. 

Нелинейная модель динамики объекта.

Учитывает нелинейные эффекты насыщения и колебательность управления:

\[y(k+1) = a \cdot y - b \cdot y^2 + c \cdot u + d \cdot \sin(u)
\]где:

* ( a ) — влияние предыдущего состояния,
* ( b ) — коэффициент нелинейного затухания,
* ( c ) — коэффициент влияния управляющего воздействия,
* ( d ) — амплитуда синусоидального воздействия.




## Source code

```cpp


#include "model.h"
#include <cmath>

double linear(double y, double u, double a, double b)
{
    return a * y + b * u;
}

double non_linear(double y, double u, double a, double b, double c, double d)
{
    return a * y - b * y * y + c * u + d * std::sin(u);
}
```


-------------------------------

Updated on 2025-11-26 at 11:50:51 +0300
