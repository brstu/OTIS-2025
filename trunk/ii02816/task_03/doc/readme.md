# Лабораторная работа №3: Моделирование ПИД-регулятора для теплового объекта

<p align="center">
  <strong>Министерство образования Республики Беларусь</strong><br>
  <strong>Учреждение образования «Брестский Государственный технический университет»</strong><br>
  <strong>Кафедра ИИТ</strong>
</p>

<br><br><br><br>

<p align="center">
  <strong>Лабораторная работа №3</strong><br>
  <strong>По дисциплине «Общая теория интеллектуальных систем»</strong><br>
  <strong>Тема: «Моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса»</strong>
</p>

<br><br><br>

<p align="right">
  <strong>Выполнил:</strong><br>
  Студент 2 курса<br>
  Группы ИИ-28/24<br>
  Литвинчук И.М.<br>
  <br>
  <strong>Проверил:</strong><br>
  Дворанинович Д.А.
</p>

<br><br><br>

<p align="center">
  <strong>Брест 2025</strong>
</p>

## Содержание
1. [Цель работы](#цель-работы)
2. [Теоретические сведения](#теоретические-сведения)
3. [Реализация программы](#реализация-программы)
4. [Структура проекта](#структура-проекта)
5. [Результаты работы](#результаты-работы)
6. [Документация](#документация)
7. [Тестирование](#тестирование)
8. [Выводы](#выводы)

## Цель работы

Разработка и моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса. Исследование влияния параметров регулятора на качество управления линейной и нелинейной моделями объекта.

## Теоретические сведения

### Структура системы автоматического управления

Система с обратной связью включает:
- **w(t)** — задающее воздействие
- **u(t)** — управляющее воздействие
- **y(t)** — выходная переменная
- **e(t) = w(t) - y(t)** — ошибка управления

### Уравнение ПИД-регулятора

Идеализированное уравнение непрерывного ПИД-регулятора:

u(t) = K * [e(t) + 1/T * ∫e(τ)dτ + Td * de(t)/dt]где:
- **K** — коэффициент усиления
- **T** — постоянная времени интегрирования
- **Td** — постоянная времени дифференцирования

### Дискретная реализация

Для реализации на компьютере используется дискретная форма:
u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)где:
- **q0 = K * (1 + T0/T + Td/T0)**
- **q1 = -K * (1 + 2*Td/T0)**
- **q2 = K * Td/T0**
- **T0** — шаг квантования

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

````
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

````