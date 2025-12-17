---
title: PID
summary: Класс дискретного ПИД-регулятора. 

---

# PID



Класс дискретного ПИД-регулятора.  [More...](#detailed-description)


`#include <pid.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PID](Classes/class_p_i_d.md#function-pid)**(double K_, double T_, double Td_, double T0_)<br>Конструктор PID-регулятора.  |
| double | **[compute](Classes/class_p_i_d.md#function-compute)**(double e)<br>Вычисляет новое управляющее воздействие.  |

## Detailed Description

```cpp
class PID;
```

Класс дискретного ПИД-регулятора. 

Реализует дискретный [PID](Classes/class_p_i_d.md) с использованием разностного уравнения. 

## Public Functions Documentation

### function PID

```cpp
PID(
    double K_,
    double T_,
    double Td_,
    double T0_
)
```

Конструктор PID-регулятора. 

**Parameters**: 

  * **K** Усиление 
  * **T** Время интегрирования 
  * **Td** Время дифференцирования 
  * **T0** Шаг моделирования 


### function compute

```cpp
double compute(
    double e
)
```

Вычисляет новое управляющее воздействие. 

**Parameters**: 

  * **e** Текущая ошибка 


**Return**: Управляющее воздействие 

-------------------------------

Updated on 2025-11-26 at 11:50:51 +0300