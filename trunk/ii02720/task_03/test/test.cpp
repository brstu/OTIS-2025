#include <gtest/gtest.h>
#include <memory>

#include "../src/factory/factorylinearmodel.hpp"
#include "../src/factory/factorynonlinearmodel.hpp"
#include "../src/regulator/pidregulator.hpp"
#include "../src/adaptivecontroller.hpp"

TEST(LinearModelTests, SimulationOutput)
{   
    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->createModel();
    auto results = model->runSimulation(0, 1, 5);
    
    std::vector<double> expected = {0, 0.5, 0.75, 0.875, 0.9375, 0.96875};

    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i)
        EXPECT_NEAR(results[i], expected[i], 1e-5);
}

TEST(NonLinearModelTests, SimulationOutput)
{   
    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->createModel();
    auto results = model->runSimulation(0, 1, 5);
    
    std::vector<double> expected = {0, 0.499999, 0.989713, 1.29059, 1.15428, 0.698974};

    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i)
        EXPECT_NEAR(results[i], expected[i], 1e-5);
}

TEST(ControllerTests, LinearModelControl)
{
    auto reg = std::make_unique<PIDRegulator>();
    auto factory = std::make_unique<FactoryLinearModel>();
    auto model = factory->createModel();
    auto controller = std::make_unique<AdaptiveController>(std::move(reg), std::move(model)); 
    
    auto results = controller->execute(10, 5);
    std::vector<double> expected = {0.55, 1.32775, 2.10299, 2.80855, 3.05697, 3.106};

    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i)
        EXPECT_NEAR(results[i], expected[i], 1e-4);
}

TEST(ControllerTests, NonLinearModelControl)
{
    auto reg = std::make_unique<PIDRegulator>();
    auto factory = std::make_unique<FactoryNonLinearModel>();
    auto model = factory->createModel();
    auto controller = std::make_unique<AdaptiveController>(std::move(reg), std::move(model)); 
    
    auto results = controller->execute(10, 5);
    std::vector<double> expected = {0.55, 1.77335, 2.58247, 1.55651, -1.1215, -0.0515545};

    ASSERT_EQ(results.size(), expected.size());
    for (size_t i = 0; i < results.size(); ++i)
        EXPECT_NEAR(results[i], expected[i], 1e-4);
}
