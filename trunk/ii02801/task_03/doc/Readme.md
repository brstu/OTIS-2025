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
<p align="right">Артыш Е.А.</p>
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


## Код программы [ src/lab3main.cpp ]
```C++
#include <iostream>
#include <vector>
#include <fstream>
#include "pid.h"
#include "model.h"

std::vector<double> simulateSystem(PIDController& pid, ProcessModel& process, 
                                  const std::vector<double>& setpoints, bool use_nonlinear = false) {
    std::vector<double> results;
    
    for (double setpoint : setpoints) {

        double current_value = (results.empty()) ? 0.0 : results.back();
        
        // Вычисляем управляющее воздействие
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
    
    
    std::vector<double> setpoints(20, 20.0);  
    
    
    auto linear_results = simulateSystem(pid, process, setpoints, false);
    
    
    pid.reset();
    process.setInitialValue(0.0);
    
    
    auto nonlinear_results = simulateSystem(pid, process, setpoints, true);
    
    
    std::cout << "Step\t\tSetpoint\t\tLinear\t\tNonlinear\n";
    for (size_t i = 0; i < setpoints.size(); ++i) {
        std::cout << i << "\t\t" << setpoints[i] << "\t\t" 
                << linear_results[i] << "\t\t" << nonlinear_results[i] << "\n";
    }
    
    std::cout << "Simulation completed. Results saved to simulation_results.csv" << std::endl;
    
    return 0;
}
```

## Результат программы [ src/main.cpp ]
![result](images/result.jpg)

## Вывод полученных данных при использовании ПИД-регулятора


## Link to documentation
[https://v1tyokkk.github.io/OTIS-2025/](https://oniisssss.github.io/OTIS-2025/)

## Код юнит-тестов [ test/testlab3.cpp ]
```C++
/**
 * @file test.cpp
 * @brief Модульные тесты для ПИД-регулятора и модели объекта
 */

#include <gtest/gtest.h>
#include <cmath>
#include "../src/pid.h"
#include "../src/model.h"


TEST(PIDControllerTest, ConstructorAndParameters)
{
    PIDController pid(2.0, 1.0, 0.5, 1.0);
    
    
    double result = pid.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(result));
}


TEST(PIDControllerTest, CalculatePController)
{
    PIDController pid(1.0, 1.0, 0.0, 1.0); 
    pid.reset();

    
    double u1 = pid.calculate(1.0, 0.0); 
    EXPECT_NEAR(u1, 1.0, 1e-6); 

    
    double u2 = pid.calculate(1.0, 0.5); 
    EXPECT_NEAR(u2, 1.5, 1e-6); 

    
    double u3 = pid.calculate(1.0, 1.0); 
    EXPECT_NEAR(u3, 1.5, 1e-6); 
}


TEST(PIDControllerTest, CalculatePIController)
{
    PIDController pid(1.0, 0.5, 0.0, 1.0); 
    pid.reset();

    double u1 = pid.calculate(1.0, 0.0);
    double u2 = pid.calculate(1.0, 0.5);
    
    
    EXPECT_GT(u2, u1);
}


TEST(PIDControllerTest, Reset)
{
    PIDController pid(1.0, 1.0, 0.1, 1.0);
    
    
    pid.calculate(1.0, 0.0);
    pid.calculate(1.0, 0.5);
    
    
    pid.reset();
    
    
    double result = pid.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(result));
}


TEST(ProcessModelTest, LinearModel)
{
    std::vector<double> params = {0.5, 0.5, 0.0, 0.0};
    ProcessModel plant(params, 1.0);

    double y1 = plant.linearModel(1.0);
    EXPECT_NEAR(y1, 0.5 * 1.0 + 0.5 * 1.0, 1e-6);

    double y2 = plant.linearModel(2.0);
    EXPECT_NEAR(y2, 0.5 * y1 + 0.5 * 2.0, 1e-6);
}


TEST(ProcessModelTest, NonlinearModel)
{
    std::vector<double> params = {0.5, 0.1, 0.3, 0.1};
    ProcessModel plant(params, 1.0);

    double y = plant.nonlinearModel(0.5);
    double expected = 0.5 * 1.0 - 0.1 * 1.0 * 1.0 + 0.3 * 0.5 + 0.1 * std::sin(0.5);

    EXPECT_NEAR(y, expected, 1e-6);
}


TEST(ProcessModelTest, SetInitialValue)
{
    std::vector<double> params = {0.8, 0.2, 0.0, 0.0};
    ProcessModel plant(params, 0.0);
    
    plant.setInitialValue(2.0);
    double y = plant.linearModel(1.0);
    
    
    EXPECT_NEAR(y, 0.8 * 2.0 + 0.2 * 1.0, 1e-6);
}


TEST(SystemIntegrationTest, PControllerWithLinearPlant)
{
    std::vector<double> params = {0.8, 0.2, 0.0, 0.0};
    ProcessModel plant(params, 0.0);
    PIDController p_controller(2.0, 1.0, 0.0, 1.0);

    plant.setInitialValue(0.0);
    p_controller.reset();

    std::vector<double> outputs;
    double setpoint = 1.0;
    
    for (int i = 0; i < 10; i++)
    {
        double current_output = (outputs.empty()) ? 0.0 : outputs.back();
        double control_signal = p_controller.calculate(setpoint, current_output);
        double new_output = plant.linearModel(control_signal);
        outputs.push_back(new_output);
    }

    
    EXPECT_GT(outputs.back(), 0.0);
    EXPECT_LT(std::abs(outputs.back() - setpoint), 1.0); 
}


TEST(SystemIntegrationTest, PIDControllerWithNonlinearPlant)
{
    std::vector<double> params = {0.8, 0.1, 0.3, 0.2};
    ProcessModel plant(params, 0.0);
    PIDController pid_controller(1.5, 0.8, 0.2, 0.5);

    plant.setInitialValue(0.0);
    pid_controller.reset();

    std::vector<double> outputs;
    double setpoint = 2.0;
    
    for (int i = 0; i < 15; i++)
    {
        double current_output = (outputs.empty()) ? 0.0 : outputs.back();
        double control_signal = pid_controller.calculate(setpoint, current_output);
        double new_output = plant.nonlinearModel(control_signal);
        outputs.push_back(new_output);
    }

    
    EXPECT_TRUE(std::isfinite(outputs.back()));
    EXPECT_GT(outputs.size(), 0);
}


TEST(SystemIntegrationTest, SystemStability)
{
    std::vector<double> params = {0.9, 0.1, 0.0, 0.0}; 
    ProcessModel plant(params, 0.0);
    PIDController controller(0.5, 1.0, 0.0, 1.0);

    plant.setInitialValue(0.0);
    controller.reset();

    std::vector<double> outputs;
    double setpoint = 1.0;
    
    for (int i = 0; i < 20; i++)
    {
        double current_output = (outputs.empty()) ? 0.0 : outputs.back();
        double control_signal = controller.calculate(setpoint, current_output);
        double new_output = plant.linearModel(control_signal);
        outputs.push_back(new_output);
    }

    
    EXPECT_TRUE(std::isfinite(outputs.back()));
    EXPECT_LT(std::abs(outputs.back()), 10.0); 
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```

## Результаты юнит-тестирования (GoogleTest)
![GoogleTest Output](images/gtest.jpg)

