#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"
#include <cmath>

TEST(PIDTest, ConstructorParameters) {
    PID pid(1.0, 2.0, 0.5, 1.0);

    double K, Ti, Td;
    pid.getParameters(K, Ti, Td);

    EXPECT_DOUBLE_EQ(K, 1.0);
    EXPECT_DOUBLE_EQ(Ti, 2.0);
    EXPECT_DOUBLE_EQ(Td, 0.5);
}

TEST(PIDTest, OutputSaturation) {
    PID pid(100.0, 0.1, 10.0, 1.0);

    double u = pid.calculate(1000.0, 0.0);

    EXPECT_GE(u, 0.0);
    EXPECT_LE(u, 100.0);
}

TEST(ModelTest, LinearModelCorrect) {
    Model model(0.2, 0.3, 0.0, 0.0);
    model.init(10.0, 10.0, 0.0, 0.0);

    double y = model.linearModel(10.0);
    EXPECT_NEAR(y, 0.2 * 10.0 + 0.3 * 10.0, 1e-6);
}