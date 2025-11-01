#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "../src/factory/factorylinearmodel.hpp"
#include "../src/factory/factorynonlinearmodel.hpp"

#include "../src/regulator/pidregulator.hpp"
#include "../src/adaptivecontroller.hpp"

TEST(TestLinearModel, WhenTimeIsFive)
{   
    const double y = 0; // Initial output value
    const double u = 1; // Input signal value
    const int t = 5;    // Simulation time steps

    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->getDefaultModel();
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
    const int t = 5;    // Simulation time steps

    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->getDefaultModel();
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

TEST(TestAdaptiveControllerLinearModel, WhenInputWarmIsTenAndTimeIsFive)
{
    const double w = 10; // Input warm.
    const int t = 5;     // Simulation time steps.

    auto pidRegulatorForLinearModel = std::make_unique<PIDRegulator>();
    auto linearFactory = std::make_unique<FactoryLinearModel>();
    auto linearModel = linearFactory->getDefaultModel();

    auto linearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForLinearModel), std::move(linearModel)); 
    std::vector<double> linear_result = linearController->run(w, t);

    std::vector<double> accepted_results
    { 0.55, 1.32775, 2.10299, 2.80855, 3.05697, 3.106 };

    EXPECT_EQ(linear_result.size(), accepted_results.size());
    
    for (size_t i = 0; i < linear_result.size(); i++) 
    {
        EXPECT_NEAR(linear_result[i], accepted_results[i], 1e-4)
           << "Mismatch at index " << i;
    }
}
TEST(TestAdaptiveControllerNonLinearModel, WhenInputWarmIsTenAndTimeIsFive)
{
    const double w = 10; // Input warm.
    const int t = 5;     // Simulation time steps.

    auto pidRegulatorForNonLinearModel = std::make_unique<PIDRegulator>();
    auto nonlinearFactory = std::make_unique<FactoryNonLinearModel>();
    auto nonlinearModel = nonlinearFactory->getDefaultModel();

    auto nonlinearController = std::make_unique<AdaptiveController>(std::move(pidRegulatorForNonLinearModel), std::move(nonlinearModel)); 
    std::vector<double> nonlinear_result = nonlinearController->run(w, t);

    std::vector<double> accepted_results
    { 0.55, 1.77335, 2.58247, 1.55651, -1.1215, -0.0515545 };

    EXPECT_EQ(nonlinear_result.size(), accepted_results.size());
    
    for (size_t i = 0; i < nonlinear_result.size(); i++) 
    {
        EXPECT_NEAR(nonlinear_result[i], accepted_results[i], 1e-4)
            << "Mismatch at index " << i;
    }
}