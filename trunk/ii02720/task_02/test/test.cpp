#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cmath>

#include "../src/factory/factorylinearmodel.h"
#include "../src/factory/factorynonlinearmodel.h"

TEST(LinearModelTest, TemperatureDecay)
{   
    constexpr double initialTemp = 20.0;
    constexpr double heatInput = 2.0;
    constexpr int steps = 5;

    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->createModel();
    
    std::vector<double> results = model->simulate(initialTemp, heatInput, steps);
    std::vector<double> expected = {20.0, 16.6, 13.88, 11.704, 9.9632, 8.57056};

    ASSERT_EQ(results.size(), expected.size());
    
    for (size_t i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], expected[i], 1e-5)
            << "Mismatch at step " << i;
    }
}

TEST(NonLinearModelTest, ComplexDynamics)
{   
    constexpr double initialTemp = 20.0;
    constexpr double heatInput = 2.0;
    constexpr int steps = 5;

    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->createModel();
    
    std::vector<double> results = model->simulate(initialTemp, heatInput, steps);
    std::vector<double> expected = {20.0, 12.8, 7.13097, 4.95722, 4.34818, 4.12378};

    ASSERT_EQ(results.size(), expected.size());
    
    for (size_t i = 0; i < results.size(); i++) 
    {
        EXPECT_NEAR(results[i], expected[i], 1e-4)
            << "Mismatch at step " << i;
    }
}
