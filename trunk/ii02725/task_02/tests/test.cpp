#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/module.h"

TEST(LinearModelTest, BasicCalculation)
{
    int steps = 3;
    double coeff_a = 0.5;
    double coeff_b = 1.0;
    std::vector<double> inputs = {1.0, 2.0, 3.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 1.0;

    calculate_linear_model(steps, coeff_a, coeff_b, inputs, results);

    EXPECT_NEAR(results[1], 1.5, 1e-10);
    EXPECT_NEAR(results[2], 2.75, 1e-10);
    EXPECT_NEAR(results[3], 4.375, 1e-10);
}

TEST(LinearModelTest, OneStep)
{
    int steps = 1;
    double coeff_a = 1.0;
    double coeff_b = 2.0;
    std::vector<double> inputs = {5.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 10.0;

    calculate_linear_model(steps, coeff_a, coeff_b, inputs, results);

    EXPECT_NEAR(results[1], 20.0, 1e-10);
}

TEST(LinearModelTest, NoSteps)
{
    int steps = 0;
    double coeff_a = 1.0;
    double coeff_b = 1.0;
    std::vector<double> inputs = {};
    std::vector<double> results(1, 10.0);

    calculate_linear_model(steps, coeff_a, coeff_b, inputs, results);

    EXPECT_NEAR(results[0], 10.0, 1e-10);
    EXPECT_EQ(results.size(), 1);
}

TEST(NonlinearModelTest, TwoStepsCase)
{
    int steps = 2;
    double alpha = 1.0;
    double beta = 1.0;
    double gamma = 1.0;
    double delta = 1.0;
    std::vector<double> inputs = {1.0, 2.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 5.0;
    results[1] = 10.0;

    calculate_nonlinear_model(steps, alpha, beta, gamma, delta, inputs, results);

    EXPECT_NEAR(results[2], -12.15852902, 1e-8);
}

TEST(NonlinearModelTest, SingleStepNoComputation)
{
    int steps = 1;
    double alpha = 1.0;
    double beta = 1.0;
    double gamma = 1.0;
    double delta = 1.0;
    std::vector<double> inputs = {1.0};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 5.0;
    results[1] = 10.0;

    double initial_value = results[0];
    double second_value = results[1];
    
    calculate_nonlinear_model(steps, alpha, beta, gamma, delta, inputs, results);

    EXPECT_NEAR(results[0], initial_value, 1e-10);
    EXPECT_NEAR(results[1], second_value, 1e-10);
}

TEST(NonlinearModelTest, ThreeStepsCase)
{
    int steps = 3;
    double alpha = 0.5;
    double beta = 0.2;
    double gamma = 1.5;
    double delta = 0.8;
    std::vector<double> inputs = {0.5, 1.0, 1.5};
    std::vector<double> results(steps + 1, 0.0);
    results[0] = 2.0;
    results[1] = 3.0;
    
    calculate_nonlinear_model(steps, alpha, beta, gamma, delta, inputs, results);
    
    EXPECT_NEAR(results[2], 2.5835404309, 1e-9);
}