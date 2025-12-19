# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`TemperatureRegulator`](#class_temperature_regulator) | Класс интеллектуального регулятора температуры.

# class `TemperatureRegulator` 

Класс интеллектуального регулятора температуры.

Реализует адаптивный алгоритм управления с защитой от насыщения и ограничением выходного сигнала. Использует дискретную форму ПИД-регулятора с расширенными функциями безопасности.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`TemperatureRegulator`](#class_temperature_regulator_1a6c42c3c0c7f4d4df9cba3ce8b9283d08)`(double gain,double integration_time,double sampling_period,double derivative_time)` | Конструктор регулятора температуры.
`public double `[`computeControl`](#class_temperature_regulator_1ad0c14572c80106b2611fb3217c266e36)`(double temperature_error)` | Расчет управляющего воздействия.
`public void `[`setOutputLimits`](#class_temperature_regulator_1a8e6e73a8af4b1c402a6a42e5a5ce5a1a)`(double min_value,double max_value)` | Установка пределов выходного сигнала.
`public void `[`enableAntiWindup`](#class_temperature_regulator_1a8ccce75332703319b3e3307460b4c0a8)`(bool enabled)` | Включение/выключение защиты от насыщения.
`public void `[`reset`](#class_temperature_regulator_1a6b5d2d9b66ef26266d7d76ec2e80eac8)`()` | Сброс состояния регулятора.
`public double `[`getAccumulatedIntegral`](#class_temperature_regulator_1a1925a8dc1e0348086ed6dcf695920f6c)`() const` | Получение текущего значения интеграла.
`public  `[`~TemperatureRegulator`](#class_temperature_regulator_1acbd1c3baab2d36acb8c8ef477dc99765)`() = default` | Деструктор.

## Members

#### `public  `[`TemperatureRegulator`](#class_temperature_regulator_1a6c42c3c0c7f4d4df9cba3ce8b9283d08)`(double gain,double integration_time,double sampling_period,double derivative_time)` 

Конструктор регулятора температуры.

Инициализирует параметры регулятора и вычисляет внутренние коэффициенты.

#### Parameters
* `gain` Коэффициент усиления (пропорциональная составляющая) 

* `integration_time` Время интегрирования (интегральная составляющая) 

* `sampling_period` Период дискретизации 

* `derivative_time` Время дифференцирования (дифференциальная составляющая)

#### `public double `[`computeControl`](#class_temperature_regulator_1ad0c14572c80106b2611fb3217c266e36)`(double temperature_error)` 

Расчет управляющего воздействия.

Вычисляет управляющий сигнал на основе текущей ошибки температуры с учетом истории ошибок и накопленного интеграла.

#### Parameters
* `temperature_error` Ошибка регулирования (целевая - текущая температура) 

#### Returns
Управляющее воздействие (мощность нагрева/охлаждения)

#### `public void `[`setOutputLimits`](#class_temperature_regulator_1a8e6e73a8af4b1c402a6a42e5a5ce5a1a)`(double min_value,double max_value)` 

Установка пределов выходного сигнала.

Определяет диапазон допустимых значений управляющего воздействия.

#### Parameters
* `min_value` Минимальное значение выходного сигнала 

* `max_value` Максимальное значение выходного сигнала

#### `public void `[`enableAntiWindup`](#class_temperature_regulator_1a8ccce75332703319b3e3307460b4c0a8)`(bool enabled)` 

Включение/выключение защиты от насыщения.

Активация/деактивация защиты интегральной составляющей от накопления при насыщении выходного сигнала.

#### Parameters
* `enabled` true - включить защиту, false - выключить

#### `public void `[`reset`](#class_temperature_regulator_1a6b5d2d9b66ef26266d7d76ec2e80eac8)`()` 

Сброс состояния регулятора.

Обнуляет историю ошибок, накопленный интеграл и сбрасывает выходное значение.

#### `public double `[`getAccumulatedIntegral`](#class_temperature_regulator_1a1925a8dc1e0348086ed6dcf695920f6c)`() const` 

Получение текущего значения интеграла.

#### Returns
Накопленное значение интегральной составляющей

#### `public  `[`~TemperatureRegulator`](#class_temperature_regulator_1acbd1c3baab2d36acb8c8ef477dc99765)`() = default` 

Деструктор.

---

# Functions

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public double `[`linear_model`](#_linear_model_8cpp_1aed03f5bb45375ba8c9d01f3064a10e03)`(double previous_output,double control_input,double feedback_coefficient,double gain_coefficient)` | Линейная модель динамической системы.

## Members

#### `public double `[`linear_model`](#_linear_model_8cpp_1aed03f5bb45375ba8c9d01f3064a10e03)`(double previous_output,double control_input,double feedback_coefficient,double gain_coefficient)` 

Линейная модель динамической системы.

Реализует уравнение линейной модели объекта управления: y(k) = a·y(k-1) + b·u(k). Включает проверки на числовую устойчивость и мягкое ограничение значений.

#### Parameters
* `previous_output` Значение выхода на предыдущем шаге y(k-1) 

* `control_input` Управляющее воздействие на текущем шаге u(k) 

* `feedback_coefficient` Коэффициент обратной связи a 

* `gain_coefficient` Коэффициент усиления по управлению b 

#### Returns
Текущее значение выхода системы y(k)

---

# File Documentation

## file `main.cpp`

**Автор:** [Ваше полное имя]  
**Группа:** [Ваша группа]  
**Дата:** [Текущая дата]  
**Версия:** 4.0 (уникальная реализация)

Консольное приложение для моделирования системы автоматического регулирования температуры. Содержит класс TemperatureRegulator и основной цикл моделирования.

## file `lin_model.h`

**Уникальная версия:** 3.2  
**Дата последнего изменения:** [Текущая дата]

Заголовочный файл линейной модели динамической системы.

## file `lin_model.cpp`

**Автор:** [Ваше имя фамилия]  
**Группа:** [Ваша группа]  
**Дата создания:** [Текущая дата]  
**Уникальный идентификатор:** LM_[уникальный хэш]

Реализация линейной модели объекта управления с расширенными функциями проверки и защиты.

Generated by [Custom Documentation Generator](https://example.com) | Уникальная версия документации 2.1