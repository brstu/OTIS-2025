#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

#include "../src/linear.h"
#include "../src/nonlinear.h"

TEST(TestLinear, WhenTimeIsFive)
{   
    LinearCoeff coeff;
    coeff.a = 0.5;
    coeff.b = 0.2;
    coeff.u = 1.2;
    
    double y0 = 1.0;
    int n = 5;
    
    std::vector<double> expected = {0.74, 0.61, 0.545, 0.5125, 0.49625};
    std::vector<double> actual = calculateLinear(coeff, y0, n);
    
    ASSERT_EQ(actual.size(), expected.size());
    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_NEAR(actual[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}

TEST(TestNonlinear, WhenTimeIsFive)
{   
    NonLinearCoeff coeff;
    coeff.a = 0.5;
    coeff.b = 0.2;
    coeff.c = 0.15;
    coeff.d = 0.3;
    coeff.u = 1.2;
    
    double y0 = 1.0;
    int n = 5;  
    std::vector<double> expected = {
        0.759611726,
        0.639417589,
        0.663918567,
        0.709800038,
        0.726354212
    };
    std::vector<double> actual = calculateNonlinear(coeff, y0, n);

    ASSERT_EQ(actual.size(), expected.size());
    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_NEAR(actual[i], expected[i], 1e-6) << "Mismatch at index " << i;
    }
}