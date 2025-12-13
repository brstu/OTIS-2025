#include "gtest/gtest.h"
#include "../src/Linear.h"
#include "../src/Nonlinear.h"

TEST(Test, linearr) {
	double res = 5.6;
	Linear(2.3, 3.4, 1, res, 13.4);
	EXPECT_NEAR(res, 58.44, 0.01);
}

TEST(Test, linearr2) {
	double res = 5.6;
	Linear(4.3, 5.6, 1, res, 7.4);
	EXPECT_NEAR(res, 65.52, 0.01);
}

TEST(Test2, nonlinearr) {
	Constant c;
	c.param_a = 2.3;
	c.param_b = 2.3;
	c.param_c = 2.3;
	c.param_d = 2.3;
	double res = 5.6;
	Nonlinear(c,1, res, 2.76, 4.56, 6.54,5.34);
	EXPECT_NEAR(res, -81.0, 0.01);
}
