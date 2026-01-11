#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "../src/modelsAndPID.hpp"

TEST(PIDControllerTest, SystemStabilization) {
    PIDController pid({2.0, 0.5, 0.1, -10.0, 10.0});
    
    double y = 0.0;
    const double setpoint = 2.0;
    const double a = 0.8;
    const double b = 0.5;
    
    std::vector<double> outputs;
    for (int i = 0; i < 20; i++) {
        double u = pid.calculate(setpoint, y);
        y = a * y + b * u;
        outputs.push_back(y);
    }
       
    EXPECT_NEAR(outputs.back(), setpoint, 0.1);
}

TEST(PIDControllerTest, DisturbanceRejection) {
    PIDController pid({2.0, 0.3, 0.2, -10.0, 10.0});
    
    double y = 2.0;
    const double setpoint = 2.0;
    const double a = 0.9;
    const double b = 0.4;
    
    for (int i = 0; i < 5; i++) {
        double u = pid.calculate(setpoint, y);
        y = a * y + b * u;
    }
    
    double steady_state = y;

    y += 1.0;

    for (int i = 0; i < 10; i++) {
        double u = pid.calculate(setpoint, y);
        y = a * y + b * u;
    }
        
    EXPECT_NEAR(y, steady_state, 0.2);
}