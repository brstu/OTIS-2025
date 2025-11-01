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
<p align="right">Группы ИИ-27</p>
<p align="right">Дорошенко М.Д.</p>
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

Структурная схема системы автоматического управления с обратной связью показана на рис.1.

![1](images/1.png)

Здесь w(t) - алгоритм функционирования системы; u(t) - управляющее воздействие; z(t) - внешние возмущающие воздействия, влияние которых нужно свести к минимуму; y(t) - выходная переменная; e(t) = w(t) - y(t) - отклонение выходной переменной y(t) от желаемого значения w(t).
Выходной переменной может быть температура в печи, скорость вращения вала двигателя, уровень жидкости в баке, рассовмещение знаков привязки фотошаблонов и т.п. Целью управления может быть изменение выходной переменной по заданному закону w(t). Для этого нужно свести к минимуму ошибку управления e(t).
Эта задача решается автоматическим регулятором G<sub>R</sub> (рис.1), который описывается некоторым законом регулирования u(t) = G<sub>R</sub>[e(t)]. Для правильного выбора закона регулирования нужно знать математическую модель объекта управления y(t) = G<sub>O</sub>[u(t)]. Математическая модель обычно представляет собой систему обыкновенных нелинейных дифференциальных уравнений или дифференциальных уравнений в частных производных. Нахождение вида и коэффициентов этих уравнений представляет собой задачу идентификации объекта управления. Для традиционно используемых объектов управления математические модели часто известны и тогда задача идентификации конкретного объекта сводится к отысканию значений коэффициентов уравнений. Во многих случаях эти коэффициенты можно подобрать опытным путем в процессе настройки системы.
Выбор закона регулирования u(t) = G<sub>R</sub>[e(t)] является основным звеном в процессе проектирования системы автоматического регулирования. Синтез оптимального регулятора, дающего максимальные показатели качества регулирования, представляет собой достаточно сложную задачу. Кроме того, реализация оптимального регулятора может оказаться экономически неоправданной. Однако во многих случаях для автоматизации производственных процессов могут быть использованы простейшие и наиболее распространенные типы линейных регуляторов - П-, ПИ-. и ПИД-регуляторы.
Идеализированное уравнение ПИД-регулятора имеет вид

![2](images/2.png)

где K - коэффициент передачи, T - постоянная интегрирования, T<sub>D</sub> - постоянная дифференцирования.
Эти три параметра подбирают в процессе настройки регулятора таким образом, чтобы максимально приблизить алгоритм функционирования системы к желаемому виду.
В зависимости от типа объекта управления может быть достаточным применение более простого П-регулятора

![3](images/3.png)

или ПИ-регулятора

![4](images/4.png)

которые являются частными случаями ПИД-регулятора при соответствующем выборе постоянных интегрирования и дифференцирования.
Графики переходных процессов регулируемой величины представлены на рис. 2-4. Зеленым цветом показана реакция на скачок объекта регулирования, синим цветом - выходная переменная в процессе регулирования, красным - изменение регулируемого параметра во времени.

![5](images/5.png)
Рисунок 0.2 П-регулятор. К = 10, T=0, TD=0

![6](images/6.png)
Рисунок 0.3 ПИ-регулятор. К=10, T=0.1, TD=0

![7](images/7.png)
Рисунок 0.4 ПИД-регулятор. K=10, T=0.1, TD =50

Описанная система автоматического регулирования является непрерывной, т.е. использует непрерывное время. При построении регулятора на базе компьютера входные и выходные переменные регулятора необходимо квантовать по времени с некоторым шагом T<sub>O</sub> , и преобразовать в цифровую форму с помощью аналого-цифровых и цифро-аналоговых преобразователей. При этом уравнении ПИД-регулятора должно быть преобразовано в разностное с помощью замены производных конечной разностью, а интеграла - конечной суммой. В зависимости от выбранного метода перехода от непрерывных операторов к их дискретным аналогам возникает несколько различных уравнений, описывающих дискретные ПИД-регуляторы. При использовании метода прямоугольников для замены интеграла конечной суммой получим:

![8](images/8.png)

где ![9](images/9.png)- порядковый номер отсчета дискретного времени.
Недостатком такого представления уравнения регулятора является необходимость помнить значения отклонений е(k) для всех моментов времени от начала процесса регулирования.
Этот недостаток можно устранить, если для вычисления текущего значения управляющей переменной u(k) использовать ее предыдущее значение u(k-1) и поправочный член. Для получения такого рекуррентного алгоритма достаточно вычесть из уравнения (4) следующее уравнение:

![10](images/10.png)

В результате получим:

![11](images/11.png)

где ![12](images/12.png)

![13](images/13.png)

![14](images/14.png)

Таким образом, для вычисления текущего значения управляющего воздействия u(k) на объект управления достаточно хранить в памяти только величины u(k-1), e(k), e(k-1), e(k-2), то есть величины

![15](images/15.png)

![16](images/16.png)

Итак, алгоритм работы ПИД-регулятора может быть представлен в следующем виде:

![17](images/17.png)

![18](images/18.png)

![19](images/19.png)

![20](images/20.png)

![21](images/21.png)

При переходе от непрерывных операторов к дискретным возникает погрешность, величина которой пропорциональна остаточному члену ряда Тейлора функции e(t) . Поэтому полученные дискретные уравнения можно считать эквивалентными непрерывным только при условии, что e(t) изменяется слабо в пределах такта квантования.
Однако с помощью аппарата z-преобразования можно показать, что основные свойства ПИД-регулятора сохраняются и при больших шагах квантования, если параметры регулятора q<sub>0</sub>, q<sub>1</sub>, q<sub>2</sub> выбирать не на основании параметров его непрерывного аналога (13), а независимо от них, методами параметрической оптимизации, выбрав необходимый критерий качества оптимизации исходя из цели регулирования. Такт квантования выбирают аналогично.

**Задание.**
На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.


## Код программы [ src/main.cpp ]
```C++
#include <iostream>

#include "factory/factorylinearmodel.hpp"
#include "factory/factorynonlinearmodel.hpp"

#include "adaptivecontroller.hpp"
#include "regulator/pidregulator.hpp"

int main() 
{
    const double w = 10;  // Input warm.
    const int t = 5;     // Simulation time steps.
    
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

## Результат программы [ src/main.cpp ]
![results](images/results.png)

## Графики
### При `T = 0.05 T0 = 1 TD = 10`
Линейная модель:
<br>
![g1](images/g1.png)
<br>
Нелинейная модель:
<br>
![g2](images/g2.png)

### При `T = 0.1 T0 = 5 TD = 20`
Линейная модель:
<br>
![g3](images/g3.png)
<br>
Нелинейная модель:
<br>
![g4](images/g4.png)

## Вывод полученных данных при использовании ПИД-регулятора

### Линейная модель (`T = 0.05, T0 = 1, TD = 10`)
- Система демонстрирует **устойчивый переходный процесс** с небольшим перерегулированием.
- Выход выходит на установившееся значение ≈ 2.85 без колебаний — **хорошая стабильность**.

### Нелинейная модель (`T = 0.05, T0 = 1, TD = 10`)
- Наличие **сильных колебаний** указывает на неустойчивость или недостаточную настройку регулятора.
- Система не сходится — **необходима корректировка параметров ПИД**.

### Линейная модель (`T = 0.1, T0 = 5, TD = 20`)
- Процесс более инерционный, но также **сходится к установившемуся значению ≈ 5.0**.
- Перерегулирование выше, чем в первом случае — **увеличение времени дискретизации влияет на динамику**.

### Нелинейная модель (`T = 0.1, T0 = 5, TD = 20`)
- График показывает **аномальные значения** (порядка `-1E+168`), что указывает на **расходимость системы** или **ошибку моделирования**.
- Такое поведение характерно для нестабильной системы с 'неадекватными' параметрами регулятора.

## Link to documentation
[https://chuikam.github.io/OTIS-2025/](https://chuikam.github.io/OTIS-2025/)

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
TEST(TestNonLinearModel, WhenTimeIsFives)
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
    const double w = 10;  // Input warm.
    const int t = 5;      // Simulation time steps.

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
    const double w = 10;  // Input warm.
    const int t = 5;      // Simulation time steps.

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

## Результаты юнит-тестирования (GoogleTest)
![GoogleTest Output](images/gtest.png)

## Покрытие тестами (gcovr)
!['gcovr' Output](images/gcovr.png)

## Reviews
igor7123
<br>
![Review for igor7123](images/igor7123.png)
<br>
tstepannovikov
<br>
![Review for :](images/tstepannovikov.png)

