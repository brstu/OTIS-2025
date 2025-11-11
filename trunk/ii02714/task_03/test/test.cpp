#include "pch.h"
#include "C:\Users\boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\Class.h"
#include "C:\Users\boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\linaer.h"
#include "C:\Users\boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\PID.h"

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
	EXPECT_NEAR(res, 1.5, 0.1);
}
TEST(TESTClass, funE) {
	PID p;
	p.SetW(3, 13);
	p.SetY(3,12.5);
	double res = p.GetE(3);
	EXPECT_NEAR(res, 0.5, 0.1);
}