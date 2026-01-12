#include "gtest/gtest.h"
 29 #include "../src/Model.h"
 30 
 31 TEST(TestClass, chekQs2) {
 32     Models m(0.0,0.0,0.0,0.0)
	Qs q(1.2,1.4,2.3);
 34     double res1 = q.q0;
 35     double res2 = q.q1;
 36     double res3 = q.q2;
 38     EXPECT_NEAR(res1, 1.2, 0.1);
 39     EXPECT_NEAR(res2, 1.4, 0.1);
 40     EXPECT_NEAR(res3, 2.3, 0.1);
 41 }
