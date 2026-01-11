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
<p align="right">Олексюк И.В.</p>
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
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "pid_controller.h"
#include "model.h"

double nonlinearModelUpdate(double u, double dt) {
    static double y_prev_nl = 0.0;
    const double K_nl = 1.0;
    const double T_nl = 0.5;
    const double a = 1.0 - dt / T_nl;
    const double b = K_nl * dt / T_nl;
    double y = a * y_prev_nl + b * u;

    if (y > 25.0) {
        y = 25.0;
    }
    if (y < -25.0) {
        y = -25.0;
    }

    y_prev_nl = y;
    return y;
}

std::vector<double> simulateSystem(PIDController& pid,
    const std::vector<double>& setpoints,
    bool use_nonlinear = false,
    double dt = 0.1) {

    std::vector<double> results;
    results.reserve(setpoints.size());

    if (!use_nonlinear) {
        modelInit(1.0, 0.5);
    }

    double current_value = 0.0;

    for (const double& setpoint : setpoints) {
        const double control_signal = pid.calculate(setpoint, current_value);
        double new_value;

        if (use_nonlinear) {
            new_value = nonlinearModelUpdate(control_signal, dt);
        }
        else {
            new_value = modelUpdate(control_signal, dt);
        }

        results.push_back(new_value);
        current_value = new_value;
    }

    return results;
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "=== SIMULATION СИСТЕМЫ УПРАВЛЕНИЯ ===\n\n";

    const double K = 0.8;
    const double Ti = 4.0;
    const double Td = 0.05;
    const double T = 0.1;

    PIDController pid(K, Ti, Td, T);

    std::vector<double> setpoints;
    setpoints.reserve(35);

    for (int i = 0; i < 15; ++i) {
        setpoints.push_back(20.0);
    }
    for (int i = 0; i < 10; ++i) {
        setpoints.push_back(5.0);
    }
    for (int i = 0; i < 10; ++i) {
        setpoints.push_back(15.0);
    }

    std::cout << "1. LINEAR MODEL SIMULATION:\n";
    pid.reset();
    modelInit(1.0, 0.5);
    const auto linear_results = simulateSystem(pid, setpoints, false, T);

    std::cout << "\n2. NONLINEAR MODEL SIMULATION:\n";
    PIDController pid_nl(K, Ti, Td, T);
    pid_nl.reset();
    const auto nonlinear_results = simulateSystem(pid_nl, setpoints, true, T);

    std::cout << "\n3. COMPARISON RESULTS:\n";
    std::cout << std::string(75, '=') << "\n";
    std::cout << std::setw(6) << "Step"
        << std::setw(12) << "Setpoint"
        << std::setw(18) << "Linear Output"
        << std::setw(18) << "Nonlinear"
        << std::setw(15) << "Control" << "\n";
    std::cout << std::string(75, '-') << "\n";

    pid.reset();
    modelInit(1.0, 0.5);
    double current_value = 0.0;

    for (size_t i = 0; i < setpoints.size(); ++i) {
        const double control_signal = pid.calculate(setpoints[i], current_value);
        current_value = modelUpdate(control_signal, T);

        if (std::fabs(current_value - linear_results[i]) > 0.001) {
            std::cerr << "Warning: mismatch at step " << i
                << ": " << current_value << " vs " << linear_results[i] << std::endl;
        }

        std::cout << std::setw(6) << i
            << std::setw(12) << std::fixed << std::setprecision(2) << setpoints[i]
            << std::setw(18) << std::setprecision(4) << linear_results[i]
            << std::setw(18) << nonlinear_results[i]
            << std::setw(15) << std::setprecision(3) << control_signal << "\n";

        if (i % 10 == 9) {
            std::cout << std::string(75, '-') << "\n";
        }
    }
    std::cout << "\n4. PERFORMANCE ANALYSIS:\n";
    std::cout << std::string(50, '-') << "\n";

    const int ANALYSIS_START = 20;
    const int ANALYSIS_END = 25;

    if (const int steady_start = ANALYSIS_START;
        steady_start < static_cast<int>(linear_results.size()) &&
        ANALYSIS_END < static_cast<int>(linear_results.size())) {

        const int steady_end = ANALYSIS_END;
        double lin_sum = 0.0;
        double nl_sum = 0.0;
        int count = 0;

        for (int i = steady_start; i <= steady_end; ++i) {
            lin_sum += linear_results[i];
            nl_sum += nonlinear_results[i];
            ++count;
        }

        const double lin_avg = lin_sum / count;
        const double nl_avg = nl_sum / count;

        std::cout << "Steady-state average (target = 20.0):\n";
        std::cout << "  Linear model:    " << std::setprecision(3) << lin_avg << "\n";
        std::cout << "  Nonlinear model: " << nl_avg << "\n";
        std::cout << "  Difference:      " << (nl_avg - lin_avg)
            << " (" << std::setprecision(1)
            << std::fabs(100.0 * (nl_avg - lin_avg) / lin_avg) << "%)\n";
    }
    else {
        std::cout << "Warning: Not enough data for steady-state analysis\n";
    }
        double lin_max = 0.0;
        double nl_max = 0.0;

        for (const double& value : linear_results) {
            if (value > lin_max) {
                lin_max = value;
            }
        }

        for (const double& value : nonlinear_results) {
            if (value > nl_max) {
                nl_max = value;
            }
        }

        std::cout << "\nMaximum overshoot:\n";
        std::cout << "  Linear model:    " << std::setprecision(3) << lin_max << "\n";
        std::cout << "  Nonlinear model: " << nl_max << "\n";

        std::cout << "\n5. SYSTEM PARAMETERS:\n";
        std::cout << std::string(30, '-') << "\n";

        double pK = 0.0;
        double pTi = 0.0;
        double pTd = 0.0;
        double pT = 0.0;

        pid.getParameters(pK, pTi, pTd, pT);

        std::cout << "PID Controller:\n";
        std::cout << "  K = " << pK << ", Ti = " << pTi
            << ", Td = " << pTd << ", T = " << pT << "\n";

        std::cout << "\nSimulation parameters:\n";
        std::cout << "  Total steps: " << setpoints.size() << "\n";
        std::cout << "  Time step (dt): " << T << " sec\n";
        std::cout << "  Model: K_obj = 1.0, T_obj = 0.5\n";

        std::cout << "\n" << std::string(75, '=') << "\n";
        std::cout << "SIMULATION COMPLETED SUCCESSFULLY!\n";

        return 0;
    }
```

## Результат программы [ src/main.cpp ]
![result](images/results.png)

## Вывод полученных данных при использовании ПИД-регулятора

## Link to documentation
[https://OleksyukIlya.github.io/OTIS-2025/](https://OleksyukIlya.github.io/OTIS-2025/)

## Код юнит-тестов [ test/testlab3.cpp ]
```C++
#include <cmath>
#include <vector>
#include <gtest/gtest.h>
#include "pid_controller.h"

TEST(PIDControllerTest, ConstructorAndParameters) {
    PIDController pid(2.0, 0.5, 0.1, 0.01);
    double K = 0.0;
    double Ti = 0.0;
    double Td = 0.0;
    double T = 0.0;

    pid.getParameters(K, Ti, Td, T);
    EXPECT_DOUBLE_EQ(K, 2.0);
    EXPECT_DOUBLE_EQ(Ti, 0.5);
    EXPECT_DOUBLE_EQ(Td, 0.1);
    EXPECT_DOUBLE_EQ(T, 0.01);
}

TEST(PIDControllerTest, CalculateZeroError) {
    PIDController pid(1.0, 0.1, 0.05, 0.01);
    const double u = pid.calculate(1.0, 1.0);
    EXPECT_NEAR(u, 0.0, 1e-6);
}

TEST(PIDControllerTest, CalculateConstantError) {
    PIDController pid(2.0, 0.2, 0.0, 0.01);
    const double u1 = pid.calculate(1.0, 0.0);
    const double u2 = pid.calculate(1.0, 0.0);
    EXPECT_GT(u2, u1);
}

TEST(PIDControllerTest, ResetController) {
    PIDController pid(1.0, 0.1, 0.05, 0.01);
    pid.calculate(1.0, 0.0);
    pid.calculate(1.0, 0.5);
    pid.reset();
    const double u = pid.calculate(1.0, 1.0);
    EXPECT_NEAR(u, 0.0, 1e-6);
}

TEST(PIDControllerTest, SetParameters) {
    PIDController pid(1.0, 0.1, 0.05, 0.01);
    pid.setParameters(2.0, 0.2, 0.1, 0.02);
    double K = 0.0;
    double Ti = 0.0;
    double Td = 0.0;
    double T = 0.0;

    pid.getParameters(K, Ti, Td, T);
    EXPECT_DOUBLE_EQ(K, 2.0);
    EXPECT_DOUBLE_EQ(Ti, 0.2);
    EXPECT_DOUBLE_EQ(Td, 0.1);
    EXPECT_DOUBLE_EQ(T, 0.02);
}

TEST(PIDControllerTest, PControllerBehavior) {
    PIDController p_controller(10.0, 0.0, 0.0, 0.01);
    p_controller.reset();
    const double u1 = p_controller.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u1));

    const double u2 = p_controller.calculate(1.0, 0.5);
    EXPECT_TRUE(std::isfinite(u2));
}

TEST(PIDControllerTest, PIDControllerStepResponse) {
    PIDController pid(10.0, 0.1, 0.05, 0.01);
    pid.reset();

    const std::vector<double> errors = { 1.0, 0.8, 0.6, 0.4, 0.2 };
    std::vector<double> controls;
    controls.reserve(errors.size());

    for (const double error : errors) {
        const double control = pid.calculate(error, 0.0);
        controls.push_back(control);
    }

    EXPECT_EQ(controls.size(), errors.size());

    for (const auto& control : controls) {
        EXPECT_TRUE(std::isfinite(control));
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
## Результаты юнит-тестирования (GoogleTest)
![GoogleTest Output](images/tests.png)