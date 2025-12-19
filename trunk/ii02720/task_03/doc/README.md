<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "ПИД-регуляторы"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Степанюк И.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

## Задание
Реализовать программу на C++, моделирующую ПИД-регулятор для управления температурой объекта.

## Теория
ПИД-регулятор вычисляет управляющее воздействие по формуле:

u(k) = u(k-1) + Δu(k)

где Δu(k) = q₀·e(k) + q₁·e(k-1) + q₂·e(k-2)

## Реализация

### Структура проекта
```
src/
├── model/           - модели объекта (линейная и нелинейная)
├── factory/         - фабрики для создания моделей  
├── regulator/       - ПИД-регулятор
├── adaptivecontroller.hpp
└── main.cpp
test/
└── test.cpp         - юнит-тесты
```

### Основной код (main.cpp)
```cpp
#include <iostream>
#include "factory/factorylinearmodel.hpp"
#include "factory/factorynonlinearmodel.hpp"
#include "adaptivecontroller.hpp"
#include "regulator/pidregulator.hpp"

int main() 
{
    double setpoint = 10.0;
    int duration = 10;
    
    std::cout << "=== Linear Model ===" << std::endl;
    auto linReg = std::make_unique<PIDRegulator>();
    auto linFactory = std::make_unique<FactoryLinearModel>();
    auto linModel = linFactory->createModel();
    auto linController = std::make_unique<AdaptiveController>(std::move(linReg), std::move(linModel)); 
    
    for (auto val : linController->execute(setpoint, duration)) 
        std::cout << val << std::endl;

    std::cout << "\n=== NonLinear Model ===" << std::endl; 
    auto nlReg = std::make_unique<PIDRegulator>();
    auto nlFactory = std::make_unique<FactoryNonLinearModel>();
    auto nlModel = nlFactory->createModel();
    auto nlController = std::make_unique<AdaptiveController>(std::move(nlReg), std::move(nlModel)); 
    
    for (auto val : nlController->execute(setpoint, duration)) 
        std::cout << val << std::endl;

    return 0;
}
```

## Результаты
Линейная модель демонстрирует устойчивый переходный процесс.
Нелинейная модель показывает колебания из-за сложной динамики.

## Тестирование
Программа покрыта 4 юнит-тестами с использованием Google Test.
