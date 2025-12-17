#include <cmath>
#include <gtest/gtest.h>
#include "pid_controller.h"

TEST(PIDControllerTest, ConstructorAndParameters) {
    PIDController pid(2.0, 0.5, 0.1, 0.01);
    double K;
    double Ti;
    double Td;
    double T;
    pid.getParameters(K, Ti, Td, T);
    EXPECT_DOUBLE_EQ(K, 2.0);
    EXPECT_DOUBLE_EQ(Ti, 0.5);
    EXPECT_DOUBLE_EQ(Td, 0.1);
    EXPECT_DOUBLE_EQ(T, 0.01);
}

TEST(PIDControllerTest, CalculateZeroError) {
    PIDController pid(1.0, 0.1, 0.05, 0.01);
    double u = pid.calculate(1.0, 1.0);
    EXPECT_NEAR(u, 0.0, 1e-6);
}

TEST(PIDControllerTest, CalculateConstantError) {
    PIDController pid(2.0, 0.2, 0.0, 0.01);
    double u1 = pid.calculate(1.0, 0.0);
    double u2 = pid.calculate(1.0, 0.0);
    EXPECT_GT(u2, u1);
}

TEST(PIDControllerTest, ResetController) {
    PIDController pid(1.0, 0.1, 0.05, 0.01);
    pid.calculate(1.0, 0.0);
    pid.calculate(1.0, 0.5);
    pid.reset();
    double u = pid.calculate(1.0, 1.0);
    EXPECT_NEAR(u, 0.0, 1e-6);
}

TEST(PIDControllerTest, SetParameters) {
    PIDController pid(1.0, 0.1, 0.05, 0.01);
    pid.setParameters(2.0, 0.2, 0.1, 0.02);
    double K;
    double Ti;
    double Td;
    double T;
    pid.getParameters(K, Ti, Td, T);
    EXPECT_DOUBLE_EQ(K, 2.0);
    EXPECT_DOUBLE_EQ(Ti, 0.2);
    EXPECT_DOUBLE_EQ(Td, 0.1);
    EXPECT_DOUBLE_EQ(T, 0.02);
}

TEST(PIDControllerTest, PControllerBehavior) {
    PIDController p_controller(10.0, 0.0, 0.0, 0.01);
    p_controller.reset();
    double u1 = p_controller.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(u1));

    double u2 = p_controller.calculate(1.0, 0.5);
    EXPECT_TRUE(std::isfinite(u2));
}

TEST(PIDControllerTest, PIDControllerStepResponse) {
    PIDController pid(10.0, 0.1, 0.05, 0.01);
    pid.reset();

    std::vector<double> errors = { 1.0, 0.8, 0.6, 0.4, 0.2 };
    std::vector<double> controls;

    for (double error : errors) {
        double control = pid.calculate(error, 0.0);
        controls.push_back(control);
    }

    EXPECT_EQ(controls.size(), errors.size());
    for (const auto& control : controls) {
        EXPECT_TRUE(std::isfinite(control));
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}