#include <gtest/gtest.h>
#include "../src/pid.h"

TEST(PIDTest, ZeroErrorGivesZeroOutput) {
    PID pid;
    initPID(pid, 0.6, 0.3, 0.1);

    double u = updatePID(pid, 0.0);
    EXPECT_DOUBLE_EQ(u, 0.0);
}

TEST(PIDTest, ConstantErrorIncreasesOutput) {
    PID pid;
    initPID(pid, 1.0, 0.0, 0.0);

    double u1 = updatePID(pid, 1.0);
    double u2 = updatePID(pid, 1.0);

    EXPECT_GT(u2, u1);
}