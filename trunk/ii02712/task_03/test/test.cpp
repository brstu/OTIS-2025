#include <gtest/gtest.h>
#include "../src/functions.h"

TEST(TestLinearModel, WhenStepsIsFour)
{   
    const int steps = 4;
    double y_next = 0;
    double u = 1;
    std::vector<double> results;
    for (int i = 0; i < steps; i++) {
        y_next = linearModel(y_next, u);
        results.push_back(y_next);
    }

    std::vector<double> accepted_results
    { 0.5, 0.45, 0.455, 0.4545 };
    EXPECT_EQ(results.size(), accepted_results.size());
    for (int i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2) << "Not equal at" << i;
    }
}

TEST(TestNonLinearModel, WhenStepsIsFour)
{   
    const int steps = 4;
    double y_next = 0;
    double u = 1;
    std::vector<double> results;
    for (int i = 0; i < steps; i++) {
        double y_pred = y_next;
        double u_pred = u;
        y_next = nonlinearModel(y_next, u, y_pred, u_pred);
        results.push_back(y_next);
    }

    std::vector<double> accepted_results
    {  0.53658, 0.33896, 0.44524, 0.3929 };
    EXPECT_EQ(results.size(), accepted_results.size());  
    for (int i = 0; i < results.size(); i++) 
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2) << "Not equal at" << i;
    }
}

TEST(TestPIDRegulatorUsingNonLinearModel, WhenStepsIsFour)
{   
    const int steps = 5;
    const double w = 100;
    std::vector<double> results = simulatePIDRegulatorUsingNonLinearModel(w, steps);

    std::vector<double> accepted_results
    { 2, 3.76, 3.29119, 0.746527, 3.94837};
    EXPECT_EQ(results.size(), accepted_results.size());  
    for (int i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-1) << "Not equal at" << i;
    }
}
