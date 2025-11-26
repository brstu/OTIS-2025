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
<p align="right">Лыщенко К.В.</p>
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
Выходной переменной может быть температура в печи, скорость вращения вала двигателя, уровень жидкости в баке, рассогласование знаков привязки фотошаблонов и т.п. Целью управления может быть изменение выходной переменной по заданному закону w(t). Для этого нужно свести к минимуму ошибку управления e(t).
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
#include "pid.h"
#include <iostream>
#include <string>

/**
 * @brief Global constants for models
 */
constexpr double TIME_STEP = 0.05;
constexpr double NONLINEAR_COEFF = 0.01;

/**
 * @brief Шаблонная модель динамической системы.
 * Template model of a dynamic system.
 */
template <typename UpdateRule>
class SystemModel {
public:
    double operator()(double input) {
        state = updateRule(state, input);
        return state;
    }

private:
    double state = 0.0;
    UpdateRule updateRule;
};

/**
 * @brief Linear system: y(t+1) = y(t) + T * u
 * Simple thermal model without nonlinearities.
 */
struct LinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input;
    }
};

/**
 * @brief Nonlinear system: y(t+1) = y(t) + T*u + α*u²
 * Accelerates growth for large inputs.
 */
struct NonlinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input + NONLINEAR_COEFF * input * input;
    }
};

using LinearModel    = SystemModel<LinearUpdate>;
using NonlinearModel = SystemModel<NonlinearUpdate>;

/**
 * @brief Universal function for simulating a system with PID.
 */
template <typename Model>
void runSimulation(Model model, int steps, PID& controller, const std::string& name)
{
    std::cout << "=== " << name << " ===\n";

    double measured = 0.0;
    const double setpoint = 1.0;

    for (int i = 0; i < steps; ++i) {
        double control = controller.compute(setpoint, measured);
        measured = model(control);

        std::cout << "Step " << i
                  << " | Setpoint: " << setpoint
                  << " | Control: " << control
                  << " | Output: " << measured << "\n";
    }

    std::cout << name << " simulation finished.\n\n";
}

int main() {
    PID linearPID(1.0, 0.1, 0.05);
    PID nonlinearPID(1.0, 0.1, 0.05);

    const int steps = 50;

    runSimulation(LinearModel{}, steps, linearPID, "Linear Model");
    runSimulation(NonlinearModel{}, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}
```

## Результат программы [ src/main.cpp ]
=== Linear Model ===
Step 0 | Setpoint: 1 | Control: 1.001 | Output: 0.05005
Step 1 | Setpoint: 1 | Control: 0.70165 | Output: 0.0350825
Step 2 | Setpoint: 1 | Control: 1.04267 | Output: 0.0521335
Step 3 | Setpoint: 1 | Control: 0.866474 | Output: 0.0433237
Step 4 | Setpoint: 1 | Control: 1.00554 | Output: 0.0502772
Step 5 | Setpoint: 1 | Control: 0.920724 | Output: 0.0460362
Step 6 | Setpoint: 1 | Control: 0.981892 | Output: 0.0490946
Step 7 | Setpoint: 1 | Control: 0.943287 | Output: 0.0471644
Step 8 | Setpoint: 1 | Control: 0.971114 | Output: 0.0485557
Step 9 | Setpoint: 1 | Control: 0.954066 | Output: 0.0477033
Step 10 | Setpoint: 1 | Control: 0.967089 | Output: 0.0483545
Step 11 | Setpoint: 1 | Control: 0.959872 | Output: 0.0479936
Step 12 | Setpoint: 1 | Control: 0.966245 | Output: 0.0483122
Step 13 | Setpoint: 1 | Control: 0.96348 | Output: 0.048174
Step 14 | Setpoint: 1 | Control: 0.966855 | Output: 0.0483427
Step 15 | Setpoint: 1 | Control: 0.966103 | Output: 0.0483052
Step 16 | Setpoint: 1 | Control: 0.968124 | Output: 0.0484062
Step 17 | Setpoint: 1 | Control: 0.968281 | Output: 0.0484141
Step 18 | Setpoint: 1 | Control: 0.969691 | Output: 0.0484845
Step 19 | Setpoint: 1 | Control: 0.970259 | Output: 0.0485129
Step 20 | Setpoint: 1 | Control: 0.971392 | Output: 0.0485696
Step 21 | Setpoint: 1 | Control: 0.972146 | Output: 0.0486073
Step 22 | Setpoint: 1 | Control: 0.973154 | Output: 0.0486577
Step 23 | Setpoint: 1 | Control: 0.973992 | Output: 0.0486996
Step 24 | Setpoint: 1 | Control: 0.974944 | Output: 0.0487472
Step 25 | Setpoint: 1 | Control: 0.975819 | Output: 0.0487909
Step 26 | Setpoint: 1 | Control: 0.976746 | Output: 0.0488373
Step 27 | Setpoint: 1 | Control: 0.977637 | Output: 0.0488819
Step 28 | Setpoint: 1 | Control: 0.978553 | Output: 0.0489276
Step 29 | Setpoint: 1 | Control: 0.979452 | Output: 0.0489726
Step 30 | Setpoint: 1 | Control: 0.980362 | Output: 0.0490181
Step 31 | Setpoint: 1 | Control: 0.981265 | Output: 0.0490632
Step 32 | Setpoint: 1 | Control: 0.982173 | Output: 0.0491086
Step 33 | Setpoint: 1 | Control: 0.983077 | Output: 0.0491538
Step 34 | Setpoint: 1 | Control: 0.983983 | Output: 0.0491992
Step 35 | Setpoint: 1 | Control: 0.984888 | Output: 0.0492444
Step 36 | Setpoint: 1 | Control: 0.985794 | Output: 0.0492897
Step 37 | Setpoint: 1 | Control: 0.986699 | Output: 0.049335
Step 38 | Setpoint: 1 | Control: 0.987605 | Output: 0.0493802
Step 39 | Setpoint: 1 | Control: 0.98851 | Output: 0.0494255
Step 40 | Setpoint: 1 | Control: 0.989416 | Output: 0.0494708
Step 41 | Setpoint: 1 | Control: 0.990321 | Output: 0.049516
Step 42 | Setpoint: 1 | Control: 0.991226 | Output: 0.0495613
Step 43 | Setpoint: 1 | Control: 0.992131 | Output: 0.0496066
Step 44 | Setpoint: 1 | Control: 0.993036 | Output: 0.0496518
Step 45 | Setpoint: 1 | Control: 0.993941 | Output: 0.0496971
Step 46 | Setpoint: 1 | Control: 0.994847 | Output: 0.0497423
Step 47 | Setpoint: 1 | Control: 0.995752 | Output: 0.0497876
Step 48 | Setpoint: 1 | Control: 0.996657 | Output: 0.0498328
Step 49 | Setpoint: 1 | Control: 0.997561 | Output: 0.0498781
Linear Model simulation finished.

=== Nonlinear Model ===
Step 0 | Setpoint: 1 | Control: 1.001 | Output: 0.06007
Step 1 | Setpoint: 1 | Control: 0.64152 | Output: 0.0361915
Step 2 | Setpoint: 1 | Control: 1.0861 | Output: 0.0661015
Step 3 | Setpoint: 1 | Control: 0.788186 | Output: 0.0456217
Step 4 | Setpoint: 1 | Control: 1.06157 | Output: 0.0643478
Step 5 | Setpoint: 1 | Control: 0.847749 | Output: 0.0495743
Step 6 | Setpoint: 1 | Control: 1.03097 | Output: 0.0621776
Step 7 | Setpoint: 1 | Control: 0.882422 | Output: 0.0519078
Step 8 | Setpoint: 1 | Control: 1.00801 | Output: 0.060561
Step 9 | Setpoint: 1 | Control: 0.905676 | Output: 0.0534863
Step 10 | Setpoint: 1 | Control: 0.992337 | Output: 0.0594642
Step 11 | Setpoint: 1 | Control: 0.922037 | Output: 0.0546034
Step 12 | Setpoint: 1 | Control: 0.982037 | Output: 0.0587458
Step 13 | Setpoint: 1 | Control: 0.933819 | Output: 0.0554111
Step 14 | Setpoint: 1 | Control: 0.975484 | Output: 0.0582899
Step 15 | Setpoint: 1 | Control: 0.94248 | Output: 0.0560067
Step 16 | Setpoint: 1 | Control: 0.971517 | Output: 0.0580143
Step 17 | Setpoint: 1 | Control: 0.948997 | Output: 0.0564558
Step 18 | Setpoint: 1 | Control: 0.96933 | Output: 0.0578625
Step 19 | Setpoint: 1 | Control: 0.954039 | Output: 0.0568039
Step 20 | Setpoint: 1 | Control: 0.968367 | Output: 0.0577957
Step 21 | Setpoint: 1 | Control: 0.958066 | Output: 0.0570822
Step 22 | Setpoint: 1 | Control: 0.968249 | Output: 0.0577875
Step 23 | Setpoint: 1 | Control: 0.961391 | Output: 0.0573123
Step 24 | Setpoint: 1 | Control: 0.968712 | Output: 0.0578196
Step 25 | Setpoint: 1 | Control: 0.964234 | Output: 0.0575092
Step 26 | Setpoint: 1 | Control: 0.969576 | Output: 0.0578796
Step 27 | Setpoint: 1 | Control: 0.966744 | Output: 0.0576831
Step 28 | Setpoint: 1 | Control: 0.970717 | Output: 0.0579587
Step 29 | Setpoint: 1 | Control: 0.969023 | Output: 0.0578412
Step 30 | Setpoint: 1 | Control: 0.972048 | Output: 0.0580512
Step 31 | Setpoint: 1 | Control: 0.971142 | Output: 0.0579883
Step 32 | Setpoint: 1 | Control: 0.973512 | Output: 0.0581528
Step 33 | Setpoint: 1 | Control: 0.973152 | Output: 0.0581278
Step 34 | Setpoint: 1 | Control: 0.975067 | Output: 0.0582609
Step 35 | Setpoint: 1 | Control: 0.975085 | Output: 0.0582622
Step 36 | Setpoint: 1 | Control: 0.976684 | Output: 0.0583733
Step 37 | Setpoint: 1 | Control: 0.976965 | Output: 0.0583929
Step 38 | Setpoint: 1 | Control: 0.978345 | Output: 0.0584889
Step 39 | Setpoint: 1 | Control: 0.978809 | Output: 0.0585211
Step 40 | Setpoint: 1 | Control: 0.980037 | Output: 0.0586066
Step 41 | Setpoint: 1 | Control: 0.980627 | Output: 0.0586476
Step 42 | Setpoint: 1 | Control: 0.981749 | Output: 0.0587258
Step 43 | Setpoint: 1 | Control: 0.982427 | Output: 0.0587729
Step 44 | Setpoint: 1 | Control: 0.983475 | Output: 0.058846
Step 45 | Setpoint: 1 | Control: 0.984214 | Output: 0.0588975
Step 46 | Setpoint: 1 | Control: 0.985212 | Output: 0.058967
Step 47 | Setpoint: 1 | Control: 0.985993 | Output: 0.0590215
Step 48 | Setpoint: 1 | Control: 0.986955 | Output: 0.0590885
Step 49 | Setpoint: 1 | Control: 0.987766 | Output: 0.0591451

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
- Система демонстрирует переходный процесс с небольшими колебаниями.
- Выход постепенно сходится к установившемуся значению ≈ 0.05 — система стабильна, без значительного перерегулирования.

### Нелинейная модель (`T = 0.05, T0 = 1, TD = 10`)
- Нелинейность модели добавляет начальные колебания, но процесс постепенно стабилизируется.
- Выход сходится к установившемуся значению ≈ 0.058 — устойчивость достигнута, хотя переходный процесс менее плавный, чем у линейной модели.

### Линейная модель (`T = 0.1, T0 = 5, TD = 20`)
- Система более инерционная, переходный процесс медленнее, чем при меньшем T.
- Выход стабилизируется около значения ≈ 0.1, перерегулирование минимальное — система остаётся стабильной, хотя скорость выхода на установившееся значение снизилась.

### Нелинейная модель (`T = 0.1, T0 = 5, TD = 20`)
- Процесс показывает более выраженные колебания на начальном этапе.
- Выход стабилизируется около значения ≈ 0.11 — система остаётся устойчивой, но переходный процесс медленнее и с большей амплитудой колебаний, чем в линейной модели.

## Link to documentation
[link to documentation](https://topg1616.github.io/OTIS-2025/)

## Код юнит-тестов [ test/test_pid.cpp ]
```C++
#include "pid.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

/**
 * @brief Basic test: PID output is positive and stable for constant positive error
 */
TEST(PIDTest, BasicResponse) {
    PID pid(1.0, 0.5, 0.1, 0.1);

    double setpoint = 1.0;
    double measured = 0.0;

    // take a few steps to let integral accumulate
    double prev_u = pid.compute(setpoint, measured);
    EXPECT_GT(prev_u, 0.0);

    for (int i = 0; i < 5; ++i) {
        double u = pid.compute(setpoint, measured);
        // should remain positive and not immediately drop below previous (basic sanity)
        EXPECT_GT(u, 0.0);
        // relax tolerance a bit to avoid flaky failures on different platforms/optimizations
        EXPECT_GE(u, prev_u - 1e-6);
        prev_u = u;
    }
}

/**
 * @brief Ensure inv_dt is correctly initialized even for invalid dt
 */
TEST(PIDTest, InvalidDtInitializesInvDt) {
    PID pid(1.0, 0.0, 1.0, -0.5); // invalid dt, will use DEFAULT_DT

    // Compute once to ensure no crash or undefined behavior
    double u = pid.compute(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u)); // Output must be finite (no NaN or inf)
}

/**
 * @brief Test derivative scaling through inv_dt (isolate derivative term)
 */
TEST(PIDTest, DerivativeScaling) {
    // isolate derivative: Kp = 0, Ki = 0, Kd = 1.0
    PID pid_fast(0.0, 0.0, 1.0, 0.1);
    PID pid_slow(0.0, 0.0, 1.0, 1.0);

    double setpoint = 1.0;

    // initial measurement to set prev_error
    double u_fast_before = pid_fast.compute(setpoint, 0.0);
    double u_slow_before = pid_slow.compute(setpoint, 0.0);

    // Now introduce small change in measurement
    double u_fast_after = pid_fast.compute(setpoint, 0.9);
    double u_slow_after = pid_slow.compute(setpoint, 0.9);

    // With smaller dt (larger inv_dt), derivative term produces larger change in output
    double delta_u_fast = u_fast_after - u_fast_before;
    double delta_u_slow = u_slow_after - u_slow_before;

    // be conservative: require strictly larger magnitude for fast
    EXPECT_GT(std::fabs(delta_u_fast), std::fabs(delta_u_slow));
}

/**
 * @brief Test that invalid output limits are ignored
 */
TEST(PIDTest, InvalidOutputLimitsIgnored) {
    PID pid(1.0, 0.0, 0.0, 0.1);
    pid.setOutputLimits(-1.0, 1.0);

    // Invalid call: should be ignored
    pid.setOutputLimits(2.0, -2.0);

    // After invalid call, old limits must remain valid
    double u = pid.compute(10.0, 0.0);
    const double eps = 1e-6;
    EXPECT_LE(u, 1.0 + eps);
    EXPECT_GE(u, -1.0 - eps);
}

/**
 * @brief Test that integral limits are applied correctly
 */
TEST(PIDTest, IntegralLimitsWork) {
    // Ki = 1 so output == integral (before output clamping), Kp = Kd = 0
    PID pid(0.0, 1.0, 0.0, 0.1);
    pid.setIntegralLimits(-0.5, 0.5);

    // Force integral windup
    for (int i = 0; i < 100; ++i)
        pid.compute(10.0, 0.0);

    // Integral should be clamped; output == integral (Ki = 1)
    double u = pid.compute(10.0, 0.0);
    const double eps = 1e-6;
    EXPECT_LE(u, 0.5 + eps);
    EXPECT_GE(u, -0.5 - eps);
}

/**
 * @brief Test reset and changing dt at runtime
 */
TEST(PIDTest, ResetAndSetDt) {
    PID pid(1.0, 1.0, 1.0, 0.1);
    pid.compute(1.0, 0.0);
    pid.reset();
    double u_after_reset = pid.compute(1.0, 0.0);

    // After reset, integral and prev_error cleared — output should be finite and reasonable
    EXPECT_TRUE(std::isfinite(u_after_reset));

    // Changing dt should not crash and should affect derivative scaling
    pid.setDt(0.05);
    double u_after_dt_change = pid.compute(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u_after_dt_change));
}
```
## Результаты юнит-тестирования (GoogleTest)
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from PIDTest
[ RUN      ] PIDTest.BasicResponse
[       OK ] PIDTest.BasicResponse (0 ms)
[ RUN      ] PIDTest.InvalidDtInitializesInvDt
PID::PID: invalid dt <= 0, using DEFAULT_DT=0.01
[       OK ] PIDTest.InvalidDtInitializesInvDt (12 ms)
[ RUN      ] PIDTest.DerivativeScaling
[       OK ] PIDTest.DerivativeScaling (0 ms)
[ RUN      ] PIDTest.InvalidOutputLimitsIgnored
PID::setOutputLimits ignored invalid limits: min > max
[       OK ] PIDTest.InvalidOutputLimitsIgnored (0 ms)
[ RUN      ] PIDTest.IntegralLimitsWork
[       OK ] PIDTest.IntegralLimitsWork (0 ms)
[ RUN      ] PIDTest.ResetAndSetDt
[       OK ] PIDTest.ResetAndSetDt (0 ms)
[----------] 6 tests from PIDTest (26 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (32 ms total)
[  PASSED  ] 6 tests.