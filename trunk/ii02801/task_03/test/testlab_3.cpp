#include <gtest/gtest.h>
#include "../src/model.h"
#include "../src/pid.h"

TEST(ModelTest, LinearIncreasingInput) {
    std::vector<double> u = {1,1,1,1};
    auto y = simulateLinear(5, 0, 1.0, 1.0, u);
    EXPECT_EQ(y.size(), 5);
    EXPECT_EQ(y[1], 1);
    EXPECT_EQ(y[2], 2);
}

TEST(ModelTest, NonlinearBasic) {
    std::vector<double> u = {1,1,1,1};
    auto y = simulateNonlinear(5, 1, 1.0, 0.1, 0.5, 0.0, u);
    EXPECT_EQ(y.size(), 5);
    EXPECT_GT(y[3], 0);
}

TEST(PIDTest, Stabilizes) {
    PID pid(1.0, 3.0, 0.1, 1.0);

    double y = 0;
    double w = 10;

    for(int i=0; i<100; i++) {
        double e = w - y;
        y += 0.1 * pid.compute(e);
    }

    EXPECT_NEAR(y, 10, 3);
}
