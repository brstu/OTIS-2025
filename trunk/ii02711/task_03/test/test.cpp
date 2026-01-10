#include "gtest/gtest.h"
#include "../src/Model.h"

TEST(TestClass, chekQs2) {
	PID_reg p;
	p.Qs_find();
	double res1;
	double res2;
	double res3;
	p.GetQ(res1, res2, res3);
	EXPECT_NEAR(res1, 3, 0.1);
	EXPECT_NEAR(res2, -3.2, 0.1);
	EXPECT_NEAR(res3, 1.5, 0.1);
}