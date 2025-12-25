# PID Temperature Control System

## Summary

| Members | Descriptions |
|---------|--------------|
| `double linearModel(double y, double u)` | Линейная модель объекта управления. |
| `double nonlinearModel(double y, double u, double y_pred, double u_pred)` | Нелинейная модель объекта управления. |
| `std::vector<double> simulatePIDRegulatorUsingNonLinearModel(double w, int steps)` | Выполняет симуляцию системы управления с ПИД-регулятором и нелинейной моделью объекта. |
| `class PIDController` | Класс ПИД-регулятора для управления температурой. |
| `PIDController::PIDController(double p, double i, double d, double min, double max)` | Конструктор ПИД-регулятора. |
| `double PIDController::calculate(double measured_value, double dt)` | Вычисляет управляющее воздействие. |
| `void PIDController::setSetpoint(double value)` | Устанавливает заданное значение. |
| `double PIDController::getSetpoint() const` | Возвращает текущее заданное значение. |
| `void PIDController::reset()` | Сбрасывает интегральную составляющую и предыдущую ошибку. |
| `void PIDController::setParameters(double p, double i, double d)` | Устанавливает новые коэффициенты ПИД-регулятора. |
| `double temperatureModel(double current_temp, double control_signal, double dt, double room_temp)` | Модель объекта управления температурой. |

## Functions

### `double linearModel(double y, double u)`

Линейная модель объекта управления первого порядка.

**Parameters:**
- `y` - текущее значение выхода объекта
- `u` - текущее значение управления

**Returns:**
следующее значение выхода объекта

**Mathematical Model:**
```
y[k+1] = a * y[k] + b * u[k]
```
где `a` и `b` - коэффициенты модели.

**Example:**
```cpp
double y_next = linearModel(y_current, u_current);
```

### `double nonlinearModel(double y, double u, double y_pred, double u_pred)`

Нелинейная модель объекта управления второго порядка с квадратичной и синусоидальной нелинейностями.

**Parameters:**
- `y` - текущее значение выхода объекта
- `u` - текущее значение управления
- `y_pred` - предыдущее значение выхода объекта
- `u_pred` - предыдущее значение управления

**Returns:**
следующее значение выхода объекта

**Mathematical Model:**
```
y[k+1] = a * y[k] + b * y[k]² + c * u[k] + d * sin(u[k-1])
```
где `a`, `b`, `c`, `d` - коэффициенты модели.

**Example:**
```cpp
double y_next = nonlinearModel(y_curr, u_curr, y_prev, u_prev);
```

### `std::vector<double> simulatePIDRegulatorUsingNonLinearModel(double w, int steps)`

Выполняет симуляцию системы управления с ПИД-регулятором и нелинейной моделью объекта.

**Parameters:**
- `w` - заданное значение (уставка)
- `steps` - количество шагов симуляции

**Returns:**
вектор значений выхода объекта на каждом шаге симуляции

**Algorithm:**
1. Инициализация ПИД-регулятора с заданными коэффициентами
2. Для каждого шага симуляции:
   - Вычисление ошибки регулирования
   - Расчет управляющего сигнала ПИД-регулятором
   - Обновление состояния объекта через нелинейную модель
   - Сохранение текущего значения выхода

**Example:**
```cpp
std::vector<double> output_history = simulatePIDRegulatorUsingNonLinearModel(75.0, 1000);
```

### `PIDController::PIDController(double p, double i, double d, double min, double max)`

Конструктор класса ПИД-регулятора.

**Parameters:**
- `p` - пропорциональный коэффициент (Kp)
- `i` - интегральный коэффициент (Ki)
- `d` - дифференциальный коэффициент (Kd)
- `min` - минимальное значение выходного сигнала (по умолчанию 0)
- `max` - максимальное значение выходного сигнала (по умолчанию 100)

**Initial Values:**
- Заданное значение (setpoint) инициализируется нулем
- Интегральная составляющая обнуляется
- Предыдущая ошибка устанавливается в ноль

**Example:**
```cpp
PIDController pid(2.5, 0.5, 1.0, 0.0, 100.0);
```

### `double PIDController::calculate(double measured_value, double dt)`

Вычисляет управляющее воздействие на основе текущей ошибки регулирования.

**Parameters:**
- `measured_value` - измеренное значение процесса
- `dt` - временной шаг в секундах

**Returns:**
управляющее воздействие (ограниченное заданными пределами)

**Algorithm:**
1. Вычисление ошибки: `error = setpoint - measured_value`
2. Пропорциональная составляющая: `P = Kp * error`
3. Интегральная составляющая: `I = Ki * integral` (с накоплением)
4. Дифференциальная составляющая: `D = Kd * (error - prev_error) / dt`
5. Суммирование: `output = P + I + D`
6. Ограничение выходного сигнала
7. Обновление предыдущей ошибки

**Example:**
```cpp
double control_signal = pid.calculate(current_temperature, 0.1);
```

### `void PIDController::setSetpoint(double value)`

Устанавливает новое заданное значение для регулятора.

**Parameters:**
- `value` - новое заданное значение

**Note:**
Изменение уставки не сбрасывает интегральную составляющую.

**Example:**
```cpp
pid.setSetpoint(80.0);
```

### `double PIDController::getSetpoint() const`

Возвращает текущее заданное значение регулятора.

**Returns:**
текущая уставка регулятора

**Example:**
```cpp
double current_setpoint = pid.getSetpoint();
```

### `void PIDController::reset()`

Сбрасывает внутреннее состояние регулятора.

**Effects:**
- Обнуляет интегральную составляющую
- Сбрасывает предыдущую ошибку в ноль

**Use Cases:**
- При запуске системы
- При изменении режима работы
- При возникновении аварийной ситуации

**Example:**
```cpp
pid.reset();
```

### `void PIDController::setParameters(double p, double i, double d)`

Устанавливает новые коэффициенты ПИД-регулятора.

**Parameters:**
- `p` - новый пропорциональный коэффициент
- `i` - новый интегральный коэффициент
- `d` - новый дифференциальный коэффициент

**Note:**
Изменение коэффициентов не сбрасывает накопленный интеграл.

**Example:**
```cpp
pid.setParameters(3.0, 0.8, 1.2);
```

### `double temperatureModel(double current_temp, double control_signal, double dt, double room_temp)`

Модель объекта управления температурой (нагреватель/охладитель).

**Parameters:**
- `current_temp` - текущая температура объекта
- `control_signal` - управляющий сигнал (0-100%)
- `dt` - временной шаг
- `room_temp` - температура окружающей среды (по умолчанию 20°C)

**Returns:**
новая температура объекта

**Mathematical Model:**
```
dT/dt = (P_heating - (T - T_room) / τ) * dt
```
где:
- `P_heating = max_power * (control_signal / 100)`
- `τ` - постоянная времени системы
- `max_power` - максимальная мощность нагрева

**Example:**
```cpp
double new_temp = temperatureModel(current_temp, control_signal, 0.1, 25.0);
```

## Class Diagram

```
┌─────────────────────────┐
│     PIDController       │
├─────────────────────────┤
│ - Kp: double            │
│ - Ki: double            │
│ - Kd: double            │
│ - setpoint: double      │
│ - integral: double      │
│ - prev_error: double    │
│ - output_min: double    │
│ - output_max: double    │
├─────────────────────────┤
│ + PIDController()       │
│ + calculate(): double   │
│ + setSetpoint(): void   │
│ + getSetpoint(): double │
│ + reset(): void         │
│ + setParameters(): void │
└─────────────────────────┘
```