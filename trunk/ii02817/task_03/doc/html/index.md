# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`PIDController`](#class_p_i_d_controller) | Дискретный ПИД-регулятор
`class `[`PlantModel`](#class_plant_model) | Модель объекта управления с линейной и нелинейной динамикой

# class `PIDController` 

Дискретный ПИД-регулятор

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`PIDController`](#class_p_i_d_controller_1a970b2fb3c3d8517db45b066030ea1723)`() = default` | Конструктор по умолчанию
`public  `[`PIDController`](#class_p_i_d_controller_1a85a66025d7a1a8c040036feaa63faf05)`(double K,double Ti,double Td,double T0)` | Параметризованный конструктор
`public void `[`setParameters`](#class_p_i_d_controller_1ac43ca81ca1c80f123773dc0296283514)`(double K,double Ti,double Td,double T0)` | Установка параметров ПИД-регулятора
`public void `[`setLimits`](#class_p_i_d_controller_1a2f11970d0216de3802e81a8fe84f14e8)`(double u_min,double u_max)` | Установка ограничений управления
`public void `[`reset`](#class_p_i_d_controller_1ab6adfbffa30414f0a83b95ba999a2fea)`()` | Сброс состояния регулятора
`public double `[`calculate`](#class_p_i_d_controller_1af31656b67630f25fe8b85eefa24fe956)`(double e)` | Вычисление управляющего воздействия
`public std::vector< double > `[`getCoefficients`](#class_p_i_d_controller_1a3f6a05e6457da67ca575c0da2280dcba)`() const` | Получение коэффициентов регулятора

## Members

#### `public  `[`PIDController`](#class_p_i_d_controller_1a970b2fb3c3d8517db45b066030ea1723)`() = default` 

Конструктор по умолчанию

#### `public  `[`PIDController`](#class_p_i_d_controller_1a85a66025d7a1a8c040036feaa63faf05)`(double K,double Ti,double Td,double T0)` 

Параметризованный конструктор

#### Parameters
* `K` Коэффициент усиления 

* `Ti` Постоянная интегрирования 

* `Td` Постоянная дифференцирования 

* `T0` Шаг квантования

#### `public void `[`setParameters`](#class_p_i_d_controller_1ac43ca81ca1c80f123773dc0296283514)`(double K,double Ti,double Td,double T0)` 

Установка параметров ПИД-регулятора

#### Parameters
* `K` Коэффициент усиления 

* `Ti` Постоянная интегрирования 

* `Td` Постоянная дифференцирования 

* `T0` Шаг квантования

#### `public void `[`setLimits`](#class_p_i_d_controller_1a2f11970d0216de3802e81a8fe84f14e8)`(double u_min,double u_max)` 

Установка ограничений управления

#### Parameters
* `u_min` Минимальное значение управления 

* `u_max` Максимальное значение управления

#### `public void `[`reset`](#class_p_i_d_controller_1ab6adfbffa30414f0a83b95ba999a2fea)`()` 

Сброс состояния регулятора

#### `public double `[`calculate`](#class_p_i_d_controller_1af31656b67630f25fe8b85eefa24fe956)`(double e)` 

Вычисление управляющего воздействия

#### Parameters
* `e` Текущая ошибка (задание - измерение) 

#### Returns
Управляющее воздействие

#### `public std::vector< double > `[`getCoefficients`](#class_p_i_d_controller_1a3f6a05e6457da67ca575c0da2280dcba)`() const` 

Получение коэффициентов регулятора

#### Returns
Вектор коэффициентов [q0, q1, q2]

# class `PlantModel` 

Модель объекта управления с линейной и нелинейной динамикой

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`PlantModel`](#class_plant_model_1aa43bd77e2783d08d0e23afd69fa0b8db)`() = default` | Конструктор по умолчанию
`public  `[`PlantModel`](#class_plant_model_1a52ef4f497e9231fd8316574a2f0d4d57)`(double a,double b,double c,double d)` | Параметризованный конструктор
`public void `[`setParameters`](#class_plant_model_1a23e795fe4f0351117bdba4a197688c40)`(double a,double b,double c,double d)` | Установка параметров модели
`public void `[`setState`](#class_plant_model_1a25e1496652f7d97c9c93c35bb18eb95d)`(double tcurr,double tprev,double ucurr,double uprev)` | Установка состояния модели
`public double `[`getOutput`](#class_plant_model_1af76e6d3c9e05d6f7c0c4b847acfe49be)`() const` | Получение текущего выхода модели
`public double `[`linearStep`](#class_plant_model_1a5aba471744e92f4e93abdaacaa6bd951)`(double u)` | Линейная модель на один шаг
`public double `[`nonlinearStep`](#class_plant_model_1ac9799cb700d1f26b4dd8758d34a5dde9)`(double u)` | Нелинейная модель на один шаг
`public std::vector< double > `[`linear`](#class_plant_model_1ad7733a467a1d833967a6cc3b48731722)`(int steps) const` | Линейная модель на несколько шагов
`public std::vector< double > `[`nonlinear`](#class_plant_model_1abadb2876a8862aa167d8f1acb3523cbb)`(int steps) const` | Нелинейная модель на несколько шагов

## Members

#### `public  `[`PlantModel`](#class_plant_model_1aa43bd77e2783d08d0e23afd69fa0b8db)`() = default` 

Конструктор по умолчанию

#### `public  `[`PlantModel`](#class_plant_model_1a52ef4f497e9231fd8316574a2f0d4d57)`(double a,double b,double c,double d)` 

Параметризованный конструктор

#### Parameters
* `a` Коэффициент a 

* `b` Коэффициент b 

* `c` Коэффициент c 

* `d` Коэффициент d

#### `public void `[`setParameters`](#class_plant_model_1a23e795fe4f0351117bdba4a197688c40)`(double a,double b,double c,double d)` 

Установка параметров модели

#### Parameters
* `a` Коэффициент a 

* `b` Коэффициент b 

* `c` Коэффициент c 

* `d` Коэффициент d

#### `public void `[`setState`](#class_plant_model_1a25e1496652f7d97c9c93c35bb18eb95d)`(double tcurr,double tprev,double ucurr,double uprev)` 

Установка состояния модели

#### Parameters
* `tcurr` Текущее значение выходной переменной 

* `tprev` Предыдущее значение выходной переменной 

* `ucurr` Текущее значение входной переменной 

* `uprev` Предыдущее значение входной переменной

#### `public double `[`getOutput`](#class_plant_model_1af76e6d3c9e05d6f7c0c4b847acfe49be)`() const` 

Получение текущего выхода модели

#### Returns
Текущее значение выходной переменной

#### `public double `[`linearStep`](#class_plant_model_1a5aba471744e92f4e93abdaacaa6bd951)`(double u)` 

Линейная модель на один шаг

#### Parameters
* `u` Входное воздействие 

#### Returns
Новое значение выходной переменной

#### `public double `[`nonlinearStep`](#class_plant_model_1ac9799cb700d1f26b4dd8758d34a5dde9)`(double u)` 

Нелинейная модель на один шаг

#### Parameters
* `u` Входное воздействие 

#### Returns
Новое значение выходной переменной

#### `public std::vector< double > `[`linear`](#class_plant_model_1ad7733a467a1d833967a6cc3b48731722)`(int steps) const` 

Линейная модель на несколько шагов

#### Parameters
* `steps` Количество шагов 

#### Returns
Вектор значений выходной переменной

#### `public std::vector< double > `[`nonlinear`](#class_plant_model_1abadb2876a8862aa167d8f1acb3523cbb)`(int steps) const` 

Нелинейная модель на несколько шагов

#### Parameters
* `steps` Количество шагов 

#### Returns
Вектор значений выходной переменной

Generated by [Moxygen](https://sourcey.com/moxygen)