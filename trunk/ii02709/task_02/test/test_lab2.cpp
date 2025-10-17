#include <gtest/gtest.h>
#include "lab2.h"
#include <cmath>

// Тест 1: next_linear простая проверка формулы
TEST(NextLinearTest, Basic) {
    long double y = 1.5L;
    long double u = 2.0L;
    long double expected = lab2::a * y + lab2::b * u;
    ASSERT_NEAR(lab2::next_linear(y, u), expected, 1e-15L);
}

// Тест 2: next_nonlinear базовая проверка
TEST(NextNonlinearTest, Basic) {
    long double y = 1.5L;
    long double u = 2.0L;
    long double expected = lab2::a * y - lab2::b * y * y + lab2::c1 * u + lab2::c2 * std::sinh(u);
    ASSERT_NEAR(lab2::next_nonlinear(y, u), expected, 1e-14L);
}

// Тест 3: simulate_linear возвращает ожидаемую длину и первые значения
TEST(SimulateLinearTest, LengthAndValues) {
    int steps = 5;
    long double y0 = 1.0L;
    long double u = 0.5L;
    auto vals = lab2::simulate_linear(steps, y0, u);
    ASSERT_EQ((int)vals.size(), steps);
    // проверить первый элемент
    long double first_expected = lab2::next_linear(y0, u);
    ASSERT_NEAR(vals[0], first_expected, 1e-15L);
}

// Тест 4: simulate_nonlinear возвращает ожидаемую длину и первые значения
TEST(SimulateNonlinearTest, LengthAndValues) {
    int steps = 5;
    long double y0 = 1.0L;
    long double u = -1.2L; // тест с отрицательным u
    auto vals = lab2::simulate_nonlinear(steps, y0, u);
    ASSERT_EQ((int)vals.size(), steps);
    long double first_expected = lab2::next_nonlinear(y0, u);
    ASSERT_NEAR(vals[0], first_expected, 1e-14L);
}

// Тест 5: simulate_* с steps == 0 возвращает пустой вектор
TEST(SimulateEdgeCases, ZeroSteps) {
    auto v1 = lab2::simulate_linear(0, 1.0L, 0.0L);
    auto v2 = lab2::simulate_nonlinear(0, 1.0L, 0.0L);
    ASSERT_TRUE(v1.empty());
    ASSERT_TRUE(v2.empty());
}

// Тест 6: simulate_* с негативным steps выбрасывает исключение
TEST(SimulateEdgeCases, NegativeSteps) {
    EXPECT_THROW(lab2::simulate_linear(-1, 1.0L, 0.0L), std::invalid_argument);
    EXPECT_THROW(lab2::simulate_nonlinear(-5, 1.0L, 0.0L), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}