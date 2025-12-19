<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Реализация ПИД регулятора.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Киричук В.А.</p>
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
#include <fstream>
#include <iomanip>
#include <vector>
#include "nonlinear.h"
#include "pid.h"

/**
 * @brief Сохраняет данные в CSV файл
 * 
 * @param filename Имя файла для сохранения
 * @param time Вектор временных меток
 * @param values Вектор значений
 * @param setpoint Заданное значение (опционально)
 * @return true Файл успешно сохранен
 * @return false Ошибка при сохранении
 */
bool saveToCSV(const std::string& filename, 
               const std::vector<int>& time, 
               const std::vector<double>& values,
               double setpoint = 0.0);

int main()
{
    NonLinearCoeff nonlinearCoeff;
    nonlinearCoeff.a = 0.5;
    nonlinearCoeff.b = 0.2;
    nonlinearCoeff.c = 0.15;
    nonlinearCoeff.d = 0.3;
    nonlinearCoeff.u = 1.2;
    
    double y0;
    std::cout << "Enter initial temperature y1: ";
    std::cin >> y0;
    
    int n = 20;
    double setpoint = 2.0;
    
    double Kp = 1.5;
    double Ki = 0.2;
    double Kd = 0.05;
    
    std::cout << "\n=== Temperature Regulation System Simulation ===\n";
    std::cout << "Initial temperature: " << y0 << "\n";
    std::cout << "Desired temperature: " << setpoint << "\n";
    std::cout << "Number of steps: " << n << "\n";
    std::cout << "PID parameters: Kp=" << Kp << ", Ki=" << Ki << ", Kd=" << Kd << "\n\n";
    
    std::cout << "1. System without regulator:" << std::endl;
    std::vector<double> nonlinearResults = calculateNonlinear(nonlinearCoeff, y0, n);
    
    std::vector<int> timeSteps(n);
    for (int i = 0; i < n; i++) {
        timeSteps[i] = i + 1;
    }
    
    if (saveToCSV("temperature_without_pid.csv", timeSteps, nonlinearResults, setpoint)) {
        std::cout << "   Results saved to temperature_without_pid.csv\n";
    }
    
    for (int i = 0; i < std::min(5, n); i++) {
        std::cout << "   t" << i + 1 << " = " << nonlinearResults[i];
        std::cout << " (deviation: " << std::abs(setpoint - nonlinearResults[i]) << " )" << std::endl;
    }
    if (n > 5) {
        std::cout << "   ...\n";
        std::cout << "   t" << n << " = " << nonlinearResults[n-1];
        std::cout << " (deviation: " << std::abs(setpoint - nonlinearResults[n-1]) << " )" << std::endl;
    }
    
    std::cout << "\n2. System with PID regulator:" << std::endl;
    std::vector<double> pidResults = simulatePidRegulatorForNonlinear(
        nonlinearCoeff, y0, n, setpoint, Kp, Ki, Kd);
    
    if (saveToCSV("temperature_with_pid.csv", timeSteps, pidResults, setpoint)) {
        std::cout << "   Results saved to temperature_with_pid.csv\n";
    }
    
    for (int i = 0; i < std::min(5, n); i++) {
        std::cout << "   t" << i + 1 << " = " << pidResults[i];
        std::cout << " (deviation: " << std::abs(setpoint - pidResults[i]) << " )" << std::endl;
    }
    if (n > 5) {
        std::cout << "   ...\n";
        std::cout << "   t" << n << " = " << pidResults[n-1];
        std::cout << " (deviation: " << std::abs(setpoint - pidResults[n-1]) << " )" << std::endl;
    }

    std::cout << "\n3. Efficiency comparison:" << std::endl;
    
    double sumErrorWithoutPID = 0.0;
    double sumErrorWithPID = 0.0;
    
    for (int i = 0; i < n; i++) {
        sumErrorWithoutPID += std::abs(setpoint - nonlinearResults[i]);
        sumErrorWithPID += std::abs(setpoint - pidResults[i]);
    }
    
    double avgErrorWithoutPID = sumErrorWithoutPID / n;
    double avgErrorWithPID = sumErrorWithPID / n;
    
    std::cout << "   Average deviation without regulator: " << avgErrorWithoutPID << "\n";
    std::cout << "   Average deviation with PID regulator: " << avgErrorWithPID << "\n";
    
    double improvement = ((avgErrorWithoutPID - avgErrorWithPID) / avgErrorWithoutPID) * 100;
    std::cout << "   Improvement: " << std::fixed << std::setprecision(1) << improvement << "%\n";
    
    std::ofstream summary("simulation_summary.txt");
    if (summary.is_open()) {
        summary << "=== Simulation Summary ===\n";
        summary << "Initial temperature: " << y0 << "\n";
        summary << "Desired temperature: " << setpoint << "\n";
        summary << "Number of steps: " << n << "\n";
        summary << "PID parameters: Kp=" << Kp << ", Ki=" << Ki << ", Kd=" << Kd << "\n";
        summary << "Average error without PID: " << avgErrorWithoutPID << "\n";
        summary << "Average error with PID: " << avgErrorWithPID << "\n";
        summary << "Improvement: " << improvement << "%\n";
        summary << "\nTo plot graphs run: python plot_temperature.py\n";
        summary.close();
        std::cout << "\nSummary saved to simulation_summary.txt\n";
    }
    
    std::cout << "\nTo plot graphs run the command: python plot_temperature.py\n";
    
    return 0;
}

bool saveToCSV(const std::string& filename, 
               const std::vector<int>& time, 
               const std::vector<double>& values,
               double setpoint)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    
    file << "Time,Value";
    if (setpoint != 0.0) {
        file << ",Setpoint";
    }
    file << std::endl;
    
    for (size_t i = 0; i < values.size(); ++i) {
        file << time[i] << "," << std::fixed << std::setprecision(6) << values[i];
        if (setpoint != 0.0) {
            file << "," << setpoint;
        }
        file << std::endl;
    }
    
    file.close();
    std::cout << "Data saved to file: " << filename << std::endl;
    return true;
}
```

## Результат программы [ src/main.cpp ]
![results](images/results.png)

## Код юнит-тестов [ test/test.cpp ]
```C++
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/pid.h"

TEST(TestPid, WhenSetpointIsTwo)
{   
    NonLinearCoeff coeff;
    coeff.a = 0.5;
    coeff.b = 0.2;
    coeff.c = 0.15;
    coeff.d = 0.3;
    coeff.u = 1.2;
    
    double y0 = 1.0;
    int n = 5;
    double setpoint = 2.0;
    
    std::vector<double> results = simulatePidRegulatorForNonlinear(coeff, y0, n, setpoint);
    std::vector<double> expected = {
        1.0,
        0.73520960570401428,
        0.69080628322815185,
        0.78596368906104797,
        0.84912544875185891
    };
    
    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_NEAR(results[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}

TEST(TestPid, WhenCustomPidCoefficients)
{   
    NonLinearCoeff coeff;
    coeff.a = 0.5;
    coeff.b = 0.2;
    coeff.c = 0.15;
    coeff.d = 0.3;
    coeff.u = 1.2;
    
    double y0 = 1.0;
    int n = 5;
    double setpoint = 3.0;
    double Kp = 2.0;
    double Ki = 0.5;
    double Kd = 0.1;
    double dt = 1.0;
    
    std::vector<double> results = simulatePidRegulatorForNonlinear(
        coeff, y0, n, setpoint, Kp, Ki, Kd, dt);
    std::vector<double> expected = {
        1.0,
        0.81496360328395412,
        1.2386319653734363,
        1.5053874385565871,
        1.5651009452716802
    };
    
    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_NEAR(results[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}
```

## Тестирование
![tests](images/tests.png)

## Графики
[graph](images/graph.png)

## Документация
[https://kriskess.github.io/OTIS-2025/](https://kriskess.github.io/OTIS-2025/)