#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "../src/factory/factorylinearmodel.h"
#include "../src/factory/factorynonlinearmodel.h"

TEST(TestLinearModel, WhenTimeIsFive)
{   
    const double y = 20.0; // Initial output value (temperature)
    const double u = 2.0;  // Input signal value (heat)
    const int t = 5;       // Simulation time steps

    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->getModel();
    std::vector<double> calculated_results = model->simulate(y, u, t);
    // y(n+1) = 0.8 * y(n) + 0.3 * u
    // y0 = 20
    // y1 = 0.8 * 20 + 0.3 * 2 = 16 + 0.6 = 16.6
    // y2 = 0.8 * 16.6 + 0.6 = 13.28 + 0.6 = 13.88
    // y3 = 0.8 * 13.88 + 0.6 = 11.104 + 0.6 = 11.704
    // y4 = 0.8 * 11.704 + 0.6 = 9.3632 + 0.6 = 9.9632
    // y5 = 0.8 * 9.9632 + 0.6 = 7.97056 + 0.6 = 8.57056
    std::vector<double> accepted_results
    { 20.0, 16.6, 13.88, 11.704, 9.9632, 8.57056 };

    EXPECT_EQ(calculated_results.size(), accepted_results.size());
    
    for (size_t i = 0; i < calculated_results.size(); i++)
    {
        EXPECT_NEAR(calculated_results[i], accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
    }
}

TEST(TestNonLinearModel, WhenTimeIsFive)
{   
    const double y = 20.0; // Initial output value (temperature)
    const double u = 2.0;  // Input signal value (heat)
    const int t = 5;       // Simulation time steps

    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->getModel();
    std::vector<double> calculated_results = model->simulate(y, u, t);
    // y(n+1) = 0.8 * y(n) - 0.01 * y(n-1)^2 + 0.4 * u + 0.1 * sin(u_prev)
    // y0 = 20, prevY = 20, prevU = 0
    // y1 = 0.8*20 - 0.01*20*20 + 0.4*2 + 0.1*sin(0) = 16 - 4 + 0.8 + 0 = 12.8
    // y2 = 0.8*12.8 - 0.01*20*20 + 0.4*2 + 0.1*sin(2) = 10.24 - 4 + 0.8 + 0.0909 = 7.1309
    // y3 = 0.8*7.1309 - 0.01*12.8*12.8 + 0.4*2 + 0.1*sin(2) = 5.7047 - 1.6384 + 0.8 + 0.0909 = 4.9572
    // y4 = 0.8*4.9572 - 0.01*7.1309*7.1309 + 0.4*2 + 0.1*sin(2) = 3.9658 - 0.5085 + 0.8 + 0.0909 = 4.3482
    // y5 = 0.8*4.3482 - 0.01*4.9572*4.9572 + 0.4*2 + 0.1*sin(2) = 3.4786 - 0.2457 + 0.8 + 0.0909 = 4.1238
    std::vector<double> accepted_results
    { 20.0, 12.8, 7.13097, 4.95722, 4.34818, 4.12378 };

    EXPECT_EQ(calculated_results.size(), accepted_results.size());
    
    for (size_t i = 0; i < calculated_results.size(); i++) 
    {
        EXPECT_NEAR(calculated_results[i], accepted_results[i], 1e-4)
            << "Mismatch at index " << i;
    }
}



