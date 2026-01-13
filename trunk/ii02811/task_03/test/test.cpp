#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"
#include <cmath>

TEST(PIDTest, ConstructorParameters) {
    PID pid(1.0, 2.0, 0.5, 1.0);
    double K;
    double Ti;
    double Td;
    pid.getParameters(K, Ti, Td);
    EXPECT_DOUBLE_EQ(K, 1.0);
    EXPECT_DOUBLE_EQ(Ti, 2.0);
    EXPECT_DOUBLE_EQ(Td, 0.5);
}

TEST(PIDTest, OutputSaturation) {
    PID pid(100.0, 0.1, 10.0, 1.0);
    double u = pid.calculate(1000.0, 0.0);
    EXPECT_GE(u, 0.0);
    EXPECT_LE(u, 100.0);
}

TEST(PIDTest, ZeroErrorTest) {
    PID pid(1.0, 1.0, 0.1, 1.0);
    pid.reset();
    double control1 = pid.calculate(10.0, 10.0);
    EXPECT_DOUBLE_EQ(control1, 0.0);
    double control2 = pid.calculate(10.0, 10.0);
    EXPECT_DOUBLE_EQ(control2, 0.0);
}

TEST(PIDTest, BasicCalculation) {
    PID pid(0.5, 1.0, 0.1, 0.1);
    pid.reset();
    double control = pid.calculate(10.0, 5.0);
    EXPECT_GT(control, 0.0);
    EXPECT_LE(control, 100.0);
}

TEST(ModelTest, LinearModelCorrect) {
    Model model(0.2, 0.3, 0.0, 0.0);
    model.init(10.0, 10.0, 0.0, 0.0);
    double y = model.linearModel(10.0);
    double expected = 0.2 * 10.0 + 0.3 * 10.0;
    EXPECT_NEAR(y, expected, 1e-6);
}

TEST(ModelTest, NonlinearModelBounds) {
    Model model(10.0, 10.0, 10.0, 10.0);
    model.init(0.0, 0.0, 0.0, 0.0);
    double y = model.nonlinearModel(1000.0);
    EXPECT_LE(y, 1000.0);
    EXPECT_GE(y, -1000.0);
}

TEST(ModelTest, GetSetCurrentValue) {
    Model model(0.2, 0.3, 0.4, 0.5);
    model.init(10.0, 20.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(model.getCurrentValue(), 20.0);
    model.setCurrentValue(30.0);
    EXPECT_DOUBLE_EQ(model.getCurrentValue(), 30.0);
}

TEST(ModelTest, LinearModelSequence) {
    Model model(0.8, 0.2, 0.0, 0.0);
    model.init(0.0, 0.0, 0.0, 0.0);
    
    std::vector<double> outputs;
    for (int i = 0; i < 5; i++) {
        outputs.push_back(model.linearModel(1.0));
    }
    
    for (size_t i = 1; i < outputs.size(); i++) {
        EXPECT_GT(outputs[i], outputs[i-1]);
    }
}

TEST(IntegrationTest, PIDWithLinearModel) {
    Model model(0.7, 0.3, 0.0, 0.0);
    model.init(20.0, 20.0, 0.0, 0.0);
    
    PID pid(0.5, 2.0, 0.1, 1.0);
    
    const double setpoint = 30.0;
    double final_temp = 0.0;
    
    for (int i = 0; i < 50; i++) {
        double temp = model.getCurrentValue();
        double control = pid.calculate(setpoint, temp);
        if (control > 100.0) control = 100.0;
        if (control < 0.0) control = 0.0;
        model.linearModel(control);
        final_temp = temp;
    }
    
    EXPECT_GT(final_temp, 20.0);
    EXPECT_LT(std::abs(final_temp - setpoint), 10.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}