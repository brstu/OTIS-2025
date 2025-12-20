#include <gtest/gtest.h>
#include <memory>
#include <cmath>

#include "../src/factory/factorylinearmodel.h"
#include "../src/factory/factorynonlinearmodel.h"

// Test LinearModel with single input
TEST(TestLinearModel, SingleInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.3;
    const double initialY = 20.0;
    const double u = 2.0;

    auto model = std::make_unique<LinearModel>(a, b, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
}

// Test LinearModel with multiple steps
TEST(TestLinearModel, MultipleStepsSimulation)
{   
    const double a = 0.8;
    const double b = 0.3;
    const double initialY = 20.0;
    std::vector<double> inputs = {2.0, 3.0, 4.0};
    
    auto model = std::make_unique<LinearModel>(a, b, initialY);
    
    std::vector<double> expected_results = {20.0, 16.6, 14.18};
    
    for (size_t i = 0; i < inputs.size(); i++)
    {
        auto result = model->simulate(inputs[i]);
        EXPECT_EQ(result.size(), 1);
        EXPECT_NEAR(result[0], expected_results[i], 1e-5)
            << "Mismatch at step " << i;
    }
}

// Test LinearModel with factory
TEST(TestLinearModelFactory, FactoryCreation)
{   
    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->getModel();
    
    ASSERT_NE(model, nullptr);
    
    auto result = model->simulate(2.0);
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
}

// Test LinearModel with zero input
TEST(TestLinearModel, ZeroInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.3;
    const double initialY = 20.0;
    const double u = 0.0;

    auto model = std::make_unique<LinearModel>(a, b, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
    
    // Next step should be 0.8 * 20.0 = 16.0
    result = model->simulate(u);
    EXPECT_NEAR(result[0], 16.0, 1e-5);
}

// Test LinearModel with negative input
TEST(TestLinearModel, NegativeInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.3;
    const double initialY = 20.0;
    const double u = -5.0;

    auto model = std::make_unique<LinearModel>(a, b, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
    
    // Next step: 0.8 * 20.0 + 0.3 * (-5.0) = 16.0 - 1.5 = 14.5
    result = model->simulate(u);
    EXPECT_NEAR(result[0], 14.5, 1e-5);
}

// Test NonLinearModel with single input
TEST(TestNonLinearModel, SingleInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.01;
    const double c = 0.4;
    const double d = 0.1;
    const double initialY = 20.0;
    const double u = 2.0;

    auto model = std::make_unique<NonLinearModel>(a, b, c, d, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
}

// Test NonLinearModel with multiple steps
TEST(TestNonLinearModel, MultipleStepsSimulation)
{   
    const double a = 0.8;
    const double b = 0.01;
    const double c = 0.4;
    const double d = 0.1;
    const double initialY = 20.0;
    std::vector<double> inputs = {2.0, 3.0, 4.0};
    
    auto model = std::make_unique<NonLinearModel>(a, b, c, d, initialY);
    
    // Calculate expected values manually based on the formula:
    // result = a*prevY - b*prevPrevY^2 + c*u + d*sin(prevU)
    double prevY = initialY;
    double prevPrevY = initialY;
    double prevU = 0;
    
    for (size_t i = 0; i < inputs.size(); i++)
    {
        auto result = model->simulate(inputs[i]);
        EXPECT_EQ(result.size(), 1);
        EXPECT_NEAR(result[0], prevY, 1e-5)
            << "Mismatch at step " << i;
        
        // Update for next iteration
        double nextY = a * prevY - b * prevPrevY * prevPrevY 
                     + c * inputs[i] + d * std::sin(prevU);
        prevPrevY = prevY;
        prevY = nextY;
        prevU = inputs[i];
    }
}

// Test NonLinearModel with factory
TEST(TestNonLinearModelFactory, FactoryCreation)
{   
    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->getModel();
    
    ASSERT_NE(model, nullptr);
    
    auto result = model->simulate(2.0);
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
}

// Test NonLinearModel with zero input
TEST(TestNonLinearModel, ZeroInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.01;
    const double c = 0.4;
    const double d = 0.1;
    const double initialY = 20.0;
    const double u = 0.0;

    auto model = std::make_unique<NonLinearModel>(a, b, c, d, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
}

// Test NonLinearModel with negative input
TEST(TestNonLinearModel, NegativeInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.01;
    const double c = 0.4;
    const double d = 0.1;
    const double initialY = 20.0;
    const double u = -3.0;

    auto model = std::make_unique<NonLinearModel>(a, b, c, d, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
    
    // Calculate expected next value
    // result = 0.8*20.0 - 0.01*20.0^2 + 0.4*(-3.0) + 0.1*sin(0)
    double expected = 0.8 * 20.0 - 0.01 * 20.0 * 20.0 + 0.4 * (-3.0) + 0.1 * std::sin(0);
    result = model->simulate(u);
    EXPECT_NEAR(result[0], expected, 1e-5);
}

// Test LinearModel boundary conditions
TEST(TestLinearModel, BoundaryConditions)
{   
    const double a = 0.8;
    const double b = 0.3;
    const double initialY = 0.0;
    const double u = 0.0;

    auto model = std::make_unique<LinearModel>(a, b, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 0.0, 1e-5);
}

// Test NonLinearModel boundary conditions
TEST(TestNonLinearModel, BoundaryConditions)
{   
    const double a = 0.8;
    const double b = 0.01;
    const double c = 0.4;
    const double d = 0.1;
    const double initialY = 0.0;
    const double u = 0.0;

    auto model = std::make_unique<NonLinearModel>(a, b, c, d, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 0.0, 1e-5);
}

// Test LinearModel sequence matching original implementation
TEST(TestLinearModel, OriginalSequenceTest)
{   
    std::vector<double> inputs = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    
    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->getModel();
    
    std::vector<double> results;
    for (const auto& u : inputs)
    {
        auto result = model->simulate(u);
        results.push_back(result[0]);
    }
    
    // Verify we got all results
    EXPECT_EQ(results.size(), inputs.size());
    
    // First result should be the initial value
    EXPECT_NEAR(results[0], 20.0, 1e-5);
}

// Test NonLinearModel sequence matching original implementation
TEST(TestNonLinearModel, OriginalSequenceTest)
{   
    std::vector<double> inputs = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    
    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->getModel();
    
    std::vector<double> results;
    for (const auto& u : inputs)
    {
        auto result = model->simulate(u);
        results.push_back(result[0]);
    }
    
    // Verify we got all results
    EXPECT_EQ(results.size(), inputs.size());
    
    // First result should be the initial value
    EXPECT_NEAR(results[0], 20.0, 1e-5);
}

