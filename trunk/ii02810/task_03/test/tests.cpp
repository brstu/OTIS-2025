#include <gtest/gtest.h>
#include "../src/pid.h"
#include "../src/model.h"

TEST(PIDController, ProportionalOnly) {
    PIDController pid(10.0, 1e12, 0.0, 1.0);
    pid.reset();
    double u = pid.calculate(100.0, 90.0);
    EXPECT_NEAR(u, 100.0, 1e-2);
}

TEST(PIDController, IntegralAccumulation) {
    PIDController pid(0.0, 100.0, 0.0, 1.0); // только I
    pid.reset();
    pid.calculate(100.0, 0.0);
    double u2 = pid.calculate(100.0, 0.0);
    EXPECT_GT(u2, 0.5);
}

TEST(HeaterModel, Delay) {
    HeaterModel plant(1.0, 100.0, 5.0, 1.0);
    plant.step(100.0);
    plant.step(100.0);
    plant.step(100.0);
    plant.step(100.0);
    plant.step(100.0);
    double y = plant.step(0.0); // на 6-м шаге должно начать падать
    EXPECT_GT(y, 0.01);
}