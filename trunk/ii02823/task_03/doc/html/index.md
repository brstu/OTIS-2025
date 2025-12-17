# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`pid`](#classpid) | Класс PID-регулятора
`struct `[`NonLinearCoeffs`](#struct_non_linear_coeffs) | Структура коэффициентов нелинейной модели объекта управления
`struct `[`pid_coeffs`](#structpid__coeffs) | Структура коэффициентов PID-регулятора

# class `pid` 

Класс PID-регулятора

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`pid`](#classpid_1ae8014e9c3f602dcd6b88686fb917442e)`(const `[`pid_coeffs`](#structpid__coeffs)` & coeffs,double _u,double _e,double __e)` | Конструктор PID-регулятора
`public double `[`process`](#classpid_1a75f23675900ca669c3f12875ce55d78a)`(double e)` | Выполнить шаг PID-регулятора

## Members

#### `public  `[`pid`](#classpid_1ae8014e9c3f602dcd6b88686fb917442e)`(const `[`pid_coeffs`](#structpid__coeffs)` & coeffs,double _u,double _e,double __e)` 

Конструктор PID-регулятора

#### Parameters
* `coeffs` структура коэффициентов 

* `_u` начальное значение управляющего воздействия 

* `_e` предыдущее значение отклонения 

* `__e` предпредыдущее значение отклонения

Инициализирует регулятор с заданными коэффициентами и начальными условиями.

#### Parameters
* `coeffs` структура коэффициентов 

* `_u` начальное значение управляющего воздействия 

* `_e` предыдущее значение отклонения 

* `__e` предпредыдущее значение отклонения

#### `public double `[`process`](#classpid_1a75f23675900ca669c3f12875ce55d78a)`(double e)` 

Выполнить шаг PID-регулятора

#### Parameters
* `e` текущее значение отклонения 

#### Returns
новое управляющее воздействие

Вычисляет новое управляющее воздействие на основе текущей ошибки.

#### Parameters
* `_e` текущее значение отклонения 

#### Returns
новое управляющее воздействие

# struct `NonLinearCoeffs` 

Структура коэффициентов нелинейной модели объекта управления

Содержит параметры, используемые при расчёте выходной величины по нелинейной модели:

* `a` — коэффициент линейной части

* `b` — коэффициент квадратичной нелинейности

* `c` — коэффициент управляющего воздействия

* `d` — коэффициент синусоидальной нелинейности

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public double `[`a`](#struct_non_linear_coeffs_1ad6ff916246dfe8bab31b6f626647a91b) | коэффициент линейной части
`public double `[`b`](#struct_non_linear_coeffs_1aff8f4e829db8595497575683e77681c7) | коэффициент квадратичной нелинейности
`public double `[`c`](#struct_non_linear_coeffs_1adf2974d5f4634c09e97fd6114efb2d9b) | коэффициент управляющего воздействия
`public double `[`d`](#struct_non_linear_coeffs_1a1fea29cf6a6378aeed2600ee88a1bb54) | коэффициент синусоидальной нелинейности

## Members

#### `public double `[`a`](#struct_non_linear_coeffs_1ad6ff916246dfe8bab31b6f626647a91b) 

коэффициент линейной части

#### `public double `[`b`](#struct_non_linear_coeffs_1aff8f4e829db8595497575683e77681c7) 

коэффициент квадратичной нелинейности

#### `public double `[`c`](#struct_non_linear_coeffs_1adf2974d5f4634c09e97fd6114efb2d9b) 

коэффициент управляющего воздействия

#### `public double `[`d`](#struct_non_linear_coeffs_1a1fea29cf6a6378aeed2600ee88a1bb54) 

коэффициент синусоидальной нелинейности

# struct `pid_coeffs` 

Структура коэффициентов PID-регулятора

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const double `[`K`](#structpid__coeffs_1a72db3187cc333a2d93a7d49702cec92e) | коэффициент передачи
`public const double `[`T`](#structpid__coeffs_1aa69708722314150cbd2810cc8b7c8476) | постоянная интегрирования
`public const double `[`Td`](#structpid__coeffs_1a5cc8572ddb54086cc7b97f754b1f86c1) | постоянная дифференцирования
`public const double `[`T0`](#structpid__coeffs_1a9fa8f52e69c498586a22bc748d38fab2) | шаг
`public  `[`pid_coeffs`](#structpid__coeffs_1a1565a55a5421ee3da66debe43db919b8)`(double K,double T,double Td,double T0)` | Конструктор коэффициентов PID-регулятора

## Members

#### `public const double `[`K`](#structpid__coeffs_1a72db3187cc333a2d93a7d49702cec92e) 

коэффициент передачи

#### `public const double `[`T`](#structpid__coeffs_1aa69708722314150cbd2810cc8b7c8476) 

постоянная интегрирования

#### `public const double `[`Td`](#structpid__coeffs_1a5cc8572ddb54086cc7b97f754b1f86c1) 

постоянная дифференцирования

#### `public const double `[`T0`](#structpid__coeffs_1a9fa8f52e69c498586a22bc748d38fab2) 

шаг

#### `public  `[`pid_coeffs`](#structpid__coeffs_1a1565a55a5421ee3da66debe43db919b8)`(double K,double T,double Td,double T0)` 

Конструктор коэффициентов PID-регулятора

#### Parameters
* `K` коэффициент передачи 

* `T` постоянная интегрирования 

* `Td` постоянная дифференцирования 

* `T0` шаг

Инициализирует структуру коэффициентов PID-регулятора.

#### Parameters
* `K` коэффициент передачи 

* `T` постоянная интегрирования 

* `Td` постоянная дифференцирования 

* `T0` шаг

Generated by [Moxygen](https://sourcey.com/moxygen)