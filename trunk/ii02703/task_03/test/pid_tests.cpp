#include <gtest/gtest.h>
#include "functions.h"

/**
 * @brief Проверка линейной модели объекта
 */
TEST(PlantTest, LinearModelWorks)
{
    double y = 1.0;
    double u = 2.0;

    double y_next = linearPlant(y, u);

    double expected = A * y + B * u;
    EXPECT_NEAR(y_next, expected, 1e-9);
}

/**
 * @brief Проверка нелинейной модели объекта
 */
TEST(PlantTest, NonlinearModelWorks)
{
    double y = 1.0;
    double u = 0.5;
    double y_prev = 0.9;
    double u_prev = 0.4;

    double y_next = nonlinearPlant(y, u, y_prev, u_prev);

    double expected =
        A * y
        - B * y_prev * y_prev
        + C * u
        + D * std::sin(u_prev);

    EXPECT_NEAR(y_next, expected, 1e-9);
}

/**
 * @brief Проверка, что ПИД-регулятор сходится к заданию
 */
TEST(PIDTest, ConvergesToSetpoint)
{
    const double setpoint = 4.0;
    const int steps = 200;

    std::vector<double> result = runSimulation(setpoint, steps);

    double final_value = result.back();

    EXPECT_NEAR(final_value, setpoint, 1e-2);
}
