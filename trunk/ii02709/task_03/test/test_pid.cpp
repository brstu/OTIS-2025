#include <gtest/gtest.h>
#include <cmath>
#include <array>
#include "pid.h"
#include "plant.h"

// Тест конструктора по непрерывным параметрам
TEST(PID, ConstructorContinuous) {
    PID pid(10.0, 0.1, 0.01, 0.1);

    auto q = pid.q();
    EXPECT_NEAR(q[0], 10.0 * (1.0 + 0.1/(2*0.1) + 0.01/0.1), 1e-6);
    EXPECT_NEAR(q[1], -10.0 * (1.0 - 0.1/(2*0.1) + 2*0.01/0.1), 1e-6);
    EXPECT_NEAR(q[2], 10.0 * (0.01/0.1), 1e-6);
    EXPECT_DOUBLE_EQ(pid.last_u(), 0.0);
}

// Тест конструктора по дискретным коэффициентам
TEST(PID, ConstructorDiscrete) {
    PID pid(DiscreteTag{}, 1.0, -0.9, 0.1, 42.0);
    EXPECT_DOUBLE_EQ(pid.last_u(), 42.0);
    auto q = pid.q();
    EXPECT_DOUBLE_EQ(q[0], 1.0);
    EXPECT_DOUBLE_EQ(q[1], -0.9);
    EXPECT_DOUBLE_EQ(q[2], 0.1);
}

// Тест update и reset
TEST(PID, UpdateAndReset) {
    PID pid(DiscreteTag{}, 1.0, -1.5, 0.5);

    double u1 = pid.update(2.0);
    EXPECT_DOUBLE_EQ(u1, 2.0);  // u = 0 + 1*2 + (-1.5)*0 + 0.5*0

    double u2 = pid.update(3.0);
    EXPECT_DOUBLE_EQ(u2, 2.0 + 1*3 + (-1.5)*2 + 0.5*0);  // = 2 + 3 - 3 = 2

    pid.reset(100.0);
    EXPECT_DOUBLE_EQ(pid.last_u(), 100.0);
    double u3 = pid.update(1.0);
    EXPECT_DOUBLE_EQ(u3, 100.0 + 1.0);  // e_prev1=e_prev2=0 после reset
}

// Тест случая T <= 0 (чистый PD-регулятор)
TEST(PID, ProportionalDerivativeOnly) {
    PID pid(5.0, 0.0, 1.0, 0.1);  // T=0

    auto q = pid.q();
    EXPECT_DOUBLE_EQ(q[0], 5.0 * (1.0 + 1.0/0.1));  // = 5*(1+10) = 55
    EXPECT_DOUBLE_EQ(q[1], -5.0 * (1.0 + 2*1.0/0.1)); // = -5*(1+20) = -105
    EXPECT_DOUBLE_EQ(q[2], 5.0 * (1.0/0.1));       // = 50
}

// Покрытие линейного объекта (уже было)
TEST(PID, LinearPlantConverges) {
    LinearPlant plant(0.98, 0.05, 0.0);
    PID pid(10.0, 0.1, 0.01, 0.1);

    for (int i = 0; i < 1000; ++i) {
        double e = 50.0 - plant.y();
        double u = pid.update(e);
        plant.step(u);
    }
    EXPECT_LT(std::abs(50.0 - plant.y()), 0.5);
}

// Покрытие нелинейного объекта
TEST(PID, NonlinearPlantConverges) {
    NonlinearPlant plant(0.98, 0.05, 0.0, 0.01);
    PID pid(12.0, 0.2, 0.02, 0.1);

    for (int i = 0; i < 2000; ++i) {
        double e = 50.0 - plant.y();
        double u = pid.update(e);
        plant.step(u);
    }
    EXPECT_LT(std::abs(50.0 - plant.y()), 1.0);
}