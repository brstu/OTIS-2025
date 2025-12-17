#include <gtest/gtest.h>
#include "../src/pid.h"
#include <cmath>

TEST(PIDTest, BasicFinite) {
    PIDParams params{10.0, 0.1, 0.01, 0.1};
    PID pid(params);
    double u = pid.update(1.0);
    EXPECT_TRUE(std::isfinite(u));
}

TEST(PIDTest, ZeroInput) {
    PIDParams params{5.0, 0.1, 0.01, 0.1};
    PID pid(params);
    pid.reset();
    double u = pid.update(0.0);
    EXPECT_DOUBLE_EQ(u, 0.0);
}
