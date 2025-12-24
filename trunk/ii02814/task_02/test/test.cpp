#include <gtest/gtest.h>

#include "../src/modelsimulation.h"

TEST(TestLinearModel, WhenTimeIsFive)
{   
    SimulationParams simParams = getDefaultSimulationParams();
    std::vector<double> results = simulateLinearModel(simParams);

    std::vector<double> accepted_results
    { 0.6, 48.06, 52.806, 53.2806, 53.3281, 53.3328 };
    EXPECT_EQ(results.size(), accepted_results.size());
    for (size_t i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2)
            << "Mismatch at index " << i;
    }
}

TEST(TestNonLinearModel, WhenTimeIsFive)
{   
    SimulationParams simParams = getDefaultSimulationParams();
    std::vector<double> results = simulateNonLinearModel(simParams);

    std::vector<double> accepted_results
    { 0.6, 56.0124, 109.079, -1406.39, -7302.33, -996209 };

    EXPECT_EQ(results.size(), accepted_results.size());
    
    for (size_t i = 0; i < results.size(); i++) 
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2)
            << "Mismatch at index " << i;
    }
}