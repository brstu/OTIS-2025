#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/main.h"
// Подключаем функции из main.cpp


TEST(LinearSimTest, BaseCase)
{
    std::vector<double> result = linearSim(2, 2.0);
    ASSERT_GE(result.size(), 2);
    double expected = 0.8 * 2.0 + 0.6 * 0.8;
    EXPECT_DOUBLE_EQ(result[1], expected);
}

TEST(LinearSimTest, ZeroStartTemp)
{
    std::vector<double> result = linearSim(3, 0.0);
    ASSERT_GE(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 0.6 * 0.8); // 0.48
    EXPECT_DOUBLE_EQ(result[2], 0.8 * 0.48 + 0.6 * 0.8); // 0.384 + 0.48 = 0.864
}

TEST(LinearSimTest, NegativeStartTemp)
{
    std::vector<double> result = linearSim(2, -2.0);
    ASSERT_GE(result.size(), 2);
    double expected = 0.8 * (-2.0) + 0.6 * 0.8; // -1.6 + 0.48 = -1.12
    EXPECT_DOUBLE_EQ(result[1], expected);
}

TEST(NonlinearSimTest, BaseCase)
{
    std::vector<double> result = nonlinearSim(3, 1.0);
    ASSERT_GE(result.size(), 3);
    
    // Проверяем второй элемент
    double expected_second = 0.8 * 1.0 + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], expected_second);
    
    // Проверяем третий элемент
    double expected_third = 0.8 * result[1] - 0.6 * result[0] * result[0] 
                          + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[2], expected_third);
}

TEST(NonlinearSimTest, ZeroStartTemp)
{
    std::vector<double> result = nonlinearSim(3, 0.0);
    ASSERT_GE(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 0.0);
    
    // Второй элемент не должен быть нулевым из-за sin(heat_input)
    double expected_second = 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], expected_second);
}

TEST(LinearSimTest, SingleElement)
{
    std::vector<double> result = linearSim(1, 5.0);
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0], 5.0);
}

TEST(NonlinearSimTest, TwoElements)
{
    std::vector<double> result = nonlinearSim(2, 3.0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    
    double expected_second = 0.8 * 3.0 + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], expected_second);
}

TEST(LinearSimTest, ZeroSteps)
{
    std::vector<double> result = linearSim(0, 1.0);
    EXPECT_TRUE(result.empty());
}

TEST(NonlinearSimTest, ZeroSteps)
{
    std::vector<double> result = nonlinearSim(0, 1.0);
    EXPECT_TRUE(result.empty());
}

TEST(LinearSimTest, MultipleSteps)
{
    std::vector<double> result = linearSim(5, 10.0);
    ASSERT_EQ(result.size(), 5);
    
    // Проверяем последовательные вычисления
    EXPECT_DOUBLE_EQ(result[0], 10.0);
    EXPECT_DOUBLE_EQ(result[1], 0.8 * 10.0 + 0.6 * 0.8); // 8.0 + 0.48 = 8.48
    EXPECT_DOUBLE_EQ(result[2], 0.8 * 8.48 + 0.6 * 0.8); // 6.784 + 0.48 = 7.264
    EXPECT_DOUBLE_EQ(result[3], 0.8 * 7.264 + 0.6 * 0.8); // 5.8112 + 0.48 = 6.2912
    EXPECT_DOUBLE_EQ(result[4], 0.8 * 6.2912 + 0.6 * 0.8); // 5.03296 + 0.48 = 5.51296
}

TEST(NonlinearSimTest, MultipleSteps)
{
    std::vector<double> result = nonlinearSim(4, 2.0);
    ASSERT_EQ(result.size(), 4);
    
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    
    // Проверяем второй элемент
    double second_expected = 0.8 * 2.0 + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[1], second_expected);
    
    // Проверяем третий элемент
    double third_expected = 0.8 * result[1] - 0.6 * result[0] * result[0] 
                          + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[2], third_expected);
    
    // Проверяем четвертый элемент
    double fourth_expected = 0.8 * result[2] - 0.6 * result[1] * result[1] 
                           + 0.4 * 0.8 + 2.2 * std::sin(0.8);
    EXPECT_DOUBLE_EQ(result[3], fourth_expected);
}

TEST(ComparisonTest, LinearVsNonlinearDifference)
{
    double start_temp = 5.0;
    int n = 4;
    
    auto linear_result = linearSim(n, start_temp);
    auto nonlinear_result = nonlinearSim(n, start_temp);
    
    ASSERT_EQ(linear_result.size(), n);
    ASSERT_EQ(nonlinear_result.size(), n);
    
    // Первый элемент должен быть одинаковым
    EXPECT_DOUBLE_EQ(linear_result[0], nonlinear_result[0]);
    
    // Начиная со второго элемента результаты должны различаться
    for (int i = 1; i < n; i++) {
        EXPECT_NE(linear_result[i], nonlinear_result[i]);
    }
}

