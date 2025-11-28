#include <gtest/gtest.h>
#include "pid_controller.h"
#include "model.h"
#include <cmath>

static bool is_finite(double x) { return std::isfinite(x); }

TEST(PIDController, ConstructorWorks) {
    PIDController pid(10.0, 1.0, 0.8, 0.1);
    EXPECT_TRUE(is_finite(pid.compute(0.0)));
}

TEST(PIDController, IntegralIncreasesOutput) {
    PIDController pid(10.0, 1.0, 0.0, 0.1);
    double u1 = pid.compute(1.0);
    double u2 = pid.compute(1.0);
    EXPECT_GT(u2, u1);
}

TEST(PIDController, ResetWorks) {
    PIDController pid(5.0, 1.0, 0.0, 0.1);
    pid.compute(1.0);
    pid.reset();
    EXPECT_NEAR(pid.compute(1.0), 5.5, 1e-9);
}



TEST(Model, HeatsUp) {
    Model m;
    m.reset(0.0);
    m.update(10.0);
    EXPECT_GT(m.getTemperature(), 0.0);
}

