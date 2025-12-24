#include "gtest/gtest.h"
#include "../src/equations.h"

TEST(TestFuns, linear) {
	double y_next;
	double res;
	res = Linear(2.3, 3.2, 7.8, y_next, 7.8);
	EXPECT_NEAR(res, 42.9, 0.1);
}
TEST(TestFuns, linear2) {
	double y_next;
	double res;
	res = Linear(4.3, 3.2, 5.8, y_next, 2.8);
	EXPECT_NEAR(res, 33.9, 0.1);
}
TEST(TestFuns, nonlinear) {
	Constant k = { 2.3, 4.3, 1.5, 6.2 };
	double y_next;
	double res;
	res = Nonlinear(k, 1.6, 5.7, 7.2, y_next, 1.1);
	EXPECT_NEAR(res, 4.9, 0.1);
}
TEST(TestFuns, nonlinear2) {
	Constant k = { 3.3, 2.3, 2.5, 1.2 };
	double y_next;
	double res;
	res = Nonlinear(k, 5.6, 2.7, 0.2, y_next, 3.7);
	EXPECT_NEAR(res, -52.9, 0.1);
}