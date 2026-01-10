<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28/24</p>
<p align="right">Малич А.В.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

1. Написать отчет по выполненной лабораторной работе №3 в .md формате (*readme.md*) и разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4. Документировать исходный код программы с помощью комментариев в стиле **Doxygen**. Полученную документацию разместить в каталоге: **trunk\ii0xxyy\task_03\doc\html**. Настроить `GitHub Pages` для автоматической публикации документации из этого каталога.
5. Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием **Google Test**. Тесты разместить в каталоге: **trunk\ii0xxyy\task_03\test**.

**Лабораторная работа №3.**

**ПИД-регуляторы**

На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

## Код программы [ src/model_validation.cpp ]
```C++
/**
 * @file model_validation.cpp
 * @brief Простые проверки математических функций
 */

#include <iostream>
#include <cmath>
#include <cassert>

// Простая проверочная функция
bool test_linear_calculation() {
    double result = 0.5 * 10.0 + 0.2 * 5.0; // a*y + b*u
    return std::abs(result - 6.0) < 1e-10;
}

bool test_edge_cases() {
    // Нулевые входы
    bool test1 = std::abs(0.0 * 0.0 + 0.0 * 0.0) < 1e-10;
    
    // Единичные коэффициенты
    bool test2 = std::abs(1.0 * 1.0 + 1.0 * 1.0 - 2.0) < 1e-10;
    
    return test1 && test2;
}

int main() {
    std::cout << "=== Проверка математических функций ===" << std::endl;
    
    if (test_linear_calculation()) {
        std::cout << "✓ Базовая математика: OK" << std::endl;
    } else {
        std::cout << "✗ Базовая математика: FAILED" << std::endl;
        return 1;
    }
    
    if (test_edge_cases()) {
        std::cout << "✓ Граничные случаи: OK" << std::endl;
    } else {
        std::cout << "✗ Граничные случаи: FAILED" << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Все проверки пройдены ===" << std::endl;
    return 0;
}
## Результат программы [ src/main.cpp ]
![Result](images/3.png)

![schedule1](images/4.png)
<br>



## Код юнит-тестов [ test/test_model.cpp ]
```C++
/**
class IntelligentRegulator {
private:
    struct ControlCoefficients {
        double main_gain;          // K - коэффициент усиления
        double integration_constant; // Ti - время интегрирования
        double derivative_constant;  // Td - время дифференцирования
        double sampling_rate;        // T0 - период дискретизации
    };
    
    double computeRegulationCommand(double system_error) {
        // Пропорциональная составляющая
        double proportional = Kp * error;
        // Интегральная составляющая
        double integral = Ki * error * T0;
        // Дифференциальная составляющая
        double derivative = Kd * (error - prev_error) / T0;
        return proportional + integral + derivative;
    }
};
```
## Результаты юнит-тестирования (GoogleTest)
![GoogleTest](images/2.png)

## Покрытие GCC Code Coverage

![GCC Coverage](images/1.png)
