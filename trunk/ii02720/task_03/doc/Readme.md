<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Разработка и исследование системы автоматического управления с дискретным ПИД-регулятором для теплового объекта"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27 (ii02720)</p>
<p align="right">Степанюк Илья Сергеевич</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

## Требования к выполнению работы

1. Подготовить отчёт по лабораторной работе №3 в формате Markdown (*readme.md*) и разместить в каталоге: **trunk\ii02720\task_03\doc**.
2. Исходные коды программы поместить в каталог: **trunk\ii02720\task_03\src**.
3. Зафиксировать выполнение работы в главном файле readme.md репозитория.
4. Задокументировать код в стиле **Doxygen**. Документацию разместить в: **trunk\ii02720\task_03\doc\html**. Настроить публикацию через `GitHub Pages`.
5. Разработать модульные тесты с использованием **Google Test** и разместить в: **trunk\ii02720\task_03\test**.

---

## Теоретическое введение

### Лабораторная работа №3: Дискретные ПИД-регуляторы

Структурная схема замкнутой системы автоматического регулирования представлена на рисунке 1.

![Структурная схема САУ](images/1.png)

**Обозначения:**
- w(t) — задающее воздействие (уставка)
- u(t) — управляющее воздействие от регулятора
- z(t) — внешние возмущения
- y(t) — регулируемая величина (выход объекта)
- e(t) = w(t) - y(t) — ошибка регулирования

Регулируемой величиной может являться температура в технологическом аппарате, частота вращения электродвигателя, уровень жидкости в резервуаре и подобные физические параметры. Задача системы управления — минимизировать ошибку e(t) при изменении задания w(t) или действии возмущений z(t).

Автоматический регулятор G<sub>R</sub> формирует закон управления u(t) = G<sub>R</sub>[e(t)]. Для синтеза регулятора необходима математическая модель объекта y(t) = G<sub>O</sub>[u(t)].

### Уравнение идеального ПИД-регулятора

![Формула ПИД](images/2.png)

где:
- K — коэффициент передачи
- T — постоянная интегрирования
- T<sub>D</sub> — постоянная дифференцирования

Параметры K, T, T<sub>D</sub> определяются при настройке регулятора для достижения требуемого качества переходного процесса.

### Частные случаи ПИД-регулятора

**П-регулятор** (только пропорциональное управление):

![П-регулятор](images/3.png)

**ПИ-регулятор** (пропорционально-интегральный):

![ПИ-регулятор](images/4.png)

### Графики переходных процессов

![П-регулятор график](images/5.png)
*Рисунок 2. П-регулятор: Kp=10, Ti=0, Td=0*

![ПИ-регулятор график](images/6.png)
*Рисунок 3. ПИ-регулятор: Kp=10, Ti=0.1, Td=0*

![ПИД-регулятор график](images/7.png)
*Рисунок 4. ПИД-регулятор: Kp=10, Ti=0.1, Td=50*

### Дискретизация ПИД-регулятора

При реализации на микроконтроллере или ПК сигналы квантуются с периодом T<sub>0</sub>. Непрерывное уравнение преобразуется в разностное заменой производной конечной разностью и интеграла конечной суммой:

![Дискретный ПИД](images/8.png)

где k — номер дискретного отсчёта времени.

### Рекуррентный алгоритм ПИД

Для исключения необходимости хранить всю историю ошибок применяется рекуррентная формула:

![Рекуррентная формула](images/11.png)

где коэффициенты вычисляются как:

![q0](images/12.png)
![q1](images/13.png)
![q2](images/14.png)

Таким образом, для расчёта u(k) достаточно хранить: u(k-1), e(k), e(k-1), e(k-2).

![Структура данных](images/15.png)
![Алгоритм](images/16.png)

### Алгоритм работы ПИД-регулятора

![Шаг 1](images/17.png)
![Шаг 2](images/18.png)
![Шаг 3](images/19.png)
![Шаг 4](images/20.png)
![Шаг 5](images/21.png)

---

## Задание

Реализовать на **C++** программу моделирования дискретного ПИД-регулятора. Объект управления — тепловая модель из предыдущей лабораторной работы. Построить графики переходных процессов для различных заданий температуры.

---

## Исходный код программы

### Файл: src/lab3main.cpp

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "pid.h"
#include "model.h"

std::vector<double> runSimulation(PIDController& pidRegulator, ProcessModel& thermalObject, 
                                  const std::vector<double>& targetValues, bool useNonlinearMode = false) {
    std::vector<double> outputHistory;
    
    for (double targetTemp : targetValues) {
        double currentOutput = (outputHistory.empty()) ? 0.0 : outputHistory.back();
        double controlAction = pidRegulator.calculate(targetTemp, currentOutput);
        
        double nextOutput;
        if (useNonlinearMode) {
            nextOutput = thermalObject.nonlinearModel(controlAction);
        } else {
            nextOutput = thermalObject.linearModel(controlAction);
        }
        
        outputHistory.push_back(nextOutput);
    }
    
    return outputHistory;
}

int main() {
    setlocale(LC_ALL, "");
    
    // Параметры теплового объекта
    std::vector<double> thermalParams = {0.87, 0.012, 0.17, 0.012};
    ProcessModel thermalProcess(thermalParams, 12.0);
    
    // Настройка ПИД-регулятора
    double Kp = 0.75;
    double Ti = 3.5;
    double Td_coef = 0.06;
    double Ts = 1.0;
    
    PIDController pidController(Kp, Ti, Td_coef, Ts);
    
    // Моделирование
    const int simulationSteps = 25;
    std::vector<double> temperatureSetpoints(simulationSteps, 22.0);
    
    auto linearSimResults = runSimulation(pidController, thermalProcess, temperatureSetpoints, false);
    
    pidController.reset();
    thermalProcess.setInitialValue(0.0);
    
    auto nonlinearSimResults = runSimulation(pidController, thermalProcess, temperatureSetpoints, true);
    
    // Вывод результатов
    std::cout << "=== Результаты моделирования (Степанюк И.С., ii02720) ===" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Шаг\t\tЗадание\t\tЛинейная\tНелинейная\n";
    
    for (size_t step = 0; step < temperatureSetpoints.size(); ++step) {
        std::cout << step << "\t\t" << temperatureSetpoints[step] << "\t\t" 
                << linearSimResults[step] << "\t\t" << nonlinearSimResults[step] << "\n";
    }
    
    std::cout << "Моделирование завершено." << std::endl;
    
    return 0;
}
```

---

## Результаты выполнения программы

![Результат работы программы](images/result.jpg)

---

## Анализ результатов

При моделировании САУ с ПИД-регулятором для теплового объекта получены следующие результаты:
- Линейная модель обеспечивает более быстрый выход на установившееся значение
- Нелинейная модель демонстрирует колебательный переходный процесс
- Параметры регулятора (Kp=0.75, Ti=3.5, Td=0.06) обеспечивают устойчивую работу системы

---

## Модульные тесты (GoogleTest)

### Файл: test/testlab_3.cpp

```cpp
#include <gtest/gtest.h>
#include <cmath>
#include "../src/pid.h"
#include "../src/model.h"

TEST(PIDControllerTest_Stepaniuk, ConstructorAndBasicCalculation)
{
    PIDController pidReg(2.5, 1.2, 0.4, 1.0);
    double controlValue = pidReg.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(controlValue));
}

TEST(PIDControllerTest_Stepaniuk, ProportionalControllerBehavior)
{
    PIDController pReg(1.0, 1.0, 0.0, 1.0); 
    pReg.reset();
    double u_step1 = pReg.calculate(1.0, 0.0);
    EXPECT_NEAR(u_step1, 1.0, 1e-6);
}

TEST(ProcessModelTest_Stepaniuk, LinearModelCalculation)
{
    std::vector<double> coeffs = {0.55, 0.45, 0.0, 0.0};
    ProcessModel plant(coeffs, 1.0);
    double y1 = plant.linearModel(1.0);
    EXPECT_NEAR(y1, 0.55 * 1.0 + 0.45 * 1.0, 1e-6);
}

TEST(SystemIntegrationTest_Stepaniuk, ClosedLoopWithPController)
{
    std::vector<double> modelCoeffs = {0.75, 0.25, 0.0, 0.0};
    ProcessModel plant(modelCoeffs, 0.0);
    PIDController pController(2.5, 1.0, 0.0, 1.0);
    
    std::vector<double> trajectory;
    double setpoint = 1.0;
    
    for (int k = 0; k < 12; k++) {
        double currentY = (trajectory.empty()) ? 0.0 : trajectory.back();
        double controlU = pController.calculate(setpoint, currentY);
        double nextY = plant.linearModel(controlU);
        trajectory.push_back(nextY);
    }
    
    EXPECT_GT(trajectory.back(), 0.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

---

## Результаты тестирования

![GoogleTest результаты](images/gtest.jpg)

Все модульные тесты пройдены успешно.

---

## Ссылка на документацию

[GitHub Pages - Документация проекта](https://brstu.github.io/OTIS-2025/trunk/ii02720/task_03/doc/html/)

---

*© 2025 Степанюк Илья Сергеевич (ii02720, гр. ИИ-27)*
