#include "gtest/gtest.h"
#include "../src/LinearSystem.h"
#include "../src/NonLinearSystem.h"

TEST(TestFuns, LinearSystem_chek1) {
	LinearSystem l(2.3,5.6,8.7);
	float res;
	res = l.calculateNext(12.3);
	EXPECT_NEAR(res, 77.0, 0.1);
}
TEST(TestFuns, LinearSystem_chek2) {
	LinearSystem l(2.3, 5.6, 8.7);
	float res;
	res = l.calculateNext(1.3);
	EXPECT_NEAR(res, 51.7, 0.1);
}
TEST(TestFuns, NonLinearSystem_chek1) {
	NonlinearSystem l(1.5,4.8,2.4,3.9,5.7);
	float res;
	res = l.calculateNext(5.3,8.7);
	EXPECT_NEAR(res, -343.82, 0.1);
}
TEST(TestFuns, NonLinearSystem_chek2) {
	NonlinearSystem l(1.5, 3.8, 2.4, 3.9, 3.7);
	float res;
	res = l.calculateNext(7.6,0.9);
	EXPECT_NEAR(res, 15.13, 0.1);
}