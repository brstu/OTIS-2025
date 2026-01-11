#include "gtest/gtest.h"
#include "../src/PID.h"

TEST(PIDTest, checkQs) {
    PID p;
    p.calcQs();
    double r0, r1, r2;
    p.getQs(r0, r1, r2);
    EXPECT_NEAR(r0, 3, 0.1);
    EXPECT_NEAR(r1, -3.2, 0.1);
    EXPECT_NEAR(r2, 1.5, 0.1);
}