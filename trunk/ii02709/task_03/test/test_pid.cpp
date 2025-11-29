/**
 * @file test_pid.cpp
 * @brief Тесты GoogleTest: проверка, что ошибка стремится к нулю.
 */

#include <gtest/gtest.h>
#include <cmath>
#include "pid.h"
#include "plant.h"

TEST(ii02709_PID_Tests, LinearPlantErrorTendsToZero) {
    const double T0 = 0.1;
    const int steps = 1000;
    const double setpoint = 50.0;

    LinearPlant plant(0.98, 0.05, 0.0, 0.0);
    PID pid(10.0, 0.1, 0.01, T0);

    for (int i=0; i<steps; ++i) {
        double e = setpoint - plant.y();
        double u = pid.update(e);
        plant.step(u);
    }

    double final_error = std::fabs(setpoint - plant.y());
    EXPECT_LT(final_error, 0.5);
}

TEST(ii02709_PID_Tests, NonlinearPlantErrorTendsToZero) {
    const double T0 = 0.1;
    const int steps = 2000;
    const double setpoint = 50.0;

    NonlinearPlant plant(0.98, 0.05, 0.0, 0.01, 0.0);
    PID pid(12.0, 0.2, 0.02, T0);

    for (int i=0; i<steps; ++i) {
        double e = setpoint - plant.y();
        double u = pid.update(e);
        plant.step(u);
    }

    double final_error = std::fabs(setpoint - plant.y());
    EXPECT_LT(final_error, 1.0);
}
