#include "gtest/gtest.h"
#include "../src/linear.h"

TEST(Test, linearr) {
	double res;
	vector<double> y;
	vector<double> u;
	y.resize(2, 0);
	u.resize(2, 0);
	y[0] = 13;
	u[0] = 1.3;
	linear(0,2, y, u, 2.3, 5.6);
	res = y[1];
	EXPECT_NEAR(res, 75.79, 0.01);
}
TEST(Test, linearr2) {
	double res;
	vector<double> y;
	vector<double> u;
	y.resize(2, 0);
	u.resize(2, 0);
	y[0] = 2.6;
	u[0] = 3.5;
	linear(0,2, y, u, 14.7, 5.6);
	res = y[1];
	EXPECT_NEAR(res, 66, 0.01);
}

TEST(Test, linearr3) {
	double res;
	vector<double> y;
	vector<double> u;
	y.resize(2, 0);
	u.resize(2, 0);
	y[0] = 0.8;
	u[0] = 9.6;
	linear(0,2, y, u, 12.3, 7.3);
	res = y[1];
	EXPECT_NEAR(res, 75, 0.01);//123.92 правильный
}