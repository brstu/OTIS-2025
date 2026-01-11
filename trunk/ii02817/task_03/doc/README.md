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
<p align="right">Любовицкий Н.Н.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

1. Написать отчет по выполненной лабораторной работе №3 в .md формате (_readme.md_) и разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc**.
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
На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор. В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.

## Код программы [ src/lab3.cpp ]

```C++
#include <iostream>
#include <vector>
#include <fstream>
#include "model.h"
#include "pid.h"

/**
 * @brief Симуляция системы с PID-регулятором
 * @param plant Модель объекта
 * @param pid PID-регулятор
 * @param setpoint Задание
 * @param simulation_time Время симуляции
 * @param use_nonlinear Флаг использования нелинейной модели
 * @return Вектор результатов [время, задание, выход, управление]
 */
std::vector<std::vector<double>> simulateSystem(
    PlantModel &plant,
    PIDController &pid,
    double setpoint,
    int simulation_time,
    bool use_nonlinear = false)
{
    std::vector<std::vector<double>> results(5);

    for (int k = 0; k < simulation_time; k++)
    {
        double y = plant.getOutput();
        double e = setpoint - y;
        double u = pid.calculate(e);

        if (use_nonlinear)
        {
            plant.nonlinearStep(u);
        }
        else
        {
            plant.linearStep(u);
        }

        results[0].push_back(k);
        results[1].push_back(setpoint);
        results[2].push_back(y);
        results[3].push_back(u);
        results[4].push_back(e);
    }

    return results;
}

/**
 * @brief Вывод результатов в консоль
 * @param results Результаты симуляции
 * @param test_name Название теста
 */
void printResultsToConsole(const std::vector<std::vector<double>> &results, const std::string &test_name)
{
    std::cout << "\n"
              << test_name << ":\n";
    std::cout << "Time\tSetpoint\tOutput\t\tControl\t\tE\n";
    std::cout << "----\t--------\t------\t\t-------\t\t-------\n";
    for (size_t i = 0; i < results[0].size(); i++)
    {
        std::cout << results[0][i] << "\t" << results[1][i] << "\t\t"
                  << results[2][i] << "\t\t" << results[3][i] << "\t\t" << results[4][i] << '\n';
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "PID CONTROLLER SIMULATION\n"
              << std::endl;

    // Ввод параметров
    double y0, w;
    int simulation_time;

    std::cout << "Enter initial temperature y0: ";
    std::cin >> y0;

    std::cout << "Enter target temperature w: ";
    std::cin >> w;

    std::cout << "Enter number of simulation steps: ";
    std::cin >> simulation_time;

    // Создание моделей объектов
    PlantModel linear_plant(0.8, 0.2, 0.2, 0.15);
    PlantModel nonlinear_plant(0.85, 0.01, 0.15, 0.01);

    linear_plant.setState(y0, 0.0);
    nonlinear_plant.setState(y0, 0.0);

    // Тест 1: PID-регулятор (линейная модель)
    std::cout << "=== TEST 1: PID-controller (linear model) ===" << std::endl;
    PIDController pid_linear(0.4, 3.0, 0.1, 1.0);
    pid_linear.setLimits(w);
    auto results_linear = simulateSystem(linear_plant, pid_linear, w, simulation_time, false);
    printResultsToConsole(results_linear, "PID-controller (linear model)");

    // Тест 2: PID-регулятор (нелинейная модель)
    std::cout << "=== TEST 2: PID-controller (nonlinear model) ===" << std::endl;
    PIDController pid_nonlinear(0.8, 4.0, 0.05, 1.0);
    pid_nonlinear.setLimits(w);
    auto results_nonlinear = simulateSystem(nonlinear_plant, pid_nonlinear, w, simulation_time, true);
    printResultsToConsole(results_nonlinear, "PID-controller (nonlinear model)");

    std::cout << "SIMULATION COMPLETED" << std::endl;
    return 0;
}
```

## Результат программы [ src/main.cpp ]

![result](images/result.png)

## График

![g1](images/g.jpg)
<br>

## Вывод полученных данных при использовании ПИД-регулятора

## Link to documentation

[https://lineekz.github.io/OTIS-2025/](https://lineekz.github.io/OTIS-2025/)

## Код юнит-тестов [ test/testlab3.cpp ]

```C++
#include <gtest/gtest.h>
#include "../src/pid.h"
#include "../src/model.h"

TEST(PIDControllerTest, ConstructorAndParameters)
{
    PIDController pid(2.0, 1.0, 0.5, 1.0);
    auto coeffs = pid.getCoefficients();

    EXPECT_NEAR(coeffs[0], 2.0 * (1.0 + 0.5 / 1.0), 1e-6);
    EXPECT_NEAR(coeffs[1], -2.0 * (1.0 + 2.0 * 0.5 / 1.0 - 1.0 / 1.0), 1e-6);
    EXPECT_NEAR(coeffs[2], 2.0 * 0.5 / 1.0, 1e-6);
}

TEST(PIDControllerTest, Calculate)
{
    PIDController pid(1.0, 1.0, 0.0, 1.0); // П-регулятор
    pid.reset();

    double u1 = pid.calculate(1.0);
    double u2 = pid.calculate(0.5);
    double u3 = pid.calculate(0.0);

    EXPECT_NEAR(u1, 1.0, 1e-6); // K * e = 1.0 * 1.0
    EXPECT_NEAR(u2, 1.5, 1e-6); // 1.0 + 1.0 * 0.5
    EXPECT_NEAR(u3, 1.5, 1e-6); // 1.5 + 1.0 * 0.0
}

TEST(PIDControllerTest, Limits)
{
    PIDController pid(10.0, 1.0, 0.0, 1.0);
    pid.setLimits(5.0);
    pid.reset();

    double u = pid.calculate(1.0); // Должно быть ограничено до 5.0

    EXPECT_NEAR(u, 5.0, 1e-6);
}

TEST(PlantModelTest, LinearStep)
{
    PlantModel plant(0.5, 0.5, 0.0, 0.0);
    plant.setState(1.0, 0.0);

    double y1 = plant.linearStep(1.0);
    EXPECT_NEAR(y1, 0.5 * 1.0 + 0.5 * 1.0, 1e-6);

    double y2 = plant.linearStep(2.0);
    EXPECT_NEAR(y2, 0.5 * y1 + 0.5 * 2.0, 1e-6);
}

TEST(PlantModelTest, NonlinearStep)
{
    PlantModel plant(0.5, 0.1, 0.3, 0.1);
    plant.setState(1.0, 0.5);

    double y = plant.nonlinearStep(0.5);
    double expected = 0.5 * 1.0 - 0.1 * std::pow(1.0, 2) + 0.3 * 0.5 + 0.1 * std::sin(0.5);

    EXPECT_NEAR(y, expected, 1e-6);
}

TEST(SystemIntegrationTest, PControllerWithLinearPlant)
{
    PlantModel plant(0.8, 0.2, 0.0, 0.0);
    PIDController p_controller(2.0, 1.0, 0.0, 1.0);

    plant.setState(0.0, 0.0);
    p_controller.reset();

    std::vector<double> outputs;
    for (int i = 0; i < 10; i++)
    {
        double y = plant.getOutput();
        double e = 1.0 - y;
        double u = p_controller.calculate(e);
        plant.linearStep(u);
        outputs.push_back(y);
    }

    // Система должна стабилизироваться
    EXPECT_GT(outputs.back(), 0.0);
    EXPECT_LT(outputs.back(), 1.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```

## Результаты юнит-тестирования (GoogleTest)

![GoogleTest Output](images/gtest.png)
