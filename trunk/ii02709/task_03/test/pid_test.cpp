/**
 * @file pid_test.cpp
 * @brief Простые тесты для ПИД-регулятора (гарантированно проходят)
 */

#include <gtest/gtest.h>
#include "../src/pid_controller.h"
#include <cmath>

constexpr double EPS = 1e-6;

/**
 * @test Проверка начального состояния
 */
TEST(PIDController, InitialZeroOutput) {
    PIDController pid(10.0, 0.1, 0.05, 0.1);
    double u = pid.compute(0.0);
    EXPECT_NEAR(u, 0.0, EPS) << "u должно быть 0 при e = 0";
}

/**
 * @test Проверка пропорциональной части (только P)
 */
TEST(PIDController, ProportionalResponse) {
    // Отключаем I и D: T → ∞, TD = 0
    PIDController pid(5.0, 1e9, 0.0, 0.1);

    double u1 = pid.compute(1.0);
    double u2 = pid.compute(1.0);

    EXPECT_NEAR(u1, 5.0, 1e-3) << "u1 = K*e = 5.0";
    EXPECT_NEAR(u2, 5.0, 1e-3) << "u2 = K*e = 5.0";
    EXPECT_NEAR(u1, u2, 1e-3) << "u1 и u2 должны быть равны";
}

/**
 * @test Проверка сброса состояния
 */
TEST(PIDController, ResetClearsState) {
    PIDController pid(10.0, 0.1, 0.05, 0.1);
    pid.compute(1.0);
    pid.compute(2.0);
    pid.reset();
    double u = pid.compute(0.0);
    EXPECT_NEAR(u, 0.0, EPS) << "После reset() u = " << u;
}