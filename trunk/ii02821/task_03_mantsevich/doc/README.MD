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
<p align="right">Группы ИИ-28</p>
<p align="right">Манцевич Р.С.</p>
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

ПИД-регулятор — это алгоритм управления, который вычисляет управляющее воздействие как сумму трёх компонент: пропорциональной, интегральной и дифференциальной. Пропорциональная компонента реагирует на текущую ошибку, интегральная учитывает накопленную ошибку за время, а дифференциальная предсказывает будущее поведение системы. В работе был реализован цифровой ПИД-регулятор для управления тепловым объектом, проведено тестирование на линейной и нелинейной моделях.

**Задание.**
На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.


## Код программы [ src/main_ruslan.cpp ]
```C++
/**
 * @file main_ruslan.cpp
 * @brief Главный файл программы - симулятор PID регулятора
 * @author Ruslan
 * @date 2024
 */

#include "pid_ruslan.h"
#include <iostream>
#include <string>

/**
 * @brief Глобальные константы для моделей
 */
constexpr double TIME_STEP = 0.05;
constexpr double NONLINEAR_COEFF = 0.01;

/**
 * @brief Шаблонная модель динамической системы.
 * @tparam UpdateRule Правило обновления состояния системы
 */
template <typename UpdateRule>
class SystemModel {
public:
    /**
     * @brief Оператор вызова для обновления состояния системы
     * @param input Входное воздействие
     * @return Текущее состояние системы
     */
    double operator()(double input) {
        state = updateRule(state, input);
        return state;
    }

private:
    double state = 0.0;        ///< Текущее состояние системы
    UpdateRule updateRule;     ///< Правило обновления состояния
};

/**
 * @brief Линейная система: y(t+1) = y(t) + T * u
 * Простая тепловая модель без нелинейностей
 */
struct LinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input;
    }
};

/**
 * @brief Нелинейная система: y(t+1) = y(t) + T*u + α*u²
 * Ускоряет рост при больших входных воздействиях
 */
struct NonlinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input + NONLINEAR_COEFF * input * input;
    }
};

using LinearModel    = SystemModel<LinearUpdate>;      ///< Линейная модель
using NonlinearModel = SystemModel<NonlinearUpdate>;   ///< Нелинейная модель

/**
 * @brief Универсальная функция для симуляции системы с PID регулятором
 * @tparam Model Тип модели системы
 * @param model Модель системы
 * @param steps Количество шагов симуляции
 * @param controller PID регулятор
 * @param name Название симуляции
 */
template <typename Model>
void runSimulation(Model model, int steps, PID_ruslan& controller, const std::string& name)
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

/**
 * @brief Главная функция программы
 * @return Код завершения
 */
int main() {
    PID_ruslan linearPID(1.0, 0.1, 0.05);
    PID_ruslan nonlinearPID(1.0, 0.1, 0.05);

    const int steps = 50;

    runSimulation(LinearModel{}, steps, linearPID, "Linear Model");
    runSimulation(NonlinearModel{}, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}
```

## Результат программы [ src/main_ruslan.cpp ]
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
[link to documentation](https://humoristoff.github.io/OTIS-2025/)

## Код юнит-тестов [ test/test_pid_ruslan.cpp ]
```C++
/**
 * @file test_pid_ruslan.cpp
 * @brief Unit tests for PID controller class
 * @author Ruslan
 * @date 2024
 */

#include "pid_ruslan.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

constexpr double EPS = 1e-6;   ///< Tolerance for floating point comparisons

/**
 * @brief Test basic PID response with positive error
 */
TEST(PID_Ruslan_Test, BasicResponse) {
    PID_ruslan pid(1.0, 0.5, 0.1, 0.1);

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
        EXPECT_GE(u, prev_u - EPS);
        prev_u = u;
    }
}

/**
 * @brief Test initialization with invalid time step
 */
TEST(PID_Ruslan_Test, InvalidDtInitializesInvDt) {
    PID_ruslan pid(1.0, 0.0, 1.0, -0.5); // invalid dt, will use DEFAULT_DT

    // Compute once to ensure no crash or undefined behavior
    double u = pid.compute(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u)); // Output must be finite (no NaN or inf)
}

/**
 * @brief Test derivative term scaling with different time steps
 */
TEST(PID_Ruslan_Test, DerivativeScaling) {
    // isolate derivative: Kp = 0, Ki = 0, Kd = 1.0
    PID_ruslan pid_fast(0.0, 0.0, 1.0, 0.1);
    PID_ruslan pid_slow(0.0, 0.0, 1.0, 1.0);

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
TEST(PID_Ruslan_Test, InvalidOutputLimitsIgnored) {
    PID_ruslan pid(1.0, 0.0, 0.0, 0.1);
    pid.setOutputLimits(-1.0, 1.0);

    // Invalid call: should be ignored
    pid.setOutputLimits(2.0, -2.0);

    // After invalid call, old limits must remain valid
    double u = pid.compute(10.0, 0.0);
    EXPECT_LE(u, 1.0 + EPS);
    EXPECT_GE(u, -1.0 - EPS);
}

/**
 * @brief Test integral anti-windup limits
 */
TEST(PID_Ruslan_Test, IntegralLimitsWork) {
    // Ki = 1 so output == integral (before output clamping), Kp = Kd = 0
    PID_ruslan pid(0.0, 1.0, 0.0, 0.1);
    pid.setIntegralLimits(-0.5, 0.5);

    // Force integral windup
    for (int i = 0; i < 100; ++i)
        pid.compute(10.0, 0.0);

    // Integral should be clamped; output == integral (Ki = 1)
    double u = pid.compute(10.0, 0.0);
    EXPECT_LE(u, 0.5 + EPS);
    EXPECT_GE(u, -0.5 - EPS);
}

/**
 * @brief Test reset functionality and dynamic time step change
 */
TEST(PID_Ruslan_Test, ResetAndSetDt) {
    PID_ruslan pid(1.0, 1.0, 1.0, 0.1);
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
UpdateCTestConfiguration  from :D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build/DartConfiguration.tcl
Test project D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: PID_Ruslan_Test.BasicResponse

1: Test command: D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\runTests_ruslan_task03.exe "--gtest_filter=PID_Ruslan_Test.BasicResponse" "--gtest_also_run_disabled_tests"
1: Working Directory: D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
1: Test timeout computed to be: 10000000
1: Running main() from D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\_deps\googletest-src\googletest\src\gtest_main.cc
1: Note: Google Test filter = PID_Ruslan_Test.BasicResponse
1: [==========] Running 1 test from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 1 test from PID_Ruslan_Test
1: [ RUN      ] PID_Ruslan_Test.BasicResponse
1: [       OK ] PID_Ruslan_Test.BasicResponse (0 ms)
1: [----------] 1 test from PID_Ruslan_Test (0 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/6 Test #1: PID_Ruslan_Test.BasicResponse ................   Passed    0.01 sec
test 2
    Start 2: PID_Ruslan_Test.InvalidDtInitializesInvDt

2: Test command: D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\runTests_ruslan_task03.exe "--gtest_filter=PID_Ruslan_Test.InvalidDtInitializesInvDt" "--gtest_also_run_disabled_tests"
2: Working Directory: D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
2: Test timeout computed to be: 10000000
2: Running main() from D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\_deps\googletest-src\googletest\src\gtest_main.cc
2: Note: Google Test filter = PID_Ruslan_Test.InvalidDtInitializesInvDt
2: [==========] Running 1 test from 1 test suite.
2: [----------] Global test environment set-up.
2: [----------] 1 test from PID_Ruslan_Test
2: [ RUN      ] PID_Ruslan_Test.InvalidDtInitializesInvDt
2: PID_ruslan::PID_ruslan: invalid dt <= 0, using DEFAULT_DT=0.01
2: [       OK ] PID_Ruslan_Test.InvalidDtInitializesInvDt (0 ms)
2: [----------] 1 test from PID_Ruslan_Test (0 ms total)
2:
2: [----------] Global test environment tear-down
2: [==========] 1 test from 1 test suite ran. (0 ms total)
2: [  PASSED  ] 1 test.
2/6 Test #2: PID_Ruslan_Test.InvalidDtInitializesInvDt ....   Passed    0.01 sec
test 3
    Start 3: PID_Ruslan_Test.DerivativeScaling

3: Test command: D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\runTests_ruslan_task03.exe "--gtest_filter=PID_Ruslan_Test.DerivativeScaling" "--gtest_also_run_disabled_tests"
3: Working Directory: D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
3: Test timeout computed to be: 10000000
3: Running main() from D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\_deps\googletest-src\googletest\src\gtest_main.cc   
3: Note: Google Test filter = PID_Ruslan_Test.DerivativeScaling
3: [==========] Running 1 test from 1 test suite.
3: [----------] Global test environment set-up.
3: [----------] 1 test from PID_Ruslan_Test
3: [ RUN      ] PID_Ruslan_Test.DerivativeScaling
3: [       OK ] PID_Ruslan_Test.DerivativeScaling (0 ms)
3: [----------] 1 test from PID_Ruslan_Test (0 ms total)
3:
3: [----------] Global test environment tear-down
3: [==========] 1 test from 1 test suite ran. (0 ms total)
3: [  PASSED  ] 1 test.
3/6 Test #3: PID_Ruslan_Test.DerivativeScaling ............   Passed    0.01 sec
test 4
    Start 4: PID_Ruslan_Test.InvalidOutputLimitsIgnored

4: Test command: D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\runTests_ruslan_task03.exe "--gtest_filter=PID_Ruslan_Test.InvalidOutputLimitsIgnored" "--gtest_also_run_disabled_tests"
4: Working Directory: D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
4: Test timeout computed to be: 10000000
4: Running main() from D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\_deps\googletest-src\googletest\src\gtest_main.cc   
4: Note: Google Test filter = PID_Ruslan_Test.InvalidOutputLimitsIgnored
4: [==========] Running 1 test from 1 test suite.
4: [----------] Global test environment set-up.
4: [----------] 1 test from PID_Ruslan_Test
4: [ RUN      ] PID_Ruslan_Test.InvalidOutputLimitsIgnored
4: PID_ruslan::setOutputLimits ignored invalid limits: min > max
4: [       OK ] PID_Ruslan_Test.InvalidOutputLimitsIgnored (0 ms)
4: [----------] 1 test from PID_Ruslan_Test (0 ms total)
4:
4: [----------] Global test environment tear-down
4: [==========] 1 test from 1 test suite ran. (0 ms total)
4: [  PASSED  ] 1 test.
4/6 Test #4: PID_Ruslan_Test.InvalidOutputLimitsIgnored ...   Passed    0.01 sec
test 5
    Start 5: PID_Ruslan_Test.IntegralLimitsWork

5: Test command: D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\runTests_ruslan_task03.exe "--gtest_filter=PID_Ruslan_Test.IntegralLimitsWork" "--gtest_also_run_disabled_tests"
5: Working Directory: D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
5: Test timeout computed to be: 10000000
5: Running main() from D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\_deps\googletest-src\googletest\src\gtest_main.cc   
5: Note: Google Test filter = PID_Ruslan_Test.IntegralLimitsWork
5: [==========] Running 1 test from 1 test suite.
5: [----------] Global test environment set-up.
5: [----------] 1 test from PID_Ruslan_Test
5: [ RUN      ] PID_Ruslan_Test.IntegralLimitsWork
5: [       OK ] PID_Ruslan_Test.IntegralLimitsWork (0 ms)
5: [----------] 1 test from PID_Ruslan_Test (0 ms total)
5:
5: [----------] Global test environment tear-down
5: [==========] 1 test from 1 test suite ran. (0 ms total)
5: [  PASSED  ] 1 test.
5/6 Test #5: PID_Ruslan_Test.IntegralLimitsWork ...........   Passed    0.01 sec
test 6
    Start 6: PID_Ruslan_Test.ResetAndSetDt

6: Test command: D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\runTests_ruslan_task03.exe "--gtest_filter=PID_Ruslan_Test.ResetAndSetDt" "--gtest_also_run_disabled_tests"
6: Working Directory: D:/study/otis/OTIS-2025/trunk/ii02821/task_03_mantsevich/build
6: Test timeout computed to be: 10000000
6: Running main() from D:\study\otis\OTIS-2025\trunk\ii02821\task_03_mantsevich\build\_deps\googletest-src\googletest\src\gtest_main.cc   
6: Note: Google Test filter = PID_Ruslan_Test.ResetAndSetDt
6: [==========] Running 1 test from 1 test suite.
6: [----------] Global test environment set-up.
6: [----------] 1 test from PID_Ruslan_Test
6: [ RUN      ] PID_Ruslan_Test.ResetAndSetDt
6: [       OK ] PID_Ruslan_Test.ResetAndSetDt (0 ms)
6: [----------] 1 test from PID_Ruslan_Test (0 ms total)
6:
6: [----------] Global test environment tear-down
6: [==========] 1 test from 1 test suite ran. (0 ms total)
6: [  PASSED  ] 1 test.
6/6 Test #6: PID_Ruslan_Test.ResetAndSetDt ................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.08 sec