<p style="text-align: center;">Министерство образования Республики Беларусь</p>
<p style="text-align: center;">Учреждение образования</p>
<p style="text-align: center;">“Брестский Государственный технический университет”</p>
<p style="text-align: center;">Кафедра ИИТ</p>
<div style="margin-bottom: 10em;"></div>
<p style="text-align: center;">Лабораторная работа №3</p>
<p style="text-align: center;">По дисциплине “Общая теория интеллектуальных систем”</p>
<p style="text-align: center;">Тема: “ПИД‑регуляторы”</p>
<div style="margin-bottom: 10em;"></div>
<p style="text-align: right;">Выполнил:</p>
<p style="text-align: right;">Студент 2 курса</p>
<p style="text-align: right;">Группы ИИ-27</p>
<p style="text-align: right;">Юшкевич А.Ю.</p>
<p style="text-align: right;">Проверил:</p>
<p style="text-align: right;">Иванюк Д. С.</p>
<div style="margin-bottom: 10em;"></div>
<p style="text-align: center;">Брест 2025</p>

---

1. Написать отчет по выполненной лабораторной работе №3 в .md формате (*readme.md*) и разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4. Документировать исходный код программы с помощью комментариев в стиле **Doxygen**. Полученную документацию разместить в каталоге: **trunk\ii0xxyy\task_03\doc\html**. Настроить `GitHub Pages` для автоматической публикации документации из этого каталога.
5. Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием **Google Test**. Тесты разместить в каталоге: **trunk\ii0xxyy\task_03\test**.

---

# Выполнение задания #

Код программы:

cmake_minimum_required(VERSION 3.16)
project(task_03_pid LANGUAGES CXX)

option(ENABLE_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(pid_lib
    pid.cpp
    plant.cpp
    sim.cpp
)
target_include_directories(pid_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(pid_sim main.cpp)
target_link_libraries(pid_sim PRIVATE pid_lib)

if(ENABLE_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(pid_tests
        ../test/pid_test.cpp
        ../test/plant_test.cpp
    )
    target_include_directories(pid_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../test)
    target_link_libraries(pid_tests PRIVATE pid_lib GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(pid_tests)
endif()

add_custom_command(TARGET pid_sim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/../doc/data
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/../doc/img
)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/../doc/html)

    add_custom_target(doc_doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../doc
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "pid.h"
#include "plant.h"
#include "sim.h"

/**
 * @brief Пример запуска симуляции: ступенчатое задание и линейная/нелинейная модели.
 */
int main(int argc, char** argv) {
    int steps = 1000;
    double T0 = 0.1;

    PIDConfig cfg;
    cfg.K = 2.0;
    cfg.T = 10.0;
    cfg.TD = 1.0;
    cfg.T0 = T0;
    cfg.u_max = 100.0;
    cfg.anti_windup = true;

    auto w_func = [](int k) -> double {
        if (k < 20) return 0.0;
        return 80.0;
    };

    double a = 0.95;
    double b = 0.05;

    auto plant_step_linear = [a, b](int k, double u_k, double y_k1, double /*y_k2*/) -> double {
        return a * y_k1 + b * u_k;
    };

    abcd nl{1.0, 0.0005, 0.05, 0.01};
    auto plant_step_nonlinear = [nl](int k, double u_k, double y_k1, double y_k2) -> double {
        return nl.a * y_k1 - nl.b * y_k2 * y_k2 + nl.c * u_k + nl.d * std::sin(u_k);
    };

    auto res_lin = run_simulation(steps, T0, cfg, plant_step_linear, w_func, 0.0, 0.0);
    auto res_nl  = run_simulation(steps, T0, cfg, plant_step_nonlinear, w_func, 0.0, 0.0);

    save_csv("doc/data/run_linear.csv", res_lin);
    save_csv("doc/data/run_nonlinear.csv", res_nl);

    std::cout << "Simulation finished. CSV saved to doc/data/.\n";
    return 0;
}

#include "pid.h"
#include <algorithm>
#include <cmath>

/**
 * @brief Внутреннее вычисление коэффициентов q0, q1, q2 по cfg_.
 */
void PID::compute_q() {
    const double K  = cfg_.K;
    const double T  = cfg_.T;
    const double TD = cfg_.TD;
    const double T0 = cfg_.T0;

    const bool integral_off = !std::isfinite(T) || (T <= 0.0);
    const double T_term = integral_off ? 0.0 : (T0 / T);

    q0_ = K * (1.0 + TD / T0);
    q1_ = -K * (1.0 + 2.0 * TD / T0 - T_term);
    q2_ = K * (TD / T0);
}

PID::PID(const PIDConfig& cfg) : cfg_(cfg) {
    compute_q();
    reset();
}

void PID::reset(double u0, double e_1, double e_2) {
    u_k_  = u0;
    e_k_  = e_1;
    e_k1_ = e_1;
    e_k2_ = e_2;
}

double PID::saturate(double v) const {
    if (cfg_.u_max > 0.0) {
        v = std::clamp(v, -cfg_.u_max, cfg_.u_max);
    }
    return v;
}

double PID::step(double e_k) {
    e_k2_ = e_k1_;
    e_k1_ = e_k_;
    e_k_  = e_k;

    double delta_u = q0_ * e_k_ + q1_ * e_k1_ + q2_ * e_k2_;
    double u_next  = u_k_ + delta_u;

    if (cfg_.anti_windup && cfg_.u_max > 0.0) {
        u_next = saturate(u_next);
    }

    u_k_ = u_next;
    return u_k_;
}

void PID::get_q(double& q0, double& q1, double& q2) const {
    q0 = q0_;
    q1 = q1_;
    q2 = q2_;
}

#ifndef PID_H
#define PID_H

#include <cstddef>

/**
 * @brief Конфигурация ПИД‑регулятора.
 *
 * @note Используется дискретная инкрементная форма:
 *       u(k) - u(k-1) = q0*e(k) + q1*e(k-1) + q2*e(k-2)
 */
struct PIDConfig {
    /**
     * @brief Коэффициент передачи K.
     */
    double K = 1.0;

    /**
     * @brief Постоянная интегрирования T (сек).
     * @note При T -> +inf интегральная часть выключена.
     */
    double T = 1.0;

    /**
     * @brief Постоянная дифференцирования TD (сек).
     * @note При TD = 0 дифференциальная часть выключена.
     */
    double TD = 0.0;

    /**
     * @brief Шаг дискретизации T0 (сек).
     */
    double T0 = 0.1;

    /**
     * @brief Ограничение на выход u (сатурация), |u| <= u_max. 0 — нет.
     */
    double u_max = 0.0;

    /**
     * @brief Включить анти‑windup для интегральной части при насыщении.
     */
    bool anti_windup = true;
};

/**
 * @brief ПИД‑регулятор в инкрементной форме.
 *
 * Реализует
 * u(k) = u(k-1) + Δu,
 * Δu = q0*e(k) + q1*e(k-1) + q2*e(k-2),
 * где:
 * q0 = K*(1 + TD/T0),
 * q1 = -K*(1 + 2*TD/T0 - T0/T),
 * q2 = K*(TD/T0).
 */
class PID {
public:
    /**
     * @brief Создать ПИД по конфигурации.
     */
    explicit PID(const PIDConfig& cfg);

    /**
     * @brief Сбросить внутреннее состояние.
     * @param u0 Начальное значение u(-1).
     * @param e_1 Начальное значение e(-1).
     * @param e_2 Начальное значение e(-2).
     */
    void reset(double u0 = 0.0, double e_1 = 0.0, double e_2 = 0.0);

    /**
     * @brief Выполнить шаг регулятора.
     * @param e_k Текущее значение ошибки e(k).
     * @return Текущее значение управляющего воздействия u(k).
     */
    double step(double e_k);

    /**
     * @brief Получить текущее значение u(k).
     */
    double u() const { return u_k_; }

    /**
     * @brief Получить коэффициенты q0, q1, q2.
     */
    void get_q(double& q0, double& q1, double& q2) const;

private:
    PIDConfig cfg_;
    double q0_{0.0};
    double q1_{0.0};
    double q2_{0.0};
    double u_k_{0.0};
    double e_k_{0.0};
    double e_k1_{0.0};
    double e_k2_{0.0};

    void compute_q();
    double saturate(double v) const;
};

#endif

#include "plant.h"

std::vector<double> linear_func(int steps, double a, double b,
                                const std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(steps, 0.0);
    if (steps > 0) y[0] = y0;
    if (steps > 1) y[1] = y1;

    for (int i = 2; i < steps; ++i) {
        y[i] = a * y[i - 1] + b * u[i - 1];
    }
    return y;
}

std::vector<double> nonlinear_func(int steps, const abcd& str_fun,
                                   const std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(steps, 0.0);
    if (steps > 0) y[0] = y0;
    if (steps > 1) y[1] = y1;

    for (int i = 2; i < steps; ++i) {
        y[i] = str_fun.a * y[i - 1]
             - str_fun.b * y[i - 2] * y[i - 2]
             + str_fun.c * u[i - 1]
             + str_fun.d * std::sin(u[i - 2]);
    }
    return y;
}

#ifndef PLANT_H
#define PLANT_H

#include <vector>
#include <cmath>

/**
 * @brief Коэффициенты нелинейной модели.
 *
 * y[i] = a*y[i-1] - b*y[i-2]^2 + c*u[i-1] + d*sin(u[i-2])
 */
struct abcd {
    double a{1.0};
    double b{0.0};
    double c{1.0};
    double d{0.0};
};

/**
 * @brief Линейная дискретная модель объекта:
 * y[i] = a*y[i-1] + b*u[i-1]
 *
 * @param steps Количество шагов.
 * @param a Коэффициент обратной связи.
 * @param b Коэффициент передачи управляющего сигнала.
 * @param u Управляющее воздействие (вектор длины >= steps).
 * @param y0 Начальное значение y(0).
 * @param y1 Значение y(1).
 * @return Вектор выходной переменной y.
 */
std::vector<double> linear_func(int steps, double a, double b,
                                const std::vector<double>& u, double y0, double y1);

/**
 * @brief Нелинейная дискретная модель объекта:
 * y[i] = a*y[i-1] - b*y[i-2]^2 + c*u[i-1] + d*sin(u[i-2])
 *
 * @param steps Количество шагов.
 * @param str_fun Структура коэффициентов (a,b,c,d).
 * @param u Управляющее воздействие (вектор длины >= steps).
 * @param y0 Начальное значение y(0).
 * @param y1 Значение y(1).
 * @return Вектор выходной переменной y.
 */
std::vector<double> nonlinear_func(int steps, const abcd& str_fun,
                                   const std::vector<double>& u, double y0, double y1);

#endif

#include "sim.h"
#include <fstream>
#include <iomanip>

SimResult run_simulation(int steps, double T0, const PIDConfig& pid_cfg,
                         const std::function<double(int, double, double, double)>& plant_step,
                         const SetpointFunc& w_func,
                         double y0, double y1) {
    SimResult res;
    res.T0 = T0;
    res.t.resize(steps);
    res.w.resize(steps);
    res.y.resize(steps);
    res.u.resize(steps);
    res.e.resize(steps);

    PID pid(pid_cfg);
    pid.reset(0.0, 0.0, 0.0);

    // Инициализация
    if (steps > 0) {
        res.t[0] = 0.0;
        res.w[0] = w_func(0);
        res.y[0] = y0;
        res.e[0] = res.w[0] - res.y[0];
        res.u[0] = pid.step(res.e[0]);
    }
    if (steps > 1) {
        res.t[1] = T0;
        res.w[1] = w_func(1);
        res.y[1] = y1;
        res.e[1] = res.w[1] - res.y[1];
        res.u[1] = pid.step(res.e[1]);
    }

    for (int k = 2; k < steps; ++k) {
        res.t[k] = k * T0;
        res.w[k] = w_func(k);
        res.e[k] = res.w[k] - res.y[k - 1];
        res.u[k] = pid.step(res.e[k]);
        res.y[k] = plant_step(k, res.u[k], res.y[k - 1], res.y[k - 2]);
    }

    return res;
}

void save_csv(const std::string& path, const SimResult& r) {
    std::ofstream f(path);
    f << std::fixed << std::setprecision(6);
    f << "t,w,y,u,e\n";
    for (size_t i = 0; i < r.t.size(); ++i) {
        f << r.t[i] << "," << r.w[i] << "," << r.y[i] << "," << r.u[i] << "," << r.e[i] << "\n";
    }
}

#ifndef SIM_H
#define SIM_H

#include <vector>
#include <functional>
#include <string>
#include "pid.h"

/**
 * @brief Профиль задания w(k) (кусочно‑постоянный или иной).
 */
using SetpointFunc = std::function<double(int)>;

/**
 * @brief Результаты одного прогона симуляции.
 */
struct SimResult {
    double T0{0.1};
    std::vector<double> t; 
    std::vector<double> w;  
    std::vector<double> y;
    std::vector<double> u;
    std::vector<double> e;
};

/**
 * @brief Запуск симуляции ПИД+объект по шагам.
 *
 * @param steps Количество шагов.
 * @param T0 Шаг дискретизации.
 * @param pid Конфигурация ПИД‑регулятора.
 * @param plant_step Функция шага объекта: (k, u[k], y[k-1], y[k-2]) -> y[k].
 * @param w_func Профиль задания w(k).
 * @param y0,y1 Начальные значения выхода.
 * @return Результат симуляции (векторы t,w,y,u,e).
 */
SimResult run_simulation(int steps, double T0, const PIDConfig& pid,
                         const std::function<double(int, double, double, double)>& plant_step,
                         const SetpointFunc& w_func,
                         double y0 = 0.0, double y1 = 0.0);

/**
 * @brief Сохранить результаты в CSV.
 *
 * @param path Путь к файлу.
 * @param r Результаты симуляции.
 */
void save_csv(const std::string& path, const SimResult& r);

#endif

#include <gtest/gtest.h>
#include "pid.h"

TEST(PIDCoeffsTest, ComputeQ) {
    PIDConfig cfg;
    cfg.K  = 2.0;
    cfg.T  = 10.0;
    cfg.TD = 1.0;
    cfg.T0 = 0.1;

    PID pid(cfg);
    double q0;
    double q1;
    double q2;
    pid.get_q(q0, q1, q2);

    EXPECT_NEAR(q0, 2.0 * (1.0 + 1.0 / 0.1), 1e-9);
    EXPECT_NEAR(q2, 2.0 * (1.0 / 0.1), 1e-9);
    EXPECT_NEAR(q1, -2.0 * (1.0 + 2.0 * (1.0 / 0.1) - (0.1 / 10.0)), 1e-9);
}

TEST(PIDStepTest, SaturationAntiWindup) {
    PIDConfig cfg;
    cfg.K = 100.0;
    cfg.T = 10.0;
    cfg.TD = 0.0;
    cfg.T0 = 0.1;
    cfg.u_max = 1.0;
    cfg.anti_windup = true;

    PID pid(cfg);
    pid.reset(0.0, 0.0, 0.0);

    double u = 0.0;
    for (int k = 0; k < 100; ++k) {
        u = pid.step(1.0);
        EXPECT_LE(std::abs(u), cfg.u_max + 1e-12);
    }
}

#include <gtest/gtest.h>
#include "plant.h"
#include <vector>
#include <cmath>

TEST(PlantLinearTest, ConstantInput) {
    int steps = 10;
    std::vector<double> u(steps, 1.0);
    auto y = linear_func(steps, 0.5, 0.5, u, 0.0, 0.0);

    ASSERT_EQ(y.size(), static_cast<size_t>(steps));
    EXPECT_NEAR(y[2], 0.5 * y[1] + 0.5 * u[1], 1e-9);
}

TEST(PlantNonlinearTest, BasicCheck) {
    int steps = 10;
    std::vector<double> u(steps, 1.0);
    abcd coeff{1.0, 0.1, 0.5, 0.2};
    auto y = nonlinear_func(steps, coeff, u, 0.0, 0.0);

    ASSERT_EQ(y.size(), static_cast<size_t>(steps));
    EXPECT_NEAR(y[2], coeff.a * y[1] - coeff.b * y[0] * y[0] + coeff.c * u[1] + coeff.d * std::sin(u[0]), 1e-9);
}

---

Результат действия программы:

https://cyber-baka-cmyk.github.io/

---



