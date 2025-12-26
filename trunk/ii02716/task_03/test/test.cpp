#include "gtest/gtest.h"
#include "../src/Equations.h"

TEST(TestFuns, LinearModel_chek1) {
	Equations eq(1.2, 1.4, 1.5, 1.6);
	Constunts con = { 0.85,0.05,1.5,1.2,1.4,1.6 };
	eq.LinearModel(con);
	double res;
	res = eq.GetY();
	EXPECT_NEAR(res, 1.25, 0.1);
}
TEST(TestFuns, LinearModel_chek2) {
	Equations eq(0.2, 0.4, 0.5, 0.6);
	Constunts con = { 0.85,0.05,1.5,1.2,1.4,1.6 };
	eq.LinearModel(con);
	double res;
	res = eq.GetY();
	EXPECT_NEAR(res,0.35, 0.1);
}