#include "gtest/gtest.h"
#include "../src/Linear.h"
TEST(Test, linearr) {
	double res;
	Params p;
	p.y.resize(2, 0);
	p.u.resize(2, 0);
	p.k = 2;
	p.y[0] = 13;
    p.u[0] = 1.3;
	p.a = 2.3;
	p.b = 5.6;
	linear(p,0);
	res = p.y[1];
	EXPECT_NEAR(res, 37.18, 0.01);
}
TEST(Test, linearr2) {
	double res;
	Params p;
	p.y.resize(2, 0);
	p.u.resize(2, 0);
	p.k = 2;
	p.y[0] = 2.6;
	p.u[0] = 3.5;
	p.a = 14.7;
	p.b = 5.6;
	linear(p,0);
	res = p.y[1];
	EXPECT_NEAR(res, 57.82, 0.01);
}

TEST(Test, linearr3) {
	double res;
	Params p;
	p.y.resize(2, 0);
	p.u.resize(2, 0);
	p.k = 2;
	p.y[0] = 0.8;
	p.u[0] = 9.6;
	p.a = 12.3;
	p.b = 7.3;
	linear(p,0);
	res = p.y[1];
	EXPECT_NEAR(res, 79.92, 0.01); 
}
