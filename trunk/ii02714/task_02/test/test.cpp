#include "gtest/gtest.h"
#include "C:/Users/Boss/source/repos/otis2/otis2/Solution.h"
#include "pch.h"

TEST(TestClass, linearfun1) {
	Obj o;
	o.y.at(0) = 1.0;
	o.u.at(0) = 2.5;
	o.linear(0);
	double res = o.y.at(1); 
    EXPECT_EQ(res,3.5);
}
TEST(TestClass, linearfun2) {
	Obj o;
	o.y.at(0) = -2.0;
	o.u.at(0) = 3.5;
	o.linear(0);
	double res = o.y.at(1);
	EXPECT_EQ(res, 1.5);
}
TEST(Test2Class, Nonlinearfun1) {
	Obj o;
	o.y.at(0) = 1.0;
	o.y.at(1) = 3.0;
	o.u.at(0) = 2.5;
	o.u.at(1) = 0.5;
	o.nonlinear(1);
	double res = o.y.at(2);
	EXPECT_NEAR(res, 3,0.1);
}
TEST(Test2Class, Nonlinearfun2) {
	Obj o;
	o.y.at(0) = 0.0;
	o.y.at(1) = 7.0;
	o.u.at(0) = -4.5;
	o.u.at(1) = -0.5;
	o.nonlinear(1);
	double res = o.y.at(2);
	EXPECT_NEAR(res, 7,0.5);
}