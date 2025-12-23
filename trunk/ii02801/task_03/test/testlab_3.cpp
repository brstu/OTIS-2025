/**
 * @file test.cpp
 * @brief Модульные тесты для ПИД-регулятора и модели объекта
 */

#include <gtest/gtest.h>
#include <cmath>
#include "../src/pid.h"
#include "../src/model.h"


TEST(PIDControllerTest, ConstructorAndParameters)
{
    PIDController pid(2.0, 1.0, 0.5, 1.0);
    
    
    double result = pid.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(result));
}


TEST(PIDControllerTest, CalculatePController)
{
    PIDController pid(1.0, 1.0, 0.0, 1.0); 
    pid.reset();

    
    double u1 = pid.calculate(1.0, 0.0); 
    EXPECT_NEAR(u1, 1.0, 1e-6); 

    
    double u2 = pid.calculate(1.0, 0.5); 
    EXPECT_NEAR(u2, 1.5, 1e-6); 

    
    double u3 = pid.calculate(1.0, 1.0); 
    EXPECT_NEAR(u3, 1.5, 1e-6); 
}


TEST(PIDControllerTest, CalculatePIController)
{
    PIDController pid(1.0, 0.5, 0.0, 1.0); 
    pid.reset();

    double u1 = pid.calculate(1.0, 0.0);
    double u2 = pid.calculate(1.0, 0.5);
    
    
    EXPECT_GT(u2, u1);
}


TEST(PIDControllerTest, Reset)
{
    PIDController pid(1.0, 1.0, 0.1, 1.0);
    
    
    pid.calculate(1.0, 0.0);
    pid.calculate(1.0, 0.5);
    
    
    pid.reset();
    
    
    double result = pid.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(result));
}


TEST(ProcessModelTest, LinearModel)
{
    std::vector<double> params = {0.5, 0.5, 0.0, 0.0};
    ProcessModel plant(params, 1.0);

    double y1 = plant.linearModel(1.0);
    EXPECT_NEAR(y1, 0.5 * 1.0 + 0.5 * 1.0, 1e-6);

    double y2 = plant.linearModel(2.0);
    EXPECT_NEAR(y2, 0.5 * y1 + 0.5 * 2.0, 1e-6);
}


TEST(ProcessModelTest, NonlinearModel)
{
    std::vector<double> params = {0.5, 0.1, 0.3, 0.1};
    ProcessModel plant(params, 1.0);

    double y = plant.nonlinearModel(0.5);
    double expected = 0.5 * 1.0 - 0.1 * 1.0 * 1.0 + 0.3 * 0.5 + 0.1 * std::sin(0.5);

    EXPECT_NEAR(y, expected, 1e-6);
}


TEST(ProcessModelTest, SetInitialValue)
{
    std::vector<double> params = {0.8, 0.2, 0.0, 0.0};
    ProcessModel plant(params, 0.0);
    
    plant.setInitialValue(2.0);
    double y = plant.linearModel(1.0);
    
    
    EXPECT_NEAR(y, 0.8 * 2.0 + 0.2 * 1.0, 1e-6);
}


TEST(SystemIntegrationTest, PControllerWithLinearPlant)
{
    std::vector<double> params = {0.8, 0.2, 0.0, 0.0};
    ProcessModel plant(params, 0.0);
    PIDController p_controller(2.0, 1.0, 0.0, 1.0);

    plant.setInitialValue(0.0);
    p_controller.reset();

    std::vector<double> outputs;
    double setpoint = 1.0;
    
    for (int i = 0; i < 10; i++)
    {
        double current_output = (outputs.empty()) ? 0.0 : outputs.back();
        double control_signal = p_controller.calculate(setpoint, current_output);
        double new_output = plant.linearModel(control_signal);
        outputs.push_back(new_output);
    }

    
    EXPECT_GT(outputs.back(), 0.0);
    EXPECT_LT(std::abs(outputs.back() - setpoint), 1.0); 
}


TEST(SystemIntegrationTest, PIDControllerWithNonlinearPlant)
{
    std::vector<double> params = {0.8, 0.1, 0.3, 0.2};
    ProcessModel plant(params, 0.0);
    PIDController pid_controller(1.5, 0.8, 0.2, 0.5);

    plant.setInitialValue(0.0);
    pid_controller.reset();

    std::vector<double> outputs;
    double setpoint = 2.0;
    
    for (int i = 0; i < 15; i++)
    {
        double current_output = (outputs.empty()) ? 0.0 : outputs.back();
        double control_signal = pid_controller.calculate(setpoint, current_output);
        double new_output = plant.nonlinearModel(control_signal);
        outputs.push_back(new_output);
    }

    
    EXPECT_TRUE(std::isfinite(outputs.back()));
    EXPECT_GT(outputs.size(), 0);
}


TEST(SystemIntegrationTest, SystemStability)
{
    std::vector<double> params = {0.9, 0.1, 0.0, 0.0}; 
    ProcessModel plant(params, 0.0);
    PIDController controller(0.5, 1.0, 0.0, 1.0);

    plant.setInitialValue(0.0);
    controller.reset();

    std::vector<double> outputs;
    double setpoint = 1.0;
    
    for (int i = 0; i < 20; i++)
    {
        double current_output = (outputs.empty()) ? 0.0 : outputs.back();
        double control_signal = controller.calculate(setpoint, current_output);
        double new_output = plant.linearModel(control_signal);
        outputs.push_back(new_output);
    }

    
    EXPECT_TRUE(std::isfinite(outputs.back()));
    EXPECT_LT(std::abs(outputs.back()), 10.0); 
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}