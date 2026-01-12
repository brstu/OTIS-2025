#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>

TEST(LinearTest, Basic) {
    EXPECT_DOUBLE_EQ(linear(2.0, 3.0, 1.0, 4.0), 2.0 * 1.0 + 3.0 * 4.0);
}

TEST(LinearTest, Zero) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0, 5.0, 6.0), 0.0);
}

TEST(LinearTest, Negative) {
    EXPECT_DOUBLE_EQ(linear(-1.0, 2.0, 3.0, -4.0), -1.0 * 3.0 + 2.0 * -4.0);
}

TEST(NonlinearTest, BasicNoNonlin) {
    EXPECT_NEAR(nonlinear(1.0, 0.0, 1.0, 0.0, 0.0, 0.0), 1.0, 1e-9);
}

TEST(NonlinearTest, WithSquareTerm) {
    EXPECT_NEAR(nonlinear(2.0, 0.0, 1.0, 1.0, 0.0, 0.0), 1.0 * 2.0 - 1.0 * 4.0, 1e-9);
}

TEST(NonlinearTest, WithSinTerm) {
    EXPECT_NEAR(nonlinear(0.0, M_PI / 2, 0.0, 0.0, 0.0, 1.0), 1.0 * sin(M_PI / 2), 1e-9);
}

TEST(NonlinearTest, FullCombination) {
    double y = 1.5, u = M_PI;
    double a = 0.9, b = 0.1, c = 0.05, d = 0.01;
    double expected = a * y - b * pow(y, 2) + c * u + d * sin(u);
    EXPECT_NEAR(nonlinear(y, u, a, b, c, d), expected, 1e-9);
}

TEST(PIDTest, InitializationAndCompute) {
    PID pid(10.0, 0.1, 50.0, 1.0);
    // Вычисляем ожидаемые q0, q1, q2 вручную для проверки
    // q0 = K * (1 + Td / To) = 10 * (1 + 50/1) = 510
    // q1 = -K * (1 + 2*Td/To - To/Ti) = -10 * (1 + 100 - 10) = -10*91 = -910
    // q2 = K * Td / To = 10*50/1 = 500

    // Первый вызов: e=1.0, delta_u = 510*1 + (-910)*0 + 500*0 = 510, u=0+510=510
    double u1 = pid.compute(1.0);
    EXPECT_NEAR(u1, 510.0, 1e-9);

    // Второй вызов: e=0.5, delta_u = 510*0.5 + (-910)*1 + 500*0 = 255 - 910 = -655, u=510-655=-145
    double u2 = pid.compute(0.5);
    EXPECT_NEAR(u2, -145.0, 1e-9);

    // Третий вызов: e=0.0, delta_u = 510*0 + (-910)*0.5 + 500*1 = 0 - 455 + 500 = 45, u=-145+45=-100
    double u3 = pid.compute(0.0);
    EXPECT_NEAR(u3, -100.0, 1e-9);
}

TEST(PIDTest, ZeroParameters) {
    PID pid(0.0, 1.0, 0.0, 1.0); // K=0, должен давать u=0 всегда
    EXPECT_DOUBLE_EQ(pid.compute(10.0), 0.0);
    EXPECT_DOUBLE_EQ(pid.compute(5.0), 0.0);
}

TEST(PIDTest, NoDerivative) {
    PID pid(1.0, 1.0, 0.0, 1.0); // Td=0, PI-регулятор
    // q0 =1*(1+0/1)=1
    // q1=-1*(1+0 -1/1)=-1*(1-1)=0
    // q2=1*0/1=0
    double u1 = pid.compute(1.0); // delta_u=1*1 +0*0 +0*0=1, u=1
    EXPECT_DOUBLE_EQ(u1, 1.0);
    double u2 = pid.compute(1.0); // delta_u=1*1 +0*1 +0*0=1, u=2
    EXPECT_DOUBLE_EQ(u2, 2.0);
}