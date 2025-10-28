#include <gtest/gtest.h>
#include "C:\Users\sabak\Desktop\Папки\OTIS-2025\trunk\ii02818\task_02\src\lab2otis.h"

TEST(TemperatureModelTest, ConstructorInitialization) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    
    EXPECT_DOUBLE_EQ(model.getA(), 0.1);
    EXPECT_DOUBLE_EQ(model.getB(), 0.2);
    EXPECT_DOUBLE_EQ(model.getC(), 0.3);
    EXPECT_DOUBLE_EQ(model.getD(), 0.4);
}

TEST(TemperatureModelTest, SetInitialState) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    model.setInitialState(10.0, 15.0, 1.0, 2.0);
    
    EXPECT_DOUBLE_EQ(model.getPrevY(), 10.0);
    EXPECT_DOUBLE_EQ(model.getCurrentY(), 15.0);
    EXPECT_DOUBLE_EQ(model.getPrevU(), 1.0);
    EXPECT_DOUBLE_EQ(model.getCurrentU(), 2.0);
}

TEST(TemperatureModelTest, UpdateControl) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    model.setInitialState(10.0, 15.0, 1.0, 2.0);
    model.updateControl(3.0);
    
    EXPECT_DOUBLE_EQ(model.getPrevU(), 2.0);
    EXPECT_DOUBLE_EQ(model.getCurrentU(), 3.0);
}

TEST(TemperatureModelTest, LinearModelCalculation) {
    TemperatureModel model(0.5, 1.0, 0.0, 0.0);
    model.setInitialState(0.0, 10.0, 2.0, 0.0);
    
    auto result = model.simulateLinear(3);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 10.0);
    EXPECT_DOUBLE_EQ(result[2], 0.5*10.0 + 1.0*2.0);
}

TEST(TemperatureModelTest, NonlinearModelCalculation) {
    TemperatureModel model(0.5, 0.1, 1.0, 0.2);
    model.setInitialState(2.0, 3.0, 1.0, 0.5);
    
    auto result = model.simulateNonlinear(4);
    
    ASSERT_GE(result.size(), 4);
    double expected = 0.5*3.0 - 0.1*2.0*2.0 + 1.0*1.0 + 0.2*sin(0.5);
    EXPECT_NEAR(result[2], expected, 1e-10);
}

TEST(TemperatureModelTest, BoundaryConditions) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    
    auto result_zero = model.simulateLinear(0);
    EXPECT_TRUE(result_zero.empty());
    
    auto result_single = model.simulateLinear(1);
    EXPECT_EQ(result_single.size(), 1);
    
    auto result_double = model.simulateLinear(2);
    EXPECT_EQ(result_double.size(), 2);
}

TEST(TemperatureModelTest, NegativeValues) {
    TemperatureModel model(-0.1, -0.2, -0.3, -0.4);
    model.setInitialState(-10.0, -15.0, -1.0, -2.0);
    
    auto result = model.simulateLinear(3);
    
    EXPECT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], -10.0);
    EXPECT_DOUBLE_EQ(result[1], -15.0);
}

TEST(TemperatureModelTest, LargeTimeSteps) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    model.setInitialState(1.0, 2.0, 1.0, 1.0);
    
    auto result = model.simulateLinear(1000);
    
    EXPECT_EQ(result.size(), 1000);
    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
}