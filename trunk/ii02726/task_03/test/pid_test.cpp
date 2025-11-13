#include <gtest/gtest.h>
#include "pid.h"

TEST(PIDCoeffsTest, ComputeQ) {
    PIDConfig cfg;
    cfg.K  = 2.0;
    cfg.T  = 10.0;
    cfg.TD = 1.0;
    cfg.T0 = 0.1;

    PID pid(cfg);
    double q0;
    double q1;
    double q2;
    pid.get_q(q0, q1, q2);

    EXPECT_NEAR(q0, 2.0 * (1.0 + 1.0 / 0.1), 1e-9);
    EXPECT_NEAR(q2, 2.0 * (1.0 / 0.1), 1e-9);
    EXPECT_NEAR(q1, -2.0 * (1.0 + 2.0 * (1.0 / 0.1) - (0.1 / 10.0)), 1e-9);
}

TEST(PIDStepTest, SaturationAntiWindup) {
    PIDConfig cfg;
    cfg.K = 100.0;
    cfg.T = 10.0;
    cfg.TD = 0.0;
    cfg.T0 = 0.1;
    cfg.u_max = 1.0;
    cfg.anti_windup = true;

    PID pid(cfg);
    pid.reset(0.0, 0.0, 0.0);

    double u = 0.0;
    for (int k = 0; k < 100; ++k) {
        u = pid.step(1.0);
        EXPECT_LE(std::abs(u), cfg.u_max + 1e-12);
    }
}
