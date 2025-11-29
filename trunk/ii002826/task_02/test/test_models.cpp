#include <gtest/gtest.h>
#include "../include/models.h"

// Тесты для линейной модели
TEST(LinearModelTest, BasicCalculation) {
    double result = linear_model(10.0, 5.0, 0.5, 0.2);
    EXPECT_DOUBLE_EQ(result, 0.5 * 10.0 + 0.2 * 5.0);
}

TEST(LinearModelTest, ZeroInput) {
    double result = linear_model(0.0, 0.0, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    double result = linear_model(-5.0, -3.0, 2.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 2.0 * (-5.0) + 1.0 * (-3.0));
}

TEST(LinearModelTest, UnitCoefficients) {
    double result = linear_model(7.5, 2.5, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 7.5 + 2.5);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BasicCalculation) {
    ModelParams params{ 0.5, 0.1, 0.3, 0.2 };
    double result = nonlinear_model(10.0, 8.0, 5.0, params);
    double expected = 0.5 * 10.0 - 0.1 * std::pow(8.0, 2) + 0.3 * 5.0 + 0.2 * std::sin(5.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, ZeroInput) {
    ModelParams params{ 1.0, 1.0, 1.0, 1.0 };
    double result = nonlinear_model(0.0, 0.0, 0.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, NegativeValues) {
    ModelParams params{ 2.0, 0.5, 1.0, 0.1 };
    double result = nonlinear_model(-3.0, -2.0, -1.0, params);
    double expected = 2.0 * (-3.0) - 0.5 * std::pow(-2.0, 2) + 1.0 * (-1.0) + 0.1 * std::sin(-1.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, ZeroCoefficients) {
    ModelParams params{ 0.0, 0.0, 0.0, 0.0 };
    double result = nonlinear_model(5.0, 3.0, 2.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, SineComponentOnly) {
    ModelParams params{ 0.0, 0.0, 0.0, 1.0 };
    double u = M_PI / 2; // sin(π/2) = 1
    double result = nonlinear_model(10.0, 8.0, u, params);
    EXPECT_DOUBLE_EQ(result, std::sin(u));
}

// Тесты для структуры ModelParams
TEST(ModelParamsTest, DefaultInitialization) {
    ModelParams params{};
    EXPECT_DOUBLE_EQ(params.a, 0.0);
    EXPECT_DOUBLE_EQ(params.b, 0.0);
    EXPECT_DOUBLE_EQ(params.c, 0.0);
    EXPECT_DOUBLE_EQ(params.d, 0.0);
}

TEST(ModelParamsTest, CustomInitialization) {
    ModelParams params{ 1.1, 2.2, 3.3, 4.4 };
    EXPECT_DOUBLE_EQ(params.a, 1.1);
    EXPECT_DOUBLE_EQ(params.b, 2.2);
    EXPECT_DOUBLE_EQ(params.c, 3.3);
    EXPECT_DOUBLE_EQ(params.d, 4.4);
}

// Интеграционные тесты
TEST(IntegrationTest, LinearModelStability) {
    double y_prev = 100.0;
    double u = 10.0;
    double a = 0.5;
    double b = 0.2;

    for (int i = 0; i < 10; ++i) {
        y_prev = linear_model(y_prev, u, a, b);
        EXPECT_TRUE(std::isfinite(y_prev));
    }
}

TEST(IntegrationTest, NonlinearModelStability) {
    ModelParams params{ 0.8, 0.01, 0.1, 0.05 };
    double y_prev = 50.0;
    double y_prev_2 = 45.0;
    double u = 5.0;

    for (int i = 0; i < 10; ++i) {
        double y_next = nonlinear_model(y_prev, y_prev_2, u, params);
        y_prev_2 = y_prev;
        y_prev = y_next;
        EXPECT_TRUE(std::isfinite(y_prev));
    }
}

// Тесты на граничные значения
TEST(BoundaryTest, LargeValues) {
    double result = linear_model(1e6, 1e6, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 2e6);

    ModelParams params{ 1.0, 1.0, 1.0, 1.0 };
    result = nonlinear_model(1e6, 1e6, 1e6, params);
    EXPECT_TRUE(std::isfinite(result));
}

TEST(BoundaryTest, SmallValues) {
    double result = linear_model(1e-6, 1e-6, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 2e-6);

    ModelParams params{ 1.0, 1.0, 1.0, 1.0 };
    result = nonlinear_model(1e-6, 1e-6, 1e-6, params);
    EXPECT_TRUE(std::isfinite(result));
}