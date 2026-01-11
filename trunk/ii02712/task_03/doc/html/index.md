# Summary

| Members | Descriptions |
|---------|--------------|
| `double linearModel(double y, double u)` | Линейная модель объекта управления. |
| `double nonlinearModel(double y, double u, double y_pred, double u_pred)` | Нелинейная модель объекта управления. |
| `std::vector<double> simulatePIDRegulatorUsingNonLinearModel(double w, int steps)` | Выполняет симуляцию системы управления с ПИД-регулятором и нелинейной моделью объекта. |

# Functions

## `double linearModel(double y, double u)`

Линейная модель объекта управления.

**Parameters:**
- `y` - текущее значение выхода объекта
- `u` - текущее значение управления

**Returns:**
следующее значение выхода объекта

## `double nonlinearModel(double y, double u, double y_pred, double u_pred)`

Нелинейная модель объекта управления.

**Parameters:**
- `y` - текущее значение выхода объекта
- `u` - текущее значение управления
- `y_pred` - предыдущее значение выхода объекта
- `u_pred` - предыдущее значение управления

**Returns:**
следующее значение выхода объекта

## `std::vector<double> simulatePIDRegulatorUsingNonLinearModel(double w, int steps)`

Выполняет симуляцию системы управления с ПИД-регулятором и нелинейной моделью объекта.

**Parameters:**
- `w` - заданное значение (уставка)
- `steps` - количество шагов симуляции

**Returns:**
вектор значений выхода объекта на каждом шаге симуляции