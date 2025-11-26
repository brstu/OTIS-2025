#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include "../src/lab2otis.h"  


TEST(TemperatureModelTest, ConstructorAndGetters) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);

    EXPECT_DOUBLE_EQ(model.getA(), 0.1);
    EXPECT_DOUBLE_EQ(model.getB(), 0.2);
    EXPECT_DOUBLE_EQ(model.getC(), 0.3);
    EXPECT_DOUBLE_EQ(model.getD(), 0.4);
}

TEST(TemperatureModelTest, SetInitialState) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    model.setInitialState(10.0, 11.0, 5.0, 6.0);

    EXPECT_DOUBLE_EQ(model.getPrevY(), 10.0);
    EXPECT_DOUBLE_EQ(model.getCurrentY(), 11.0);
    EXPECT_DOUBLE_EQ(model.getPrevU(), 5.0);
    EXPECT_DOUBLE_EQ(model.getCurrentU(), 6.0);
}

TEST(TemperatureModelTest, LinearSimulation) {
    TemperatureModel model(0.5, 0.3, 0.0, 0.0);
    model.setInitialState(20.0, 21.0, 1.0, 1.0);

    auto results = model.simulateLinear(5);

    EXPECT_EQ(results.size(), 5);
    EXPECT_DOUBLE_EQ(results[0], 20.0);
    EXPECT_DOUBLE_EQ(results[1], 21.0);
    EXPECT_DOUBLE_EQ(results[2], 0.5 * 21.0 + 0.3 * 1.0);
}

TEST(TemperatureModelTest, NonlinearSimulation) {
    TemperatureModel model(0.5, 0.1, 0.2, 0.3);
    model.setInitialState(2.0, 3.0, 1.0, 1.0);

    auto results = model.simulateNonlinear(5);

    EXPECT_EQ(results.size(), 5);
    EXPECT_DOUBLE_EQ(results[0], 2.0);
    EXPECT_DOUBLE_EQ(results[1], 3.0);

    double expected = 0.5 * 3.0 - 0.1 * 4.0 + 0.2 * 1.0 + 0.3 * std::sin(1.0);
    EXPECT_NEAR(results[2], expected, 1e-10);
}

TEST(TemperatureModelTest, EdgeCases) {
    TemperatureModel model(0.0, 0.0, 0.0, 0.0);
    model.setInitialState(0.0, 0.0, 0.0, 0.0);

    auto results1 = model.simulateLinear(1);
    EXPECT_EQ(results1.size(), 1);
    EXPECT_DOUBLE_EQ(results1[0], 0.0);

    auto results2 = model.simulateLinear(2);
    EXPECT_EQ(results2.size(), 2);
}

TEST(TemperatureModelTest, UpdateControl) {
    TemperatureModel model(0.1, 0.2, 0.3, 0.4);
    model.setInitialState(10.0, 11.0, 5.0, 6.0);

    model.updateControl(7.0);

    EXPECT_DOUBLE_EQ(model.getPrevU(), 6.0);
    EXPECT_DOUBLE_EQ(model.getCurrentU(), 7.0);
}