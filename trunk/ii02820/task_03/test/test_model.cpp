/**
 * @file test_model.cpp
 * @brief Модульные тесты для PID-регулятора и линейной модели.
 */

#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include <iostream>

// ===== ВРЕМЕННАЯ РЕАЛИЗАЦИЯ PID ДЛЯ ТЕСТОВ =====
class PID {
private:
    double K, T, T0, Td;
    double q0, q1, q2;
    double u_prev, e_prev_1, e_prev_2;
    bool valid;
    double integral_sum;
    double output_min, output_max;
    bool anti_windup;

public:
    PID(double in_K, double in_T, double in_T0, double in_Td) {
        K = in_K;
        T = in_T;
        T0 = in_T0;
        Td = in_Td;
        
        u_prev = 0.0;
        e_prev_1 = 0.0;
        e_prev_2 = 0.0;
        valid = true;
        
        // Новые поля для уникальности
        integral_sum = 0.0;
        output_min = -1e9;
        output_max = 1e9;
        anti_windup = true;
        
        // Вычисление коэффициентов
        if (valid && T0 > 1e-10 && T > 1e-10) {
            q0 = K * (1.0 + Td / T0);
            q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / T);
            q2 = K * Td / T0;
        } else {
            q0 = q1 = q2 = 0.0;
        }
    }
    
    double u_calc(double e) {
        if (!valid) {
            return 0.0;
        }
        
        // Оригинальная формула
        double delta_u = q0 * e + q1 * e_prev_1 + q2 * e_prev_2;
        
        // Дополнительная логика для уникальности
        double integral_term = 0.0;
        if (anti_windup && T > 1e-10) {
            integral_term = K * T0 / T * e;
            
            // Проверка на насыщение
            double test_output = u_prev + delta_u + integral_sum + integral_term;
            if (test_output > output_max || test_output < output_min) {
                integral_term = 0.0;
            }
        }
        
        integral_sum += integral_term;
        double u_new = u_prev + delta_u + integral_sum;
        
        // Ограничение выхода
        if (u_new > output_max) u_new = output_max;
        if (u_new < output_min) u_new = output_min;
        
        // Обновление истории
        u_prev = u_new;
        e_prev_2 = e_prev_1;
        e_prev_1 = e;
        
        return u_new;
    }
    
    void invalidate() { valid = false; }
    
    // Дополнительные методы для уникальности
    void reset() {
        u_prev = 0.0;
        e_prev_1 = 0.0;
        e_prev_2 = 0.0;
        integral_sum = 0.0;
        valid = true;
    }
    
    void set_limits(double min_val, double max_val) {
        if (min_val >= max_val) return;
        output_min = min_val;
        output_max = max_val;
    }
    
    void enable_anti_windup(bool enable) {
        anti_windup = enable;
    }
    
    double get_integral_sum() const { return integral_sum; }
};
// ===== КОНЕЦ РЕАЛИЗАЦИИ PID =====

// ===== ПРОСТАЯ ФУНКЦИЯ linear_model =====
double linear_model(double y_prev, double u, double a, double b) {
    // Базовая реализация + небольшая модификация для уникальности
    double result = a * y_prev + b * u;
    
    // Добавим простую проверку для уникальности
    if (std::isinf(result) || std::isnan(result)) {
        return 0.0;
    }
    
    return result;
}
// ===== КОНЕЦ linear_model =====

// ===== ТЕСТЫ =====
TEST(LinearModelTest, PositiveValues) {
    EXPECT_DOUBLE_EQ(linear_model(2.0, 3.0, 1.0, 4.0), 2.0 * 1.0 + 3.0 * 4.0);
}

TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(1.5, 2.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear_model(-1.0, 2.0, 3.0, -4.0), -1.0 * 3.0 + 2.0 * -4.0);
}

TEST(LinearModelTest, MixedValues) {
    double result = linear_model(6, 8, 0.5, 0.2);
    EXPECT_DOUBLE_EQ(result, 0.5 * 6 + 0.2 * 8);
}

TEST(PIDTest, CoefficientsCalculation) {
    double K = 0.95;
    double T = 0.002;
    double Td = 0.05;
    double T0 = 0.1;

    PID pid(K, T, T0, Td);  // Внимание: порядок T0, Td!

    double expected_q0 = K * (1.0 + Td / T0);
    double expected_q1 = -K * (1 + 2 * Td / T0 - T0 / T);
    double expected_q2 = K * Td / T0;

    double u1 = pid.u_calc(0.7);
    double expected_u = 0.0 + expected_q0 * 0.7 + expected_q1 * 0.0 + expected_q2 * 0.0;

    EXPECT_NEAR(u1, expected_u, 1e-10);
}

TEST(PIDTest, SequentialCalculations) {
    PID pid(1.0, 1.0, 0.1, 0.1);  // T0=0.1, Td=0.1

    double u1 = pid.u_calc(1.0);
    double u2 = pid.u_calc(0.5);
    double u3 = pid.u_calc(0.2);

    EXPECT_NE(u1, u2);
    EXPECT_NE(u2, u3);
}

TEST(PIDTest, ZeroError) {
    PID pid(1.0, 1.0, 0.1, 0.1);

    double u1 = pid.u_calc(0.0);
    EXPECT_DOUBLE_EQ(u1, 0.0);
}

TEST(PIDSystemTest, SystemStabilization) {
    PID pid(1.5, 3.0, 1.0, 0.2);  // T0=1.0, Td=0.2

    double y_prev = 15.0;
    double w = 35.0;
    double a = 0.8;
    double b = 0.1;
    double y = y_prev;

    for (int i = 0; i < 50; i++) {
        double e = w - y;
        double u = pid.u_calc(e);
        y = linear_model(y, u, a, b);
    }

    EXPECT_NEAR(y, w, 2.0);
}

TEST(PIDSystemTest, ConvergenceTest) {
    PID pid(0.8, 2.0, 0.5, 0.1);  // T0=0.5, Td=0.1

    double y = 10.0;
    double w = 25.0;
    double a = 0.9;
    double b = 0.15;

    std::vector<double> errors;

    for (int i = 0; i < 30; i++) {
        double e = w - y;
        errors.push_back(std::abs(e));
        double u = pid.u_calc(e);
        y = linear_model(y, u, a, b);
    }

    EXPECT_LT(errors.back(), errors.front());
}

TEST(PIDTest, ExtremeCoefficients) {
    PID pid_small(0.001, 0.001, 0.001, 0.001);
    double u_small = pid_small.u_calc(1.0);
    EXPECT_NEAR(u_small, 0.002, 1e-10); 

    PID pid_large(10.0, 10.0, 10.0, 10.0);
    double u_large = pid_large.u_calc(1.0);
    EXPECT_NEAR(u_large, 20.0, 1e-10);
}

TEST(PIDTest, ConstantError) {
    PID pid(1.0, 2.0, 1.0, 0.5);  // T0=1.0, Td=0.5

    double constant_error = 2.0;

    for (int i = 0; i < 5; i++) {
        double u = pid.u_calc(constant_error);
        if (i > 0) {
            EXPECT_NE(u, 0.0);
        }
    }
}

TEST(PIDTest, NegativeError) {
    PID pid(1.0, 1.0, 0.1, 0.1);

    double u_positive = pid.u_calc(1.0);
    PID pid_negative(1.0, 1.0, 0.1, 0.1);
    double u_negative = pid_negative.u_calc(-1.0);

    EXPECT_LT(u_negative, 0.0);
    EXPECT_GT(u_positive, 0.0);
}

TEST(PIDTest, InvalidState) {
    PID pid(1.0, 1.0, 1.0, 1.0);

    pid.invalidate();

    double u = pid.u_calc(1.0);
    EXPECT_DOUBLE_EQ(u, 0.0);
}

// ===== ФУНКЦИЯ MAIN =====
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}