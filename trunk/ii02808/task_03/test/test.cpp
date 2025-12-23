/**
 * @file test.cpp
 * @brief Модульные тесты для ПИД-регулятора и динамической системы
 */

#include <gtest/gtest.h>
#include <cmath>
#include "../src/pid_controller.h"
#include "../src/process_model.h"

/**
 * @brief Тестирование конструктора и базовых параметров регулятора
 */
TEST(PIDRegulatorTest, ConstructorValidation)
{
    // Проверка корректной инициализации регулятора
    PIDRegulator regulator(2.5, 1.2, 0.3, 0.1);
    
    // Проверка расчета управляющего воздействия
    double control_output = regulator.computeControl(5.0, 0.0);
    EXPECT_TRUE(std::isfinite(control_output));
    EXPECT_NE(control_output, 0.0);
}

/**
 * @brief Тестирование пропорционального регулятора (П-регулятор)
 */
TEST(PIDRegulatorTest, ProportionalActionTest)
{
    // Создание П-регулятора (T очень большое, Td = 0)
    PIDRegulator p_regulator(1.5, 1000.0, 0.0, 1.0);
    p_regulator.clearState();

    // Тест 1: Рассогласование 1.0
    double control1 = p_regulator.computeControl(1.0, 0.0);
    EXPECT_NEAR(control1, 1.5 * 1.0, 1e-6);

    // Тест 2: Рассогласование 0.5
    double control2 = p_regulator.computeControl(1.0, 0.5);
    EXPECT_NEAR(control2, 1.5 * 0.5, 1e-6);

    // Тест 3: Нулевое рассогласование
    double control3 = p_regulator.computeControl(1.0, 1.0);
    EXPECT_NEAR(control3, 0.0, 1e-6);
}

/**
 * @brief Тестирование пропорционально-интегрального регулятора (ПИ-регулятор)
 */
TEST(PIDRegulatorTest, ProportionalIntegralActionTest)
{
    // Создание ПИ-регулятора
    PIDRegulator pi_regulator(2.0, 0.5, 0.0, 0.1);
    pi_regulator.clearState();

    // Последовательное вычисление управляющих воздействий
    double control_signal1 = pi_regulator.computeControl(2.0, 0.0);
    double control_signal2 = pi_regulator.computeControl(2.0, 0.5);
    double control_signal3 = pi_regulator.computeControl(2.0, 1.0);

    // Проверка накопления интегральной составляющей
    EXPECT_GT(control_signal2, control_signal1);
    EXPECT_GT(control_signal3, control_signal2);
}

/**
 * @brief Тестирование сброса внутреннего состояния регулятора
 */
TEST(PIDRegulatorTest, StateResetVerification)
{
    PIDRegulator regulator(3.0, 2.0, 0.2, 0.5);
    
    // Выполнение нескольких расчетов для накопления состояния
    regulator.computeControl(10.0, 0.0);
    regulator.computeControl(10.0, 2.0);
    
    // Сброс состояния
    regulator.clearState();
    
    // Проверка, что после сброса регулятор работает корректно
    double initial_control = regulator.computeControl(5.0, 0.0);
    EXPECT_TRUE(std::isfinite(initial_control));
    EXPECT_NE(initial_control, 0.0);
}

/**
 * @brief Тестирование получения коэффициентов рекуррентного алгоритма
 */
TEST(PIDRegulatorTest, CoefficientRetrieval)
{
    PIDRegulator regulator(1.0, 2.0, 0.5, 0.1);
    std::vector<double> coefficients = regulator.obtainCoefficients();
    
    // Проверка количества коэффициентов
    EXPECT_EQ(coefficients.size(), 3);
    
    // Проверка, что все коэффициенты конечны
    for (double coeff : coefficients) {
        EXPECT_TRUE(std::isfinite(coeff));
    }
}

/**
 * @brief Тестирование линейной модели динамической системы
 */
TEST(DynamicSystemTest, LinearModelEvaluation)
{
    std::vector<double> system_params = {0.6, 0.4, 0.0, 0.0};
    DynamicSystem dynamic_model(system_params, 2.0);

    // Первый шаг моделирования
    double output1 = dynamic_model.evaluateLinear(3.0);
    double expected1 = 0.6 * 2.0 + 0.4 * 3.0;
    EXPECT_NEAR(output1, expected1, 1e-6);

    // Второй шаг моделирования
    double output2 = dynamic_model.evaluateLinear(4.0);
    double expected2 = 0.6 * output1 + 0.4 * 4.0;
    EXPECT_NEAR(output2, expected2, 1e-6);
}

/**
 * @brief Тестирование нелинейной модели динамической системы
 */
TEST(DynamicSystemTest, NonlinearModelEvaluation)
{
    std::vector<double> system_params = {0.7, 0.15, 0.2, 0.05};
    DynamicSystem dynamic_model(system_params, 1.5);

    double control_input = 2.0;
    double system_output = dynamic_model.evaluateNonlinear(control_input);
    
    // Расчет ожидаемого значения с учетом изменений (cos вместо sin)
    double expected_output = 0.7 * 1.5 - 0.15 * 1.5 * 1.5 
                           + 0.2 * control_input + 0.05 * std::cos(control_input);
    
    EXPECT_NEAR(system_output, expected_output, 1e-6);
}

/**
 * @brief Тестирование инициализации начального состояния системы
 */
TEST(DynamicSystemTest, StateInitializationTest)
{
    std::vector<double> system_params = {0.8, 0.2, 0.0, 0.0};
    DynamicSystem dynamic_model(system_params, 0.0);
    
    // Изменение начального состояния
    dynamic_model.initializeState(3.0);
    
    double system_response = dynamic_model.evaluateLinear(1.0);
    double expected_response = 0.8 * 3.0 + 0.2 * 1.0;
    
    EXPECT_NEAR(system_response, expected_response, 1e-6);
}

/**
 * @brief Интеграционный тест: П-регулятор с линейной системой
 */
TEST(SystemIntegrationTest, ProportionalControlWithLinearSystem)
{
    std::vector<double> linear_params = {0.75, 0.25, 0.0, 0.0};
    DynamicSystem linear_system(linear_params, 0.0);
    PIDRegulator p_controller(2.5, 1000.0, 0.0, 0.5);

    linear_system.initializeState(0.0);
    p_controller.clearState();

    std::vector<double> system_responses;
    const double reference_value = 3.0;
    const int simulation_steps = 8;
    
    for (int step = 0; step < simulation_steps; ++step)
    {
        double current_state = system_responses.empty() ? 0.0 : system_responses.back();
        double control_action = p_controller.computeControl(reference_value, current_state);
        double system_output = linear_system.evaluateLinear(control_action);
        system_responses.push_back(system_output);
    }

    // Проверка стабильности системы
    EXPECT_FALSE(system_responses.empty());
    EXPECT_LT(std::abs(system_responses.back() - reference_value), 5.0);
}

/**
 * @brief Интеграционный тест: ПИД-регулятор с нелинейной системой
 */
TEST(SystemIntegrationTest, PIDControlWithNonlinearSystem)
{
    std::vector<double> nonlinear_params = {0.65, 0.12, 0.25, 0.08};
    DynamicSystem nonlinear_system(nonlinear_params, 0.0);
    PIDRegulator pid_controller(1.8, 1.2, 0.3, 0.2);

    nonlinear_system.initializeState(0.0);
    pid_controller.clearState();

    std::vector<double> system_responses;
    const double target_value = 2.5;
    const int simulation_steps = 12;
    
    for (int step = 0; step < simulation_steps; ++step)
    {
        double current_state = system_responses.empty() ? 0.0 : system_responses.back();
        double control_action = pid_controller.computeControl(target_value, current_state);
        double system_output = nonlinear_system.evaluateNonlinear(control_action);
        system_responses.push_back(system_output);
    }

    // Проверка корректности работы системы
    EXPECT_EQ(system_responses.size(), simulation_steps);
    EXPECT_TRUE(std::isfinite(system_responses.back()));
    
    // Проверка, что система не ушла в бесконечность
    EXPECT_LT(std::abs(system_responses.back()), 100.0);
}

/**
 * @brief Тестирование устойчивости замкнутой системы
 */
TEST(SystemStabilityTest, ClosedLoopStabilityAnalysis)
{
    std::vector<double> stable_params = {0.5, 0.1, 0.0, 0.0};
    DynamicSystem stable_system(stable_params, 0.0);
    PIDRegulator stabilizing_controller(0.8, 2.0, 0.1, 0.5);

    stable_system.initializeState(0.0);
    stabilizing_controller.clearState();

    std::vector<double> transient_responses;
    const double setpoint = 4.0;
    const int stability_steps = 25;
    
    for (int iteration = 0; iteration < stability_steps; ++iteration)
    {
        double current_output = transient_responses.empty() ? 0.0 : transient_responses.back();
        double control_signal = stabilizing_controller.computeControl(setpoint, current_output);
        double system_response = stable_system.evaluateLinear(control_signal);
        transient_responses.push_back(system_response);
    }

    // Критерии устойчивости
    EXPECT_TRUE(std::isfinite(transient_responses.back()));
    
    // Проверка, что система не расходится
    for (double response : transient_responses) {
        EXPECT_LT(std::abs(response), 20.0);
    }
    
    // Проверка тенденции к установлению
    if (transient_responses.size() > 5) {
        double last_response = transient_responses.back();
        double average_last_five = 0.0;
        for (size_t i = transient_responses.size() - 5; i < transient_responses.size(); ++i) {
            average_last_five += transient_responses[i];
        }
        average_last_five /= 5.0;
        
        EXPECT_LT(std::abs(last_response - average_last_five), 0.5);
    }
}

/**
 * @brief Тестирование переходного процесса
 */
TEST(SystemResponseTest, TransientProcessCharacteristics)
{
    std::vector<double> system_params = {0.6, 0.3, 0.0, 0.0};
    DynamicSystem test_system(system_params, 0.0);
    PIDRegulator test_controller(1.2, 1.5, 0.0, 0.2);

    test_system.initializeState(0.0);
    test_controller.clearState();

    std::vector<double> step_responses;
    const double step_input = 5.0;
    
    // Моделирование переходного процесса
    for (int time_step = 0; time_step < 30; ++time_step)
    {
        double current_value = step_responses.empty() ? 0.0 : step_responses.back();
        double control = test_controller.computeControl(step_input, current_value);
        double response = test_system.evaluateLinear(control);
        step_responses.push_back(response);
    }

    // Проверка характеристик переходного процесса
    EXPECT_FALSE(step_responses.empty());
    
    // Поиск максимального перерегулирования
    double max_overshoot = 0.0;
    for (double response : step_responses) {
        if (response > step_input) {
            double overshoot = response - step_input;
            if (overshoot > max_overshoot) {
                max_overshoot = overshoot;
            }
        }
    }
    
    // Проверка, что перерегулирование не чрезмерное
    EXPECT_LT(max_overshoot, step_input * 2.0);
}

/**
 * @brief Основная функция запуска тестов
 */
int main(int argc, char **argv)
{
    // Инициализация Google Test
    testing::InitGoogleTest(&argc, argv);
    
    // Запуск всех тестов
    return RUN_ALL_TESTS();
}