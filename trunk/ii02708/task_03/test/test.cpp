#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/pid.h"

TEST(TestPid, WhenSetpointIsTwo)
{   
    NonLinearCoeff coeff;
    coeff.a = 0.5;
    coeff.b = 0.2;
    coeff.c = 0.15;
    coeff.d = 0.3;
    coeff.u = 1.2;
    
    double y0 = 1.0;
    int n = 5;
    double setpoint = 2.0;
    
    std::vector<double> results = simulatePidRegulatorForNonlinear(coeff, y0, n, setpoint);
    std::vector<double> expected = {
        1.0,
        0.73520960570401428,
        0.69080628322815185,
        0.78596368906104797,
        0.84912544875185891
    };
    
    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_NEAR(results[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}

TEST(TestPid, WhenCustomPidCoefficients)
{   
    NonLinearCoeff coeff;
    coeff.a = 0.5;
    coeff.b = 0.2;
    coeff.c = 0.15;
    coeff.d = 0.3;
    coeff.u = 1.2;
    
    double y0 = 1.0;
    int n = 5;
    double setpoint = 3.0;
    double Kp = 2.0;
    double Ki = 0.5;
    double Kd = 0.1;
    double dt = 1.0;
    
    std::vector<double> results = simulatePidRegulatorForNonlinear(
        coeff, y0, n, setpoint, Kp, Ki, Kd, dt);
    std::vector<double> expected = {
        1.0,
        0.81496360328395412,
        1.2386319653734363,
        1.5053874385565871,
        1.5651009452716802
    };
    
    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_NEAR(results[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}