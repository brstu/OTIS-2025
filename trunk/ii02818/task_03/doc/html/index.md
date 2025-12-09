---
layout: default
title: PID
---

# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`Model`](#class_model) | Класс, представляющий объект управления (модель).
`class `[`PID`](#class_p_i_d) | Класс цифрового ПИД-регулятора

# class `Model` 

Класс, представляющий объект управления (модель).

Класс реализует линейную и нелинейную модели объекта управления. Используется для тестирования ПИД-регулятора.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`Model`](#class_model_1ab5d4a33e22070b59a4543e6de34199e2)`(double a_val,double b_val,double c_val,double d_val)` | Конструктор класса [Model](#class_model).
`public void `[`init`](#class_model_1a016819d78d29f1533d3351cdcd83b2e5)`(double y0,double y1,double u0,double u1)` | Инициализация начальных условий модели
`public double `[`linearModel`](#class_model_1a947cfcb5e6035d29f0ead62a26fd18de)`(double u)` | Линейная модель объекта управления
`public double `[`nonlinearModel`](#class_model_1ab31570881280566275abef961ed0e68f)`(double u)` | Нелинейная модель объекта управления
`public inline double `[`getCurrentValue`](#class_model_1aa23799a2cfa94ab5b9ac78ec4c5e365c)`() const` | Получение текущего значения модели
`public inline void `[`setCurrentValue`](#class_model_1a1c926807f26dc8c433a5b8a4261c5475)`(double value)` | Установка текущего значения модели

## Members

#### `public  explicit `[`Model`](#class_model_1ab5d4a33e22070b59a4543e6de34199e2)`(double a_val,double b_val,double c_val,double d_val)` 

Конструктор класса [Model](#class_model).

#### Parameters
* `a_val` Коэффициент A (по умолчанию 0.2) 

* `b_val` Коэффициент B (по умолчанию 0.3) 

* `c_val` Коэффициент C (по умолчанию 0.4) 

* `d_val` Коэффициент D (по умолчанию 0.5)

* `a_val` Коэффициент A 

* `b_val` Коэффициент B 

* `c_val` Коэффициент C 

* `d_val` Коэффициент D

#### `public void `[`init`](#class_model_1a016819d78d29f1533d3351cdcd83b2e5)`(double y0,double y1,double u0,double u1)` 

Инициализация начальных условий модели

#### Parameters
* `y0` Начальное значение y[k-2] 

* `y1` Начальное значение y[k-1] 

* `u0` Начальное значение u[k-2] 

* `u1` Начальное значение u[k-1]

#### `public double `[`linearModel`](#class_model_1a947cfcb5e6035d29f0ead62a26fd18de)`(double u)` 

Линейная модель объекта управления

#### Parameters
* `u` Текущее управляющее воздействие 

#### Returns
Текущее значение выхода модели

Уравнение модели: y[k] = a*y[k-1] + b*u[k]

#### Parameters
* `u` Текущее управляющее воздействие 

#### Returns
Текущее значение выхода модели

Реализует разностное уравнение: y[k] = a*y[k-1] + b*u[k]

#### `public double `[`nonlinearModel`](#class_model_1ab31570881280566275abef961ed0e68f)`(double u)` 

Нелинейная модель объекта управления

#### Parameters
* `u` Текущее управляющее воздействие 

#### Returns
Текущее значение выхода модели

Уравнение модели: y[k] = a*y[k-1] - b*y[k-2]*tanh(y[k-2]) + c*u[k] + d*sin(u[k-1]) Включает ограничение выходных значений

#### Parameters
* `u` Текущее управляющее воздействие 

#### Returns
Текущее значение выхода модели

Реализует разностное уравнение: y[k] = a*y[k-1] - b*y[k-2]*tanh(y[k-2]) + c*u[k] + d*sin(u[k-1])

#### `public inline double `[`getCurrentValue`](#class_model_1aa23799a2cfa94ab5b9ac78ec4c5e365c)`() const` 

Получение текущего значения модели

#### Returns
Текущее значение выхода (y[k-1])

#### `public inline void `[`setCurrentValue`](#class_model_1a1c926807f26dc8c433a5b8a4261c5475)`(double value)` 

Установка текущего значения модели

#### Parameters
* `value` Новое значение выхода

# class `PID` 

Класс цифрового ПИД-регулятора

Реализует цифровой ПИД-регулятор с дискретной передаточной функцией. Поддерживает стандартную форму (Пропорционально-Интегрально-Дифференциальный регулятор).

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`PID`](#class_p_i_d_1a17795e8c074bdb9c7952d093571ba6d6)`(double K,double Ti,double Td,double T0)` | Конструктор класса [PID](#class_p_i_d).
`public double `[`calculate`](#class_p_i_d_1a95bd8270c27ddf8cb98a85b68a16211a)`(double setpoint,double current_value)` | Расчет управляющего воздействия
`public void `[`reset`](#class_p_i_d_1af9677e76cb1beffbcf3f54cbc627c530)`()` | Сброс состояния регулятора
`public std::vector< double > `[`getCoefficients`](#class_p_i_d_1a05cc28e1b9efe654681fa29eec5e0663)`() const` | Получение коэффициентов дискретного регулятора
`public void `[`getParameters`](#class_p_i_d_1af1e9df26131257a81b224f0e766dcb34)`(double & K_param,double & Ti_param,double & Td_param) const` | Получение параметров ПИД-регулятора

## Members

#### `public  `[`PID`](#class_p_i_d_1a17795e8c074bdb9c7952d093571ba6d6)`(double K,double Ti,double Td,double T0)` 

Конструктор класса [PID](#class_p_i_d).

#### Parameters
* `K` Коэффициент усиления 

* `Ti` Постоянная времени интегрирования 

* `Td` Постоянная времени дифференцирования 

* `T0` Период дискретизации (по умолчанию 1.0)

Инициализирует коэффициенты дискретного регулятора

#### Parameters
* `K_val` Коэффициент усиления 

* `Ti_val` Постоянная времени интегрирования 

* `Td_val` Постоянная времени дифференцирования 

* `T0_val` Период дискретизации

Рассчитывает коэффициенты дискретного регулятора по формулам: q0 = K*(1 + Td/T0) q1 = -K*(1 + 2*Td/T0 - T0/Ti) q2 = K*Td/T0

#### `public double `[`calculate`](#class_p_i_d_1a95bd8270c27ddf8cb98a85b68a16211a)`(double setpoint,double current_value)` 

Расчет управляющего воздействия

#### Parameters
* `setpoint` Задающее воздействие 

* `current_value` Текущее значение процесса 

#### Returns
Управляющее воздействие

Уравнение регулятора: u[k] = q0*e[k] + q1*e[k-1] + q2*e[k-2] + u[k-1]

#### Parameters
* `setpoint` Задающее воздействие 

* `current_value` Текущее значение процесса 

#### Returns
Управляющее воздействие (ограниченное 0-100%)

Алгоритм расчета:* Вычисление ошибки: e[k] = setpoint - current_value

* Расчет приращения: Δu = q0*e[k] + q1*e[k-1] + q2*e[k-2]

* Новое значение: u[k] = u[k-1] + Δu

* Ограничение значения

#### `public void `[`reset`](#class_p_i_d_1af9677e76cb1beffbcf3f54cbc627c530)`()` 

Сброс состояния регулятора

Обнуляет все накопленные значения (интеграл, предыдущие ошибки и т.д.)

Обнуляет все внутренние переменные регулятора. Используется при перезапуске системы или изменении режима работы.

#### `public std::vector< double > `[`getCoefficients`](#class_p_i_d_1a05cc28e1b9efe654681fa29eec5e0663)`() const` 

Получение коэффициентов дискретного регулятора

#### Returns
Вектор коэффициентов [q0, q1, q2]

#### `public void `[`getParameters`](#class_p_i_d_1af1e9df26131257a81b224f0e766dcb34)`(double & K_param,double & Ti_param,double & Td_param) const` 

Получение параметров ПИД-регулятора

#### Parameters
* `K_param` Коэффициент усиления 

* `Ti_param` Постоянная времени интегрирования 

* `Td_param` Постоянная времени дифференцирования

Generated by [Moxygen](https://sourcey.com/moxygen)
