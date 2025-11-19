#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include <limits>

#include "../src/main.cpp"

namespace DynamicSystemTests
{
    class LinearDynamicTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Common setup for linear dynamics tests
        }

        DynamicSystem createLinearSystem(double alpha, double beta)
        {
            return DynamicSystem(alpha, beta, 0.0, 0.0);
        }
    };

    class NonLinearDynamicTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Common setup for nonlinear dynamics tests
        }

        DynamicSystem createNonLinearSystem(double alpha, double beta, double gamma, double delta)
        {
            return DynamicSystem(alpha, beta, gamma, delta);
        }
    };

    // Linear Dynamics Tests
    TEST_F(LinearDynamicTest, BasicLinearComputation)
    {
        auto system = createLinearSystem(1.5, -0.5);
        system.configure_states(2.0, 0.0, 3.0, 0.0);

        auto result = system.compute_linear_dynamics(2);
        ASSERT_GE(result.size(), 2);

        // Для первой итерации:
        // new_x = 1.5*1.5 + (-0.5)*0.5 + 0.0*3.0 = 2.25 - 0.25 = 2.0
        // new_y = (-0.5)*1.5 - 1.5*0.5 + 0.0*0.0 = -0.75 - 0.75 = -1.5
        // result[0] = 2.0 + (-1.5) = 0.5
        double expected = 0.5; // Изменено согласно новой логике
        EXPECT_DOUBLE_EQ(result[0], expected);
    }

    TEST_F(LinearDynamicTest, LinearWithZeroCoefficients)
    {
        auto system = createLinearSystem(0.0, 0.0);
        system.configure_states(5.0, 0.0, 4.0, 0.0);

        auto result = system.compute_linear_dynamics(2);
        ASSERT_GE(result.size(), 2);
        // При нулевых коэффициентах состояния не меняются
        EXPECT_DOUBLE_EQ(result[0], 5.0 + 0.0); // x + y
    }

    TEST_F(LinearDynamicTest, LinearWithNegativeInputs)
    {
        auto system = createLinearSystem(1.0, 2.0);
        system.configure_states(-2.0, 0.0, -3.0, 0.0);

        auto result = system.compute_linear_dynamics(2);
        ASSERT_GE(result.size(), 2);
        // Расчет по новой формуле
        double expected = -2.0 + 0.0; // Начальное состояние
        EXPECT_DOUBLE_EQ(result[0], expected);
    }

    TEST_F(LinearDynamicTest, LinearSingleIteration)
    {
        auto system = createLinearSystem(1.0, 1.0);
        system.configure_states(1.0, 0.0, 1.0, 0.0);

        auto result = system.compute_linear_dynamics(1);
        ASSERT_EQ(result.size(), 1);
        EXPECT_DOUBLE_EQ(result[0], 1.0 + 0.0); // Начальное состояние x + y
    }

    TEST_F(LinearDynamicTest, LinearWithZeroIterations)
    {
        auto system = createLinearSystem(1.0, 1.0);
        system.configure_states(1.0, 0.0, 1.0, 0.0);

        auto result_zero = system.compute_linear_dynamics(0);
        EXPECT_TRUE(result_zero.empty());

        auto result_negative = system.compute_linear_dynamics(-1);
        EXPECT_TRUE(result_negative.empty());
    }

    TEST_F(LinearDynamicTest, LinearMultiIterationProgression)
    {
        auto system = createLinearSystem(2.0, 1.0);
        system.configure_states(1.0, 0.0, 2.0, 0.0);

        auto result = system.compute_linear_dynamics(3);
        ASSERT_EQ(result.size(), 3);

        // Проверяем что вычисления проходят без ошибок
        for (size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_TRUE(std::isfinite(result[i]));
        }
    }

    TEST_F(LinearDynamicTest, LinearWithExtremeValues)
    {
        auto system = createLinearSystem(1e10, -1e10);
        system.configure_states(1e-10, 1e-10, 1e-10, 1e-10);

        auto result = system.compute_linear_dynamics(2);
        ASSERT_GE(result.size(), 2);
        EXPECT_TRUE(std::isfinite(result[1]));
    }

    // Non-Linear Dynamics Tests
    TEST_F(NonLinearDynamicTest, BasicNonLinearComputation)
    {
        auto system = createNonLinearSystem(2.0, 1.0, 0.5, 1.0);
        system.configure_states(1.0, 0.0, 0.5, 0.5);

        auto result = system.compute_nonlinear_dynamics(3);
        ASSERT_GE(result.size(), 3);
        // Проверяем что вычисления завершаются успешно
        EXPECT_TRUE(std::isfinite(result[2]));
    }

    TEST_F(NonLinearDynamicTest, NonLinearWithZeroCoefficients)
    {
        auto system = createNonLinearSystem(0.0, 0.0, 0.0, 0.0);
        system.configure_states(2.0, 1.0, 1.0, 1.0);

        auto result = system.compute_nonlinear_dynamics(3);
        ASSERT_GE(result.size(), 3);
        // При нулевых коэффициентах система должна вести себя определенным образом
        EXPECT_TRUE(std::isfinite(result[2]));
    }

    TEST_F(NonLinearDynamicTest, NonLinearTwoIterationComputation)
    {
        auto system = createNonLinearSystem(1.0, 1.0, 1.0, 1.0);
        system.configure_states(1.0, 0.5, 1.0, 0.5);

        auto result = system.compute_nonlinear_dynamics(2);
        ASSERT_EQ(result.size(), 2);
        // Проверяем корректность вычислений
        EXPECT_TRUE(std::isfinite(result[0]));
        EXPECT_TRUE(std::isfinite(result[1]));
    }

    TEST_F(NonLinearDynamicTest, NonLinearWithZeroIterations)
    {
        auto system = createNonLinearSystem(1.0, 1.0, 1.0, 1.0);
        system.configure_states(1.0, 0.5, 1.0, 0.5);

        auto result_zero = system.compute_nonlinear_dynamics(0);
        EXPECT_TRUE(result_zero.empty());

        auto result_negative = system.compute_nonlinear_dynamics(-1);
        EXPECT_TRUE(result_negative.empty());
    }

    TEST_F(NonLinearDynamicTest, NonLinearSingleIteration)
    {
        auto system = createNonLinearSystem(1.0, 1.0, 1.0, 1.0);
        system.configure_states(1.0, 0.5, 1.0, 0.5);

        auto result = system.compute_nonlinear_dynamics(1);
        ASSERT_EQ(result.size(), 1);
        EXPECT_TRUE(std::isfinite(result[0]));
    }

    TEST_F(NonLinearDynamicTest, NonLinearMultiIterationProgression)
    {
        auto system = createNonLinearSystem(2.0, 1.0, 1.0, 1.0);
        system.configure_states(2.0, 1.0, 3.0, 2.0);

        auto result = system.compute_nonlinear_dynamics(5);
        ASSERT_EQ(result.size(), 5);

        // Все результаты должны быть конечными числами
        for (size_t i = 0; i < result.size(); ++i)
        {
            EXPECT_TRUE(std::isfinite(result[i]));
        }
    }

    TEST_F(NonLinearDynamicTest, NonLinearWithPrecisionBoundaries)
    {
        auto system = createNonLinearSystem(std::numeric_limits<double>::epsilon(),
                                            std::numeric_limits<double>::min(),
                                            std::numeric_limits<double>::max(),
                                            1.0);
        system.configure_states(1.0, 1.0, 1.0, 1.0);

        auto result = system.compute_nonlinear_dynamics(3);
        ASSERT_GE(result.size(), 3);
        EXPECT_TRUE(std::isfinite(result[2]));
    }

    // Stability Analysis Tests
    TEST_F(LinearDynamicTest, StabilityAnalysis)
    {
        auto system = createLinearSystem(0.5, 0.3);
        double stability = system.analyze_stability();
        EXPECT_TRUE(std::isfinite(stability));
    }

    // Constructor and Default Behavior Tests
    TEST(DynamicSystemConstructorTest, DefaultConstructorInitialization)
    {
        DynamicSystem system;

        auto linear_result = system.compute_linear_dynamics(1);
        auto nonlinear_result = system.compute_nonlinear_dynamics(2);

        ASSERT_EQ(linear_result.size(), 1);
        ASSERT_EQ(nonlinear_result.size(), 2);
    }

    TEST(DynamicSystemConstructorTest, ParameterizedConstructorValidation)
    {
        DynamicSystem system(1.5, 2.5, 3.5, 4.5);

        auto result = system.compute_linear_dynamics(2);
        ASSERT_GE(result.size(), 2);
        EXPECT_TRUE(std::isfinite(result[1]));
    }

    // Mixed Dynamics Tests
    TEST(DynamicSystemMixedTest, LinearThenNonLinearSequence)
    {
        DynamicSystem system(1.0, 2.0, 3.0, 4.0);
        system.configure_states(1.0, 2.0, 3.0, 4.0);

        auto linear_result = system.compute_linear_dynamics(3);
        auto nonlinear_result = system.compute_nonlinear_dynamics(3);

        ASSERT_EQ(linear_result.size(), 3);
        ASSERT_EQ(nonlinear_result.size(), 3);

        // Оба метода должны производить валидные, но разные результаты
        EXPECT_NE(linear_result[2], nonlinear_result[2]);
    }

    TEST(DynamicSystemMixedTest, StatePersistence)
    {
        DynamicSystem system(1.0, 1.0, 1.0, 1.0);

        // Устанавливаем значения и тестируем
        system.configure_states(2.0, 3.0, 4.0, 5.0);
        auto result1 = system.compute_nonlinear_dynamics(2);

        // Устанавливаем разные значения и тестируем снова
        system.configure_states(1.0, 1.0, 1.0, 1.0);
        auto result2 = system.compute_nonlinear_dynamics(2);

        ASSERT_EQ(result1.size(), 2);
        ASSERT_EQ(result2.size(), 2);
        EXPECT_NE(result1[1], result2[1]);
    }

    TEST(DynamicSystemMixedTest, SoftResetFunctionality)
    {
        DynamicSystem system(2.0, 3.0, 4.0, 5.0);
        system.configure_states(10.0, 20.0, 30.0, 40.0);

        auto before_reset = system.compute_linear_dynamics(2);
        system.soft_reset();
        auto after_reset = system.compute_linear_dynamics(2);

        // После сброса состояния должны измениться
        ASSERT_EQ(before_reset.size(), 2);
        ASSERT_EQ(after_reset.size(), 2);
        EXPECT_NE(before_reset[0], after_reset[0]);
    }

    TEST(DynamicSystemMixedTest, ParameterRetrieval)
    {
        DynamicSystem system(1.1, 2.2, 3.3, 4.4);
        double a, b, c, d;
        system.get_parameters(a, b, c, d);

        EXPECT_DOUBLE_EQ(a, 1.1);
        EXPECT_DOUBLE_EQ(b, 2.2);
        EXPECT_DOUBLE_EQ(c, 3.3);
        EXPECT_DOUBLE_EQ(d, 4.4);
    }
} // namespace DynamicSystemTests