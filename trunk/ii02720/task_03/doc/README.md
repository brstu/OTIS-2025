<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса."</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Степанюк И.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

1. Написать отчет по выполненной лабораторной работе №3 в .md формате (*readme.md*) и разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
3. Отразить выполнение работы в файле readme.md в соответствующей строке.
4. Документировать исходный код программы с помощью комментариев в стиле **Doxygen**. Полученную документацию разместить в каталоге: **trunk\ii0xxyy\task_03\doc\html**.
5. Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием **Google Test**. Тесты разместить в каталоге: **trunk\ii0xxyy\task_03\test**.

**Лабораторная работа №3.**

**ПИД-регуляторы**

Структурная схема системы автоматического управления с обратной связью показана на рис.1.

Здесь w(t) - алгоритм функционирования системы; u(t) - управляющее воздействие; z(t) - внешние возмущающие воздействия, влияние которых нужно свести к минимуму; y(t) - выходная переменная; e(t) = w(t) - y(t) - отклонение выходной переменной y(t) от желаемого значения w(t).

Выходной переменной может быть температура в печи, скорость вращения вала двигателя, уровень жидкости в баке и т.п. Целью управления может быть изменение выходной переменной по заданному закону w(t). Для этого нужно свести к минимуму ошибку управления e(t).

Эта задача решается автоматическим регулятором G<sub>R</sub>, который описывается некоторым законом регулирования u(t) = G<sub>R</sub>[e(t)].

Идеализированное уравнение ПИД-регулятора имеет вид:

$$u(t) = K \left( e(t) + \frac{1}{T} \int_0^t e(\tau) d\tau + T_D \frac{de(t)}{dt} \right)$$

где K - коэффициент передачи, T - постоянная интегрирования, T<sub>D</sub> - постоянная дифференцирования.

При переходе к дискретной форме получаем рекуррентный алгоритм:

$$u(k) = u(k-1) + \Delta u(k)$$

$$\Delta u(k) = q_0 e(k) + q_1 e(k-1) + q_2 e(k-2)$$

где:
- $q_0 = K \left( 1 + \frac{T_D}{T_0} \right)$
- $q_1 = -K \left( 1 + 2\frac{T_D}{T_0} - \frac{T_0}{T} \right)$
- $q_2 = K \frac{T_D}{T_0}$

**Задание.**
На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.


## Код программы [ src/main.cpp ]
```C++
#include <iostream>

#include "factory/factorylinearmodel.hpp"
#include "factory/factorynonlinearmodel.hpp"

#include "adaptivecontroller.hpp"
#include "regulator/pidregulator.hpp"

int main() 
{
    const double w = 10; // Input warm.
    const int t = 10;    // Simulation time steps.
    
    std::cout << "Linear simulation:" << std::endl;
    auto pidRegulatorForLinearModel = std::make_unique<PIDRegulator>();
    auto linearFactory = std::make_unique<FactoryLinearModel>();
    auto linearModel = linearFactory->getDefaultModel();

    auto linearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForLinearModel), std::move(linearModel)); 
    auto linear_result = linearController->run(w, t);
    for (const auto& value : linear_result) 
    {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Nonlinear simulation:" << std::endl; 
    auto pidRegulatorForNonLinearModel = std::make_unique<PIDRegulator>();
    auto nonlinearFactory = std::make_unique<FactoryNonLinearModel>();
    auto nonlinearModel = nonlinearFactory->getDefaultModel();

    auto nonlinearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForNonLinearModel), std::move(nonlinearModel)); 
    auto nonlinear_result = nonlinearController->run(w, t);
    for (const auto& value : nonlinear_result) 
    {
        std::cout << value << std::endl;
    }

    return 0;
}
```

## Вывод полученных данных при использовании ПИД-регулятора

### Линейная модель (`T = 0.05, T0 = 1, TD = 10`)
- Система демонстрирует **устойчивый переходный процесс** с небольшим перерегулированием.
- Выход выходит на установившееся значение без значительных колебаний — **хорошая стабильность**.

### Нелинейная модель (`T = 0.05, T0 = 1, TD = 10`)
- Наличие **колебаний** указывает на более сложную динамику системы.
- Требуется корректировка параметров ПИД для достижения устойчивости.

## Код юнит-тестов [ test/test.cpp ]
```C++
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "../src/factory/factorylinearmodel.hpp"
#include "../src/factory/factorynonlinearmodel.hpp"

#include "../src/regulator/pidregulator.hpp"
#include "../src/adaptivecontroller.hpp"

TEST(TestLinearModel, WhenTimeIsFive)
{   
    const double y = 0; // Initial output value
    const double u = 1; // Input signal value
    const int t = 5;    // Simulation time steps

    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->getDefaultModel();
    std::vector<double> calculated_results = model->simulate(y, u, t);
    std::vector<double> accepted_results
    { 0, 0.5, 0.75, 0.875, 0.9375, 0.96875 };

    EXPECT_EQ(calculated_results.size(), accepted_results.size());
    
    for (size_t i = 0; i < calculated_results.size(); i++)
    {
        EXPECT_NEAR(calculated_results[i], accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
    }
}

TEST(TestNonLinearModel, WhenTimeIsFive)
{   
    const double y = 0; // Initial output value
    const double u = 1; // Input signal value
    const int t = 5;    // Simulation time steps

    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->getDefaultModel();
    std::vector<double> calculated_results = model->simulate(y, u, t);
    std::vector<double> accepted_results
    { 0, 0.499999, 0.989713, 1.29059, 1.15428, 0.698974 };

    EXPECT_EQ(calculated_results.size(), accepted_results.size());
    
    for (size_t i = 0; i < calculated_results.size(); i++) 
    {
        EXPECT_NEAR(calculated_results[i], accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
    }
}

TEST(TestAdaptiveControllerLinearModel, WhenInputWarmIsTenAndTimeIsFive)
{
    const double w = 10; // Input warm.
    const int t = 5;     // Simulation time steps.

    auto pidRegulatorForLinearModel = std::make_unique<PIDRegulator>();
    auto linearFactory = std::make_unique<FactoryLinearModel>();
    auto linearModel = linearFactory->getDefaultModel();

    auto linearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForLinearModel), std::move(linearModel)); 
    std::vector<double> linear_result = linearController->run(w, t);

    std::vector<double> accepted_results
    { 0.55, 1.32775, 2.10299, 2.80855, 3.05697, 3.106 };

    EXPECT_EQ(linear_result.size(), accepted_results.size());
    
    for (size_t i = 0; i < linear_result.size(); i++) 
    {
        EXPECT_NEAR(linear_result[i], accepted_results[i], 1e-4)
           << "Mismatch at index " << i;
    }
}

TEST(TestAdaptiveControllerNonLinearModel, WhenInputWarmIsTenAndTimeIsFive)
{
    const double w = 10; // Input warm.
    const int t = 5;     // Simulation time steps.

    auto pidRegulatorForNonLinearModel = std::make_unique<PIDRegulator>();
    auto nonlinearFactory = std::make_unique<FactoryNonLinearModel>();
    auto nonlinearModel = nonlinearFactory->getDefaultModel();

    auto nonlinearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForNonLinearModel), std::move(nonlinearModel)); 
    std::vector<double> nonlinear_result = nonlinearController->run(w, t);

    std::vector<double> accepted_results
    { 0.55, 1.77335, 2.58247, 1.55651, -1.1215, -0.0515545 };

    EXPECT_EQ(nonlinear_result.size(), accepted_results.size());
    
    for (size_t i = 0; i < nonlinear_result.size(); i++) 
    {
        EXPECT_NEAR(nonlinear_result[i], accepted_results[i], 1e-4)
            << "Mismatch at index " << i;
    }
}
```

