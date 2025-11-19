#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include <limits>

#include "../src/main.cpp"

namespace QuantumSystemTests
{
    class LinearQuantumTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Common setup for linear quantum tests
        }

        QuantumDynamicModel createLinearQuantum(double qf, double te)
        {
            return QuantumDynamicModel(qf, te, 0.0, 0.0);
        }
    };

    class NonLinearQuantumTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Common setup for nonlinear quantum tests
        }

        QuantumDynamicModel createNonLinearQuantum(double qf, double te, double cr, double cf)
        {
            return QuantumDynamicModel(qf, te, cr, cf);
        }
    };

    // Linear Quantum Tests
    TEST_F(LinearQuantumTest, BasicQuantumComputation)
    {
        auto quantum_system = createLinearQuantum(1.5, -0.5);
        quantum_system.configure_quantum_states(2.0, 0.0, 3.0, 0.0);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(2);
        ASSERT_GE(quantum_result.size(), 2);
        double quantum_expected = 1.5 * 2.0 + (-0.5) * 3.0;
        EXPECT_DOUBLE_EQ(quantum_result[1], quantum_expected);
    }

    TEST_F(LinearQuantumTest, QuantumWithZeroCoefficients)
    {
        auto quantum_system = createLinearQuantum(0.0, 0.0);
        quantum_system.configure_quantum_states(5.0, 0.0, 4.0, 0.0);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(2);
        ASSERT_GE(quantum_result.size(), 2);
        EXPECT_DOUBLE_EQ(quantum_result[1], 0.0);
    }

    TEST_F(LinearQuantumTest, QuantumWithNegativeInputs)
    {
        auto quantum_system = createLinearQuantum(1.0, 2.0);
        quantum_system.configure_quantum_states(-2.0, 0.0, -3.0, 0.0);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(2);
        ASSERT_GE(quantum_result.size(), 2);
        double quantum_expected = 1.0 * (-2.0) + 2.0 * (-3.0);
        EXPECT_DOUBLE_EQ(quantum_result[1], quantum_expected);
    }

    TEST_F(LinearQuantumTest, QuantumSingleOscillation)
    {
        auto quantum_system = createLinearQuantum(1.0, 1.0);
        quantum_system.configure_quantum_states(1.0, 0.0, 1.0, 0.0);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(1);
        ASSERT_EQ(quantum_result.size(), 1);
        EXPECT_DOUBLE_EQ(quantum_result[0], 1.0);
    }

    TEST_F(LinearQuantumTest, QuantumWithZeroOscillations)
    {
        auto quantum_system = createLinearQuantum(1.0, 1.0);
        quantum_system.configure_quantum_states(1.0, 0.0, 1.0, 0.0);

        auto result_zero = quantum_system.compute_quantum_wavefunction(0);
        EXPECT_TRUE(result_zero.empty());

        auto result_negative = quantum_system.compute_quantum_wavefunction(-1);
        EXPECT_TRUE(result_negative.empty());
    }

    TEST_F(LinearQuantumTest, QuantumMultiOscillationProgression)
    {
        auto quantum_system = createLinearQuantum(2.0, 1.0);
        quantum_system.configure_quantum_states(1.0, 0.0, 2.0, 0.0);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(5);
        ASSERT_EQ(quantum_result.size(), 5);

        std::vector<double> expected_quantum_states = {1.0, 4.0, 10.0, 22.0, 46.0};
        for (size_t i = 0; i < expected_quantum_states.size(); ++i)
        {
            EXPECT_DOUBLE_EQ(quantum_result[i], expected_quantum_states[i]);
        }
    }

    TEST_F(LinearQuantumTest, QuantumWithExtremeValues)
    {
        auto quantum_system = createLinearQuantum(1e10, -1e10);
        quantum_system.configure_quantum_states(1e-10, 0.0, 1e-10, 0.0);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(3);
        ASSERT_GE(quantum_result.size(), 3);
        EXPECT_NEAR(quantum_result[1], 0.0, 1e-6);
    }

    // Non-Linear Quantum Tests
    TEST_F(NonLinearQuantumTest, BasicChaoticComputation)
    {
        auto chaotic_system = createNonLinearQuantum(2.0, 1.0, 0.5, 1.0);
        chaotic_system.configure_quantum_states(1.0, 0.0, 0.5, 0.5);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(3);
        ASSERT_GE(chaotic_result.size(), 3);
        double chaotic_expected = 2.0 * 1.0 - 1.0 * std::pow(0.0, 2) + 0.5 * 0.5 + 1.0 * std::sin(0.5);
        EXPECT_DOUBLE_EQ(chaotic_result[2], chaotic_expected);
    }

    TEST_F(NonLinearQuantumTest, ChaoticWithZeroCoefficients)
    {
        auto chaotic_system = createNonLinearQuantum(0.0, 0.0, 0.0, 0.0);
        chaotic_system.configure_quantum_states(2.0, 1.0, 1.0, 1.0);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(3);
        ASSERT_GE(chaotic_result.size(), 3);
        EXPECT_DOUBLE_EQ(chaotic_result[2], 0.0);
    }

    TEST_F(NonLinearQuantumTest, ChaoticTwoOscillationComputation)
    {
        auto chaotic_system = createNonLinearQuantum(1.0, 1.0, 1.0, 1.0);
        chaotic_system.configure_quantum_states(1.0, 0.5, 1.0, 0.5);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(2);
        ASSERT_EQ(chaotic_result.size(), 2);
        EXPECT_DOUBLE_EQ(chaotic_result[0], 0.5);
        EXPECT_DOUBLE_EQ(chaotic_result[1], 1.0);
    }

    TEST_F(NonLinearQuantumTest, ChaoticWithZeroOscillations)
    {
        auto chaotic_system = createNonLinearQuantum(1.0, 1.0, 1.0, 1.0);
        chaotic_system.configure_quantum_states(1.0, 0.5, 1.0, 0.5);

        auto result_zero = chaotic_system.compute_chaotic_resonance(0);
        EXPECT_TRUE(result_zero.empty());

        auto result_negative = chaotic_system.compute_chaotic_resonance(-1);
        EXPECT_TRUE(result_negative.empty());
    }

    TEST_F(NonLinearQuantumTest, ChaoticSingleOscillation)
    {
        auto chaotic_system = createNonLinearQuantum(1.0, 1.0, 1.0, 1.0);
        chaotic_system.configure_quantum_states(1.0, 0.5, 1.0, 0.5);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(1);
        ASSERT_EQ(chaotic_result.size(), 1);
        EXPECT_DOUBLE_EQ(chaotic_result[0], 0.5);
    }

    TEST_F(NonLinearQuantumTest, ChaoticMultiOscillationProgression)
    {
        auto chaotic_system = createNonLinearQuantum(2.0, 1.0, 1.0, 1.0);
        chaotic_system.configure_quantum_states(2.0, 1.0, 3.0, 2.0);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(5);
        ASSERT_EQ(chaotic_result.size(), 5);

        EXPECT_DOUBLE_EQ(chaotic_result[0], 1.0);
        EXPECT_DOUBLE_EQ(chaotic_result[1], 2.0);

        double expected_oscillation = 2.0 * 2.0 - 1.0 * std::pow(1.0, 2) + 1.0 * 3.0 + 1.0 * std::sin(2.0);
        EXPECT_DOUBLE_EQ(chaotic_result[2], expected_oscillation);
    }

    TEST_F(NonLinearQuantumTest, ChaoticSinusoidalDominance)
    {
        auto chaotic_system = createNonLinearQuantum(0.0, 0.0, 0.0, 2.0);
        chaotic_system.configure_quantum_states(0.0, 0.0, 0.0, M_PI / 2);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(3);
        ASSERT_GE(chaotic_result.size(), 3);
        EXPECT_DOUBLE_EQ(chaotic_result[2], 2.0);
    }

    TEST_F(NonLinearQuantumTest, ChaoticSpecialCaseValues)
    {
        auto chaotic_system = createNonLinearQuantum(0.0, 0.0, 0.0, 0.0);
        chaotic_system.configure_quantum_states(1.0, 2.0, 3.0, 4.0);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(4);
        ASSERT_EQ(chaotic_result.size(), 4);

        std::vector<double> expected_chaotic_states = {2.0, 1.0, 0.0, 0.0};
        for (size_t i = 0; i < expected_chaotic_states.size(); ++i)
        {
            EXPECT_DOUBLE_EQ(chaotic_result[i], expected_chaotic_states[i]);
        }
    }

    TEST_F(NonLinearQuantumTest, ChaoticWithPrecisionBoundaries)
    {
        auto chaotic_system = createNonLinearQuantum(std::numeric_limits<double>::epsilon(),
                                                     std::numeric_limits<double>::min(),
                                                     std::numeric_limits<double>::max(),
                                                     1.0);
        chaotic_system.configure_quantum_states(1.0, 1.0, 1.0, 1.0);

        auto chaotic_result = chaotic_system.compute_chaotic_resonance(3);
        ASSERT_GE(chaotic_result.size(), 3);
        EXPECT_TRUE(std::isfinite(chaotic_result[2]));
    }

    // Constructor and Default Behavior Tests
    TEST(QuantumConstructorTest, DefaultConstructorInitialization)
    {
        QuantumDynamicModel quantum_system;

        auto linear_quantum_result = quantum_system.compute_quantum_wavefunction(1);
        auto chaotic_quantum_result = quantum_system.compute_chaotic_resonance(2);

        ASSERT_EQ(linear_quantum_result.size(), 1);
        ASSERT_EQ(chaotic_quantum_result.size(), 2);
    }

    TEST(QuantumConstructorTest, ParameterizedConstructorValidation)
    {
        QuantumDynamicModel quantum_system(1.5, 2.5, 3.5, 4.5);

        auto quantum_result = quantum_system.compute_quantum_wavefunction(2);
        ASSERT_GE(quantum_result.size(), 2);
        EXPECT_TRUE(std::isfinite(quantum_result[1]));
    }

    // Mixed Quantum Tests
    TEST(QuantumMixedTest, LinearThenChaoticSequence)
    {
        QuantumDynamicModel quantum_system(1.0, 2.0, 3.0, 4.0);
        quantum_system.configure_quantum_states(1.0, 2.0, 3.0, 4.0);

        auto linear_quantum_result = quantum_system.compute_quantum_wavefunction(3);
        auto chaotic_quantum_result = quantum_system.compute_chaotic_resonance(3);

        ASSERT_EQ(linear_quantum_result.size(), 3);
        ASSERT_EQ(chaotic_quantum_result.size(), 3);
        EXPECT_NE(linear_quantum_result[2], chaotic_quantum_result[2]);
    }

    TEST(QuantumMixedTest, QuantumStatePersistence)
    {
        QuantumDynamicModel quantum_system(1.0, 1.0, 1.0, 1.0);

        quantum_system.configure_quantum_states(2.0, 3.0, 4.0, 5.0);
        auto quantum_result1 = quantum_system.compute_chaotic_resonance(2);

        quantum_system.configure_quantum_states(1.0, 1.0, 1.0, 1.0);
        auto quantum_result2 = quantum_system.compute_chaotic_resonance(2);

        ASSERT_EQ(quantum_result1.size(), 2);
        ASSERT_EQ(quantum_result2.size(), 2);
        EXPECT_NE(quantum_result1[1], quantum_result2[1]);
    }
} // namespace QuantumSystemTests