#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "../src/factory/factorylinearmodel.h"
#include "../src/factory/factorynonlinearmodel.h"

TEST(TestLinearModel, WhenTimeIsFive)
{   
    const double y = 0; // Initial output value
    const double u = 1; // Input signal value
    const int t = 5; // Simulation time steps

    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->getModel();
    std::vector<double> calculated_results = model->simulate(y, u, t);
    std::vector<double> accepted_results
    { 0, 0.5, 0.75, 0.875, 0.9375, 0.96875 };

    EXPECT_EQ(calculated_results.size(), accepted_results.size());
    
    for (size_t i = 0; i < calculated_results.size(); i++)
    {
        EXPECT_NEAR(calculated_results[i], accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
    }
}

TEST(TestNonLinearModel, WhenTimeIsFives)
{   
    const double y = 0; // Initial output value
    const double u = 1; // Input signal value
    const int t = 5; // Simulation time steps

    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->getModel();
    std::vector<double> calculated_results = model->simulate(y, u, t);
    std::vector<double> accepted_results
    { 0, 0.499999, 0.989713, 1.29059, 1.15428, 0.698974 };

    EXPECT_EQ(calculated_results.size(), accepted_results.size());
    
    for (size_t i = 0; i < calculated_results.size(); i++) 
    {
        EXPECT_NEAR(calculated_results[i], accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
    }
}



