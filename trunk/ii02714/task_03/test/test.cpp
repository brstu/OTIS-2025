#include "gtest/gtest.h"
#include "../src/PID.h"

TEST(TestClass, calculQs) {
	PID p;
	p.calcul_q0_q1_q2();
	double res1;
	double res2;
	double res3;
	p.GetQs(res1, res2, res3);
	EXPECT_NEAR(res1, 0.95, 0.1);
	EXPECT_NEAR(res2, -0.87, 0.1);
	EXPECT_NEAR(res3, 0.45, 0.1);
}


