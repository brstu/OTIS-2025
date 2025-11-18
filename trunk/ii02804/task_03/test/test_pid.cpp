#include <gtest/gtest.h>
#include "pid.h"
#include "models.h"

TEST(PID, ZeroErrorProducesZeroOutput) {
    PID pid(10, 0.1, 50, 0.01);

    double u = pid.update(0.0);
    EXPECT_NEAR(u, 0.0, 1e-9);
}

TEST(PID, StepErrorGivesPositiveOutput) {
    PID pid(10, 0.1, 50, 0.01);

    double u = pid.update(1.0);
    EXPECT_GT(u, 0.0);
}

TEST(Model, NonLinearChangesWithInput) {
    double y = 0, y_prev = 0, u_prev = 0;

    double y1 = non_linear_model(y, y_prev, 1.0, u_prev,
                                 1.0, 0.2, 0.5, 0.1);
    double y2 = non_linear_model(y1, y_prev, 2.0, u_prev,
                                 1.0, 0.2, 0.5, 0.1);

    EXPECT_NE(y1, y2);
}
