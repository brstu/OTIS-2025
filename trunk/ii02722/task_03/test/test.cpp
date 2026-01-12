#include "gtest/gtest.h"
#include "../src/Model.h"

TEST(TestClass, chekQs) {
	Const_ c(2.3, 3.4, 1.2, 1.05, 0.85, 0.05);
	Qs q(0.0, 0.0, 0.0);
	find_Qs(q, c);
	double res1 = q.q0;
	double res2 = q.q1;
	double res3 = q.q2;
	EXPECT_NEAR(res1, 4.025, 0.1);
	EXPECT_NEAR(res2, -6.45, 0.1);
	EXPECT_NEAR(res3, 3, 0.1);
}