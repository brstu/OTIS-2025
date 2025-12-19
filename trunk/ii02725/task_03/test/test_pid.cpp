#include <gtest/gtest.h>
#include <cmath>
#include <array>
#include "pid.h"
#include "plant.h"

// Тест 1: Конструктор по непрерывным параметрам
TEST(PID, ConstructorContinuous) {
    PID pid(10.0, 0.1, 0.01, 0.1);

    auto q = pid.q();
    EXPECT_NEAR(q[0], 16.0, 1e-6);
    EXPECT_NEAR(q[1], -7.0, 1e-6);
    EXPECT_NEAR(q[2], 1.0, 1e-6);
}

// Тест 2: Конструктор по дискретным коэффициентам
TEST(PID, ConstructorDiscrete) {
    PID pid(DiscreteTag{}, 1.0, -0.9, 0.1, 42.0);
    EXPECT_DOUBLE_EQ(pid.last_u(), 42.0);
    auto q = pid.q();
    EXPECT_DOUBLE_EQ(q[0], 1.0);
    EXPECT_DOUBLE_EQ(q[1], -0.9);
    EXPECT_DOUBLE_EQ(q[2], 0.1);
}

// Тест 3: Основной функционал update и reset
TEST(PID, UpdateAndReset) {
    PID pid(DiscreteTag{}, 1.0, -1.5, 0.5);

    double u1 = pid.update(2.0);
    EXPECT_DOUBLE_EQ(u1, 2.0);

    double u2 = pid.update(3.0);
    EXPECT_DOUBLE_EQ(u2, 2.0);

    pid.reset(100.0);
    EXPECT_DOUBLE_EQ(pid.last_u(), 100.0);
    
    double u3 = pid.update(1.0);
    EXPECT_DOUBLE_EQ(u3, 101.0);
}

// Тест 4: Проверка сходимости с линейным объектом
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