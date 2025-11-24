#include <gtest/gtest.h>
#include <cmath>
#include <array>
#include "../src/pid_contr.h"

TEST(PIDValueTest, DirectCoefficients) {
    PID pid(1.0, -0.5, 0.2);

    pid.reset();

    double u1 = pid.compute(2.0);
    EXPECT_NEAR(u1, 2.0, 1e-10);

    double u2 = pid.compute(1.0);
    EXPECT_NEAR(u2, 2.0, 1e-10);

    double u3 = pid.compute(0.5);
    EXPECT_NEAR(u3, 2.4, 1e-10);
}

TEST(PIDValueTest, FromKTdT0) {
    double K = 0.5;
    double Ti = 4.0;
    double Td = 0.3;
    double T0 = 1.4;

    PID pid(K, Ti, Td, T0);
    pid.reset();

    double u1 = pid.compute(1.0);
    EXPECT_TRUE(std::isfinite(u1));

    double u2 = pid.compute(1.0);
    EXPECT_TRUE(std::isfinite(u2));
}

TEST(PIDTest, ResetFunctionality) {
    PID pid(1.0, 1.0, 0.1, 0.1);

    pid.compute(1.0);
    pid.compute(1.0);

    pid.reset();

    PID pid_new(1.0, 1.0, 0.1, 0.1);

    double u_reset = pid.compute(1.0);
    double u_new = pid_new.compute(1.0);

    EXPECT_DOUBLE_EQ(u_reset, u_new);
}

TEST(PIDTest, ZeroError) {
    PID pid(1.0, 1.0, 0.0, 0.1);
    pid.reset();

    double u = pid.compute(0.0);

    EXPECT_DOUBLE_EQ(u, 0.0);
}

TEST(PIDTest, ConstantError) {
    PID pid(2.0, 0.5, 0.1, 0.1);

    double u1 = pid.compute(1.0);
    double u2 = pid.compute(1.0);
    double u3 = pid.compute(1.0);

    EXPECT_NE(u1, u2);
    EXPECT_NE(u2, u3);
}

TEST(PIDBasicTest, SequenceOfComputations) {
    PID pid(1.0, 0.1, 0.01, 0.1);

    std::array<double, 3> results;
    for (auto& result : results) {
        result = pid.compute(1.0);
    }

    EXPECT_NE(results[0], results[1]);
    EXPECT_NE(results[1], results[2]);
    EXPECT_NE(results[0], results[2]);
}

TEST(PIDValueTest, BoundaryCases) {
    PID pid_large(1000.0, 1000.0, 1000.0, 0.01);
    pid_large.reset();
    double u_large = pid_large.compute(0.1);
    EXPECT_TRUE(std::isfinite(u_large));

    PID pid_small_dt(1.0, 1.0, 1.0, 1e-10);
    pid_small_dt.reset();
    double u_small = pid_small_dt.compute(1.0);
    EXPECT_TRUE(std::isfinite(u_small));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}