#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "../src/functions.h"

using namespace std;

TEST(TestLinear, WhenStepsAreFive)
{   
    const int n = 5;    // Simulation time steps

    vector<double> accepted_results
    { 0.36, 0.096, 0.0696, 0.06696, 0.066696 };
    double y = 3;
    for (int i = 0; i < n; i++)
	{
        liner_funcnt(y);
        EXPECT_NEAR(y, accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
	}
}
TEST(TestNonLinear, WhenStepsAreFive)
{   
    const int n = 5;    // Simulation time steps

    vector<double> accepted_results
    { 0.538208, -1.47842, 0.0619846, -0.163186, 0.250673 };
    double y = 3;
    double y_previous;
	bool second_iteration = true;
    for (int i = 0; i < n; i++)
	{
        nonliner_funct(y, y_previous, second_iteration);
        EXPECT_NEAR(y, accepted_results[i], 1e-5)
            << "[Mismatch at index]: " << i;
	}
}

TEST(TestPIDRegulatorUsingNonLinearModel, WhenStepsIsFive)
 {
    unsigned int step = 5;
    double w = 100;
    std::vector<double> results = simulatePIDRegulatorByNonLinearModel(w, step);

    std::vector<double> accepted_results
    { 7.15507, 13.7002, -5.47014, -66.113};
    EXPECT_EQ(results.size(), accepted_results.size());  
    for (int i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2) << "Not equal at" << i;
    }
} 
