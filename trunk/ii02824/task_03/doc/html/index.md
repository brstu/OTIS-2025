# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`pid1`](#classpid1) | Класс PID-регулятора
`struct `[`NonLinearCoeffs`](#struct_non_linear_coeffs) | Структура коэффициентов нелинейной модели объекта управления
`struct `[`pid1_coeffs`](#structpid1__coeffs) | Структура коэффициентов PID-регулятора


# class `pid1` 


Класс PID-регулятора


## Summary


 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`pid1`](#classpid1_1ae8014e9c3f602dcd6b88686fb917442e)`(const `[`pid1_coeffs`](#structpid1__coeffs)` & coeffs,double _u,double _e,double __e)` | Конструктор PID-регулятора
`public double `[`process`](#classpid1_1a75f23675900ca669c3f12875ce55d78a)`(double e)` | Выполнить шаг PID-регулятора


## Members


#### `public double `[`process`](#classpid1_1a75f23675900ca669c3f12875ce55d78a)`(double e)` 


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


* `a1` — коэффициент линейной части


* `b1` — коэффициент квадратичной нелинейности


* `c1` — коэффициент управляющего воздействия


* `d1` — коэффициент синусоидальной нелинейности


## Summary


 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public double `[`a1`](#struct_non_linear_coeffs_1ad6ff916246dfe8bab31b6f626647a91b) | коэффициент линейной части
`public double `[`b1`](#struct_non_linear_coeffs_1aff8f4e829db8595497575683e77681c7) | коэффициент квадратичной нелинейности
`public double `[`c1`](#struct_non_linear_coeffs_1adf2974d5f4634c09e97fd6114efb2d9b) | коэффициент управляющего воздействия
`public double `[`d1`](#struct_non_linear_coeffs_1a1fea29cf6a6378aeed2600ee88a1bb54) | коэффициент синусоидальной нелинейности


## Members


#### `public double `[`a1`](#struct_non_linear_coeffs_1ad6ff916246dfe8bab31b6f626647a91b) 


коэффициент линейной части


#### `public double `[`b1`](#struct_non_linear_coeffs_1aff8f4e829db8595497575683e77681c7) 


коэффициент квадратичной нелинейности


#### `public double `[`c1`](#struct_non_linear_coeffs_1adf2974d5f4634c09e97fd6114efb2d9b) 


коэффициент управляющего воздействия


#### `public double `[`d1`](#struct_non_linear_coeffs_1a1fea29cf6a6378aeed2600ee88a1bb54) 


коэффициент синусоидальной нелинейности


# struct `pid1_coeffs` 


Структура коэффициентов PID-регулятора


## Summary


 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const double `[`K1`](#structpid1__coeffs_1a72db3187cc333a2d93a7d49702cec92e) | коэффициент передачи
`public const double `[`T1`](#structpid1__coeffs_1aa69708722314150cbd2810cc8b7c8476) | постоянная интегрирования
`public const double `[`Td1`](#structpid1__coeffs_1a5cc8572ddb54086cc7b97f754b1f86c1) | постоянная дифференцирования
`public const double `[`T01`](#structpid1__coeffs_1a9fa8f52e69c498586a22bc748d38fab2) | шаг
`public  `[`pid1_coeffs`](#structpid1__coeffs_1a1565a55a5421ee3da66debe43db919b8)`(double K1,double T1,double Td1,double T01)` | Конструктор коэффициентов PID-регулятора


## Members


#### `public const double `[`K1`](#structpid1__coeffs_1a72db3187cc333a2d93a7d49702cec92e) 


коэффициент передачи


#### `public const double `[`T1`](#structpid1__coeffs_1aa69708722314150cbd2810cc8b7c8476) 


постоянная интегрирования


#### `public const double `[`Td1`](#structpid1__coeffs_1a5cc8572ddb54086cc7b97f754b1f86c1) 


постоянная дифференцирования


#### `public const double `[`T01`](#structpid1__coeffs_1a9fa8f52e69c498586a22bc748d38fab2) 


шаг


#### `public  `[`pid1_coeffs`](#structpid1__coeffs_1a1565a55a5421ee3da66debe43db919b8)`(double K1,double T1,double Td1,double T01)` 


Конструктор коэффициентов PID-регулятора


#### Parameters
* `K1` коэффициент передачи 


* `T1` постоянная интегрирования 


* `Td1` постоянная дифференцирования 


* `T01` шаг


Инициализирует структуру коэффициентов PID-регулятора.


#### Parameters
* `K1` коэффициент передачи 


* `T1` постоянная интегрирования 


* `Td1` постоянная дифференцирования 


* `T01` шаг