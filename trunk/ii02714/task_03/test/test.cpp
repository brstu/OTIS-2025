#include "pch.h"
#include "../src/Class.h"
#include "../src/PID.h"

TEST(TestClass, linearfun1) {
	Obj o;
	o.SetY(0, 1.0);
	o.SetU(0, 2.5);
	o.linear(0);
	double res = o.getY(1);
	EXPECT_NEAR(res, 3.5, 0.1);
}
TEST(TestClass, linearfun2) {
	Obj o;
	o.SetY(0, -2.0);
	o.SetU(0, 3.5);
	o.linear(0);
	double res = o.getY(1);
	EXPECT_NEAR(res, 1.5, 0.01);
}
TEST(TESTClass, funE1) {
	PID p(13,12.5);
	p.setE(3);
	double res = p.GetE(3);
	EXPECT_NEAR(res, 0.5, 0.01);
}
TEST(TESTClass, funE2) {
	PID p(2.5, 1.5);
	p.setE(3);
	double res = p.GetE(3);
	EXPECT_NEAR(res,1, 0.01);
}
TEST(TESTClass, funQ1) {
	PID p(2.5, 1.5);
	p.SetQs();
	double res = p.GetQs0();
	EXPECT_NEAR(res, 10.1,0.01);
}
TEST(TESTClass, funQ2) {
	PID p(2.5, 1.5);
	p.SetQs();
	double res = p.GetQs1();
	EXPECT_NEAR(res, -20, 0.01);
}
TEST(TESTClass, funQ3) {
	PID p(2.5, 1.5);
	p.SetQs();
	double res = p.GetQs2();
	EXPECT_NEAR(res, 10, 0.01);
}
TEST(TESTClass, funU1) {
	PID p(2.5, 1.5);
	p.SetQs();
	p.SetU(0);
	double res = p.GetUP(1);
	EXPECT_NEAR(res, 1, 0.01);
}
