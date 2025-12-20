#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <cmath>

#include "../src/factory/factorylinearmodel.h"
#include "../src/factory/factorynonlinearmodel.h"

namespace {

constexpr double TOLERANCE = 1e-5;

class ModelTestFixture : public ::testing::Test {
protected:
    const double initialCondition = 0.0;
    const double controlInput = 1.0;
    const int simulationSteps = 5;
};

TEST_F(ModelTestFixture, LinearModelSimulationWithFiveSteps) {
    auto modelFactory = std::make_unique<FactoryLinearModel>();
    auto dynamicModel = modelFactory->getModel();
    
    const std::vector<double> simulationOutput = 
        dynamicModel->simulate(initialCondition, controlInput, simulationSteps);
    
    const std::vector<double> referenceValues = {
        0.0, 0.5, 0.75, 0.875, 0.9375, 0.96875
    };

    ASSERT_EQ(simulationOutput.size(), referenceValues.size())
        << "Размеры векторов результатов не совпадают";

    for (size_t stepIndex = 0; stepIndex < simulationOutput.size(); ++stepIndex) {
        EXPECT_NEAR(simulationOutput[stepIndex], referenceValues[stepIndex], TOLERANCE)
            << "Расхождение на временном шаге " << stepIndex 
            << ": получено " << simulationOutput[stepIndex] 
            << ", ожидалось " << referenceValues[stepIndex];
    }
}

TEST_F(ModelTestFixture, NonlinearModelSimulationWithFiveSteps) {
    auto modelFactory = std::make_unique<FactoryNonLinearModel>();
    auto dynamicModel = modelFactory->getModel();
    
    const std::vector<double> simulationOutput = 
        dynamicModel->simulate(initialCondition, controlInput, simulationSteps);
    
    const std::vector<double> referenceValues = {
        0.0, 0.499999, 0.989713, 1.29059, 1.15428, 0.698974
    };

    ASSERT_EQ(simulationOutput.size(), referenceValues.size())
        << "Размеры векторов результатов не совпадают";

    for (size_t stepIndex = 0; stepIndex < simulationOutput.size(); ++stepIndex) {
        EXPECT_NEAR(simulationOutput[stepIndex], referenceValues[stepIndex], TOLERANCE)
            << "Расхождение на временном шаге " << stepIndex 
            << ": получено " << simulationOutput[stepIndex] 
            << ", ожидалось " << referenceValues[stepIndex];
    }
}

} // namespace