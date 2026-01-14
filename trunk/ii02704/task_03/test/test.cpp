#include "gtest/gtest.h"
#include "../src/PID.h"

TEST(TestClass, chekQs2) {
	Qs q;
	q.T = 2.5;
	q.To = 1.3;
	q.Td = 1.4;
	q.k = 1.5;
	findQ(q);
	double res1 = q.q0;
	double res2 = q.q0;
	double res3 = q.q0;
	EXPECT_NEAR(res1, 3, 0.1);
	EXPECT_NEAR(res2, 3, 0.1);
	EXPECT_NEAR(res3, 3, 0.1);
}
