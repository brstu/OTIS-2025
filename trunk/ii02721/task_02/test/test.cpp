#include "gtest/gtest.h"
#include "../src/n_linear.h"

TEST(TestClass, lin) {
	double res;
	res = linear(2.3, 3.5, 12.6, 15.8);
	EXPECT_NEAR(res, 84.2, 0.1);
}
TEST(TestClass, lin2) {
	double res;
	res = linear(5.3, 4.2, 2.6, 5.8);
	EXPECT_NEAR(res, 38.1, 0.1);
}
TEST(TestClass, nonlin) {
	Nonl l = { 2.3, 4.5, 3.2, 6.7, 8.6, 4.6, 8.7, 9.1 };
	double res;
	res = nonlinear(l);
	EXPECT_NEAR(res, -303.9, 0.1);
}
TEST(TestClass, nonlin2) {
	Nonl l = { 4.7, 9.5, 13.2, 3.7, 8.6, 14.6, 4.7, 0.2 };
	double res;
	res = nonlinear(l);
	EXPECT_NEAR(res, 24.0, 0.1);
}
