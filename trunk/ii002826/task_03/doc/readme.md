<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Шумский И.Н.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1.Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc.
2.Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.
3.Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4.Документировать исходный код программы с помощью комментариев в стиле Doxygen. Полученную документацию разместить в каталоге: trunk\ii0xxyy\task_03\doc\html. Настроить GitHub Pages для автоматической публикации документации из этого каталога.
5.Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием Google Test. Тесты разместить в каталоге: trunk\ii0xxyy\task_03\test.

## Код юнит-тестов [ test/test_pid.cpp ]
```
#include <gtest/gtest.h>
#include "../src/pid.h"
#include <cmath>

TEST(PIDTest, BasicFinite) {
    PIDParams params{10.0, 0.1, 0.01, 0.1};
    PID pid(params);
    double u = pid.update(1.0);
    EXPECT_TRUE(std::isfinite(u));
}

TEST(PIDTest, ZeroInput) {
    PIDParams params{5.0, 0.1, 0.01, 0.1};
    PID pid(params);
    pid.reset();
    double u = pid.update(0.0);
    EXPECT_DOUBLE_EQ(u, 0.0);
}
```

## Исходный код: [ main.cpp ]
```
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "pid.h"
#include "model.h"

/**
 * @brief Моделирование PID-регулятора вместе с объектом управления.
 *
 * Результат сохраняется в result.csv (k,w,y,u).
 */

int main() {
    // Настройки модели (можно сменить на нелинейную)
    ModelParams mp{};
    mp.a = 0.8;
    mp.b = 0.05;
    mp.c = 0.0;
    mp.d = 0.0;

    // Настройки ПИД
    PIDParams pidp{};
    pidp.K = 10.0;
    pidp.T = 0.1;
    pidp.Td = 0.01;
    pidp.T0 = 0.1;

    PID pid(pidp);

    const int steps = 400;
    const double target = 10.0;

    std::vector<double> w, y, u;
    y.reserve(steps);
    u.reserve(steps);
    w.reserve(steps);

    double yk = 0.0;
    double yk_1 = 0.0;

    for (int k = 0; k < steps; ++k) {
        double e = target - yk;
        double uk = pid.update(e);
        double y_next = plant_linear(yk, uk, mp);

        w.push_back(target);
        u.push_back(uk);
        y.push_back(y_next);

        yk_1 = yk;
        yk = y_next;
    }

    std::ofstream out("result.csv");
    out << "k,w,y,u\n";
    for (size_t i = 0; i < w.size(); ++i) {
        out << i << "," << w[i] << "," << y[i] << "," << u[i] << "\n";
    }
    out.close();

    std::cout << "Simulation finished. result.csv created.\n";
    return 0;
}
```

## Исходный код: [ model.cpp ]
```
#include "model.h"
#include <cmath>

double plant_linear(double y_prev, double u, const ModelParams& p) {
    return p.a * y_prev + p.b * u;
}

double plant_nonlinear(double y_prev, double y_prev2, double u, const ModelParams& p) {
    return p.a * y_prev - p.b * (y_prev2 * y_prev2) + p.c * u + p.d * std::sin(u);
}
```

## Исходный код: [ model.h ]
```
/**
 * @file model.h
 * @brief Простейшая модель объекта (линейная и нелинейная)
 */

#pragma once

struct ModelParams {
    double a;
    double b;
    double c; // используется для нелинейной модели
    double d; // используется для нелинейной модели
};

/**
 * @brief Линейная модель: y_next = a*y_prev + b*u
 */
double plant_linear(double y_prev, double u, const ModelParams& p);

/**
 * @brief Нелинейная модель: y_next = a*y_prev - b*y_prev2^2 + c*u + d*sin(u)
 */
double plant_nonlinear(double y_prev, double y_prev2, double u, const ModelParams& p);
```

## Исходный код: [ pid.cpp ]
```
#include "pid.h"
#include <cmath>

PID::PID(const PIDParams& p) : p_(p) {
    // Защита от деления на ноль для T и T0
    double T = (p_.T == 0.0) ? 1e-12 : p_.T;
    double T0 = (p_.T0 == 0.0) ? 1e-12 : p_.T0;

    q0_ = p_.K * (1.0 + T0 / T + p_.Td / T0);
    q1_ = -p_.K * (1.0 + 2.0 * p_.Td / T0);
    q2_ = p_.K * (p_.Td / T0);
}

double PID::update(double e) {
    double du = q0_ * e + q1_ * e_prev_ + q2_ * e_prev2_;
    double u = u_prev_ + du;

    // shift memory
    e_prev2_ = e_prev_;
    e_prev_  = e;
    u_prev_  = u;

    return u;
}

void PID::reset() {
    u_prev_ = e_prev_ = e_prev2_ = 0.0;
}
```

## Исходный код: [ pid.h ]
```
/**
 * @file pid.h
 * @brief Дискретный PID-регулятор (приращённая форма)
 */

#pragma once

/**
 * @struct PIDParams
 * @brief Параметры ПИД-регулятора
 */
struct PIDParams {
    double K;   ///< коэффициент передачи
    double T;   ///< постоянная интегрирования
    double Td;  ///< постоянная дифференцирования
    double T0;  ///< шаг дискретизации
};

/**
 * @class PID
 * @brief Дискретный ПИД-регулятор в приращённой форме:
 *
 * u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
class PID {
public:
    PID(const PIDParams& p);

    /**
     * @brief Вычислить управляющее воздействие
     * @param e текущее отклонение e(k)
     * @return u(k)
     */
    double update(double e);

    /** @brief Сброс внутреннего состояния */
    void reset();

private:
    PIDParams p_;
    double q0_{0.0}, q1_{0.0}, q2_{0.0};
    double u_prev_{0.0};
    double e_prev_{0.0};
    double e_prev2_{0.0};
};
```

## Результаты юнит-тестирования (GoogleTest)

```
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from PIDTest
[ RUN      ] PIDTest.BasicFinite
[       OK ] PIDTest.BasicFinite (0 ms)
[ RUN      ] PIDTest.ZeroInput
[       OK ] PIDTest.ZeroInput (0 ms)
[----------] 2 tests from PIDTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.

Test project C:/projects/task_03/build
    Start 1: PIDTests
1/1 Test #1: PIDTests .....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.02 sec
```

## Результат действия программы:

GitHub Pages: [https://tlbery.github.io/OTIS-2025/](https://tlbery.github.io/OTIS-2025/)
