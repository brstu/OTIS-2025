#include <gtest/gtest.h>
#include "../src/model/linearmodel.h"
#include "../src/model/nonlinearmodel.h"

TEST(LinearModelTest, SimpleSimulation) {
    LinearModel model(0.9, 0.1);
    auto res = model.simulate(3, 1, 2);
    std::vector<double> expected = {2, 1.9, 1.81};
    ASSERT_EQ(res.size(), expected.size());
    for (size_t i = 0; i < res.size(); ++i)
        EXPECT_NEAR(res[i], expected[i], 1e-5);
}

TEST(NonlinearModelTest, CustomInputs) {
    NonlinearModel model(0.9, 0.1, 0.05, 0.02);
    std::vector<double> inputs = {1, 2, 3};
    auto res = model.simulate(3, 1, 2, inputs);
    ASSERT_EQ(res.size(), 3);
    EXPECT_NE(res[0], res[1]);
}
