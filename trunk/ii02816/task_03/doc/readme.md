# Лабораторная работа №3: Моделирование ПИД-регулятора для теплового объекта

**Министерство образования Республики Беларусь**  
**Учреждение образования «Брестский Государственный технический университет»**  
**Кафедра ИИТ**

---

**Лабораторная работа №3**  
**По дисциплине «Общая теория интеллектуальных систем»**  
**Тема: «Моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса»**

---

**Выполнил:**  
Студент 2 курса  
Группы ИИ-28/24  
Литвинчук И.М.

**Проверил:**  
Дворанинович Д.А.

---

**Брест 2025**

---

## Содержание
1. [Цель работы](#цель-работы)
2. [Теоретические сведения](#теоретические-сведения)
3. [Реализация программы](#реализация-программы)
4. [Структура проекта](#структура-проекта)
5. [Результаты работы](#результаты-работы)
6. [Документация](#документация)
7. [Тестирование](#тестирование)
8. [Выводы](#выводы)

---

## Цель работы

Разработка и моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса. Исследование влияния параметров регулятора на качество управления линейной и нелинейной моделями объекта.

---

## Теоретические сведения

### Структура системы автоматического управления

Система с обратной связью включает:
- **w(t)** — задающее воздействие
- **u(t)** — управляющее воздействие
- **y(t)** — выходная переменная
- **e(t) = w(t) - y(t)** — ошибка управления

### Уравнение ПИД-регулятора

Идеализированное уравнение непрерывного ПИД-регулятора:
u(t) = K * [e(t) + 1/T * ∫e(τ)dτ + Td * de(t)/dt]


где:
- **K** — коэффициент усиления
- **T** — постоянная времени интегрирования
- **Td** — постоянная времени дифференцирования

### Дискретная реализация

Для реализации на компьютере используется дискретная форма:
u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)


где:
- **q0 = K * (1 + T0/T + Td/T0)**
- **q1 = -K * (1 + 2*Td/T0)**
- **q2 = K * Td/T0**
- **T0** — шаг квантования

---

## Реализация программы

### Основные компоненты

#### 1. Класс PIDController (`pid.h`, `pid.cpp`)

```cpp
/**
 * @class PIDController
 * @brief Реализация дискретного ПИД-регулятора
 */
class PIDController {
private:
    double K, T, Td, T0;  // Параметры регулятора
    double q0, q1, q2;    // Коэффициенты дискретной формы
    double u_prev;        // Предыдущее управляющее воздействие
    double e_prev[2];     // Предыдущие ошибки
    
public:
    PIDController(double K, double T, double Td, double T0);
    double calculate(double setpoint, double current_value);
    void reset();
};

Класс ProcessModel (model.h, model.cpp)
/**
 * @class ProcessModel
 * @brief Модель объекта управления теплового класса
 */
class ProcessModel {
private:
    std::vector<double> params;  // Параметры модели
    double y_prev;               // Предыдущее значение выхода
    
public:
    ProcessModel(const std::vector<double>& params, double initial_value);
    double linearModel(double u);
    double nonlinearModel(double u);
    void setInitialValue(double value);
};
. Главная программа (lab3main.cpp)
#include <iostream>
#include <vector>
#include <fstream>
#include "pid.h"
#include "model.h"
#include "plot_utils.h"

std::vector<double> simulateSystem(PIDController& pid, ProcessModel& process, 
                                  const std::vector<double>& setpoints, bool use_nonlinear = false) {
    std::vector<double> results;
    
    for (double setpoint : setpoints) {
        double current_value = (results.empty()) ? 0.0 : results.back();
        double control_signal = pid.calculate(setpoint, current_value);
        
        double new_value;
        if (use_nonlinear) {
            new_value = process.nonlinearModel(control_signal);
        } else {
            new_value = process.linearModel(control_signal);
        }
        
        results.push_back(new_value);
    }
    
    return results;
}

int main() {
    setlocale(LC_ALL, "");
    std::vector<double> model_params = {0.85, 0.01, 0.15, 0.01};
    ProcessModel process(model_params, 10.0);
    
    double K = 0.8;   
    double T = 4.0;   
    double Td = 0.05;  
    double T0 = 1.0;  
    
    PIDController pid(K, T, Td, T0);
    std::vector<double> setpoints(100, 20.0);
    
    // Симуляция линейной модели
    auto linear_results = simulateSystem(pid, process, setpoints, false);
    
    pid.reset();
    process.setInitialValue(0.0);
    
    // Симуляция нелинейной модели
    auto nonlinear_results = simulateSystem(pid, process, setpoints, true);
    
    // Сохранение в CSV файл
    std::ofstream csv_file("simulation_results.csv");
    csv_file << "Step,Setpoint,Linear_Output,Nonlinear_Output\n";
    
    for (size_t i = 0; i < setpoints.size(); ++i) {
        csv_file << i << "," 
                 << setpoints[i] << "," 
                 << linear_results[i] << "," 
                 << nonlinear_results[i] << "\n";
    }
    csv_file.close();
    
    std::cout << "Simulation completed. Results saved to simulation_results.csv" << std::endl;
    
    // Генерация визуализации
    generatePythonPlotScript();
    
    return 0;
}
 Утилиты визуализации (plot_utils.h, plot_utils.cpp)
 void generatePythonPlotScript() {
    std::ofstream py_script("plot_results.py");
    py_script << R"(
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Загрузка данных
data = pd.read_csv('simulation_results.csv')

# Создание графиков
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))

# График линейной модели
ax1.plot(data['Step'], data['Setpoint'], 'r--', label='Задание')
ax1.plot(data['Step'], data['Linear_Output'], 'b-', label='Линейная модель')
ax1.set_xlabel('Шаг времени')
ax1.set_ylabel('Температура')
ax1.set_title('Линейная модель ПИД-регулирования')
ax1.legend()
ax1.grid(True)

# График нелинейной модели
ax2.plot(data['Step'], data['Setpoint'], 'r--', label='Задание')
ax2.plot(data['Step'], data['Nonlinear_Output'], 'g-', label='Нелинейная модель')
ax2.set_xlabel('Шаг времени')
ax2.set_ylabel('Температура')
ax2.set_title('Нелинейная модель ПИД-регулирования')
ax2.legend()
ax2.grid(True)

plt.tight_layout()
plt.savefig('pid_simulation_results.png', dpi=300)
plt.show()

# Вывод статистики
print("=== Статистика результатов ===")
print(f"Линейная модель:")
print(f"  Среднее значение: {data['Linear_Output'].mean():.3f}")
print(f"  Стандартное отклонение: {data['Linear_Output'].std():.3f}")
print(f"  Установившееся значение: {data['Linear_Output'].iloc[-10:].mean():.3f}")
print()
print(f"Нелинейная модель:")
print(f"  Среднее значение: {data['Nonlinear_Output'].mean():.3f}")
print(f"  Стандартное отклонение: {data['Nonlinear_Output'].std():.3f}")
print(f"  Установившееся значение: {data['Nonlinear_Output'].iloc[-10:].mean():.3f}")
)";
    py_script.close();
    
    system("python plot_results.py");
}
