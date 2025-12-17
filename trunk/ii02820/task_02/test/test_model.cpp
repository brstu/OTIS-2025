#include <gtest/gtest.h>
#include <cmath>
#include "model.h"


class LinearModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = new LinearModel(0.95, 0.002, 10.0);
    }
    
    void TearDown() override {
        delete model;
    }
    
    LinearModel* model;
};

TEST_F(LinearModelTest, Initialization) {
    EXPECT_DOUBLE_EQ(model->getPreviousY(), 10.0);
}

TEST_F(LinearModelTest, CalculateFirstStep) {
    double result = model->calculate(5.0);
    double expected = 0.95 * 10.0 + 0.002 * 5.0;
    EXPECT_NEAR(result, expected, 1e-10);
}

TEST_F(LinearModelTest, CalculateMultipleSteps) {
    double result1 = model->calculate(5.0);
    double result2 = model->calculate(10.0);
    
    double expected1 = 0.95 * 10.0 + 0.002 * 5.0;
    double expected2 = 0.95 * expected1 + 0.002 * 10.0;
    
    EXPECT_NEAR(result1, expected1, 1e-10);
    EXPECT_NEAR(result2, expected2, 1e-10);
}

TEST_F(LinearModelTest, ResetFunction) {
    model->calculate(5.0);
    model->reset(15.0);
    EXPECT_DOUBLE_EQ(model->getPreviousY(), 15.0);
}


class NonlinearModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = new NonlinearModel(0.95, 0.002, 0.05, 0.1, 10.0);
    }
    
    void TearDown() override {
        delete model;
    }
    
    NonlinearModel* model;
};

TEST_F(NonlinearModelTest, Initialization) {
    EXPECT_DOUBLE_EQ(model->getPreviousY(), 10.0);
}

TEST_F(NonlinearModelTest, CalculateFirstStep) {
    double u = 5.0;
    double result = model->calculate(u);
    double expected = 0.95 * 10.0 - 0.002 * 10.0 * 10.0 + 0.05 * u + 0.1 * sin(u);
    EXPECT_NEAR(result, expected, 1e-10);
}

TEST_F(NonlinearModelTest, CalculateMultipleSteps) {
    double u1 = 5.0;
    double result1 = model->calculate(u1);
    
    double u2 = 10.0;
    double result2 = model->calculate(u2);
    
    double expected1 = 0.95 * 10.0 - 0.002 * 10.0 * 10.0 + 0.05 * u1 + 0.1 * sin(u1);
    double expected2 = 0.95 * result1 - 0.002 * 10.0 * 10.0 + 0.05 * u2 + 0.1 * sin(u2);
    
    EXPECT_NEAR(result1, expected1, 1e-10);
    EXPECT_NEAR(result2, expected2, 1e-10);
}

TEST_F(NonlinearModelTest, ResetFunction) {
    model->calculate(5.0);
    model->reset(20.0);
    EXPECT_DOUBLE_EQ(model->getPreviousY(), 20.0);
}


TEST(ModelsComparisonTest, SameParametersComparison) {
    LinearModel linear(0.95, 0.002, 15.0);
    NonlinearModel nonlinear(0.95, 0.002, 0.0, 0.0, 15.0);
    
    double u = 10.0;
    double y_linear = linear.calculate(u);
    double y_nonlinear = nonlinear.calculate(u);
    
 
    EXPECT_NEAR(y_linear, y_nonlinear, 1e-10);
}


class LinearModelParamTest : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(LinearModelParamTest, VariousParameters) {
    auto [a, b, initial_y] = GetParam();
    LinearModel model(a, b, initial_y);
    
    double u = 5.0;
    double result = model.calculate(u);
    double expected = a * initial_y + b * u;
    
    EXPECT_NEAR(result, expected, 1e-10);
}

INSTANTIATE_TEST_SUITE_P(
    LinearModelParameters,
    LinearModelParamTest,
    ::testing::Values(
        std::make_tuple(0.5, 0.1, 10.0),
        std::make_tuple(0.9, 0.01, 5.0),
        std::make_tuple(1.0, 0.0, 15.0),
        std::make_tuple(0.0, 1.0, 20.0)
    )
);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}