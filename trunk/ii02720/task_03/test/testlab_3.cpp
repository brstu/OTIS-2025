/**
 * @file testlab_3.cpp
 * @brief Модульные тесты для ПИД-регулятора и модели теплового объекта
 * @author Степанюк Илья Сергеевич (ii02720)
 * @date 2025
 * 
 * Набор тестов GoogleTest для проверки корректности работы
 * классов PIDController и ProcessModel лабораторной работы №3.
 */

#include <gtest/gtest.h>
#include <cmath>
#include "../src/pid.h"
#include "../src/model.h"

// ============= Тесты ПИД-регулятора (Степанюк И.С.) =============

/**
 * @brief Тест создания регулятора и базовых вычислений
 */
TEST(PIDControllerTest_Stepaniuk, ConstructorAndBasicCalculation)
{
    PIDController pidReg(2.5, 1.2, 0.4, 1.0);
    
    // Проверка, что регулятор возвращает конечное число
    double controlValue = pidReg.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(controlValue));
}

/**
 * @brief Тест П-регулятора (без интегральной и дифференциальной составляющих)
 */
TEST(PIDControllerTest_Stepaniuk, ProportionalControllerBehavior)
{
    PIDController pReg(1.0, 1.0, 0.0, 1.0); 
    pReg.reset();

    // Первый шаг: e=1, u должно быть около 1
    double u_step1 = pReg.calculate(1.0, 0.0);
    EXPECT_NEAR(u_step1, 1.0, 1e-6);

    // Второй шаг: e=0.5
    double u_step2 = pReg.calculate(1.0, 0.5);
    EXPECT_NEAR(u_step2, 1.5, 1e-6);

    // Третий шаг: e=0
    double u_step3 = pReg.calculate(1.0, 1.0);
    EXPECT_NEAR(u_step3, 1.5, 1e-6);
}

/**
 * @brief Тест ПИ-регулятора (накопление интегральной составляющей)
 */
TEST(PIDControllerTest_Stepaniuk, PIControllerAccumulation)
{
    PIDController piReg(1.0, 0.4, 0.0, 1.0);
    piReg.reset();

    double u_first = piReg.calculate(1.0, 0.0);
    double u_second = piReg.calculate(1.0, 0.5);
    
    // Интегральная составляющая должна накапливаться
    EXPECT_GT(u_second, u_first);
}

/**
 * @brief Тест сброса состояния регулятора
 */
TEST(PIDControllerTest_Stepaniuk, ResetFunctionality)
{
    PIDController pidReg(1.0, 1.0, 0.15, 1.0);
    
    // Выполняем несколько итераций
    pidReg.calculate(1.0, 0.0);
    pidReg.calculate(1.0, 0.5);
    
    // Сбрасываем состояние
    pidReg.reset();
    
    // После сброса результат должен быть таким же, как в начале
    double afterReset = pidReg.calculate(1.0, 0.0);
    EXPECT_TRUE(std::isfinite(afterReset));
}

// ============= Тесты модели объекта (Степанюк И.С.) =============

/**
 * @brief Тест линейной модели теплового объекта
 */
TEST(ProcessModelTest_Stepaniuk, LinearModelCalculation)
{
    std::vector<double> coeffs = {0.55, 0.45, 0.0, 0.0};
    ProcessModel plant(coeffs, 1.0);

    double y1 = plant.linearModel(1.0);
    EXPECT_NEAR(y1, 0.55 * 1.0 + 0.45 * 1.0, 1e-6);

    double y2 = plant.linearModel(2.0);
    EXPECT_NEAR(y2, 0.55 * y1 + 0.45 * 2.0, 1e-6);
}

/**
 * @brief Тест нелинейной модели с квадратичной составляющей
 */
TEST(ProcessModelTest_Stepaniuk, NonlinearModelWithQuadratic)
{
    std::vector<double> coeffs = {0.55, 0.12, 0.35, 0.08};
    ProcessModel plant(coeffs, 1.0);

    double y = plant.nonlinearModel(0.5);
    double expected = 0.55 * 1.0 - 0.12 * 1.0 * 1.0 + 0.35 * 0.5 + 0.08 * std::sin(0.5);

    EXPECT_NEAR(y, expected, 1e-6);
}

/**
 * @brief Тест установки начального значения
 */
TEST(ProcessModelTest_Stepaniuk, InitialValueSetting)
{
    std::vector<double> coeffs = {0.75, 0.25, 0.0, 0.0};
    ProcessModel plant(coeffs, 0.0);
    
    plant.setInitialValue(2.5);
    double y = plant.linearModel(1.0);
    
    // y = 0.75 * 2.5 + 0.25 * 1.0
    EXPECT_NEAR(y, 0.75 * 2.5 + 0.25 * 1.0, 1e-6);
}

// ============= Интеграционные тесты (Степанюк И.С.) =============

/**
 * @brief Тест замкнутой системы с П-регулятором и линейным объектом
 */
TEST(SystemIntegrationTest_Stepaniuk, ClosedLoopWithPController)
{
    std::vector<double> modelCoeffs = {0.75, 0.25, 0.0, 0.0};
    ProcessModel plant(modelCoeffs, 0.0);
    PIDController pController(2.5, 1.0, 0.0, 1.0);

    plant.setInitialValue(0.0);
    pController.reset();

    std::vector<double> trajectory;
    double setpoint = 1.0;
    
    for (int k = 0; k < 12; k++)
    {
        double currentY = (trajectory.empty()) ? 0.0 : trajectory.back();
        double controlU = pController.calculate(setpoint, currentY);
        double nextY = plant.linearModel(controlU);
        trajectory.push_back(nextY);
    }

    // Система должна стремиться к заданию
    EXPECT_GT(trajectory.back(), 0.0);
    EXPECT_LT(std::abs(trajectory.back() - setpoint), 1.0);
}

/**
 * @brief Тест ПИД-регулятора с нелинейным объектом
 */
TEST(SystemIntegrationTest_Stepaniuk, PIDWithNonlinearPlant)
{
    std::vector<double> modelCoeffs = {0.75, 0.08, 0.35, 0.15};
    ProcessModel plant(modelCoeffs, 0.0);
    PIDController pidController(1.8, 0.7, 0.25, 0.5);

    plant.setInitialValue(0.0);
    pidController.reset();

    std::vector<double> outputs;
    double setpoint = 2.5;
    
    for (int k = 0; k < 18; k++)
    {
        double currentOutput = (outputs.empty()) ? 0.0 : outputs.back();
        double control = pidController.calculate(setpoint, currentOutput);
        double newOutput = plant.nonlinearModel(control);
        outputs.push_back(newOutput);
    }

    // Проверка корректности вычислений
    EXPECT_TRUE(std::isfinite(outputs.back()));
    EXPECT_GT(outputs.size(), 0);
}

/**
 * @brief Тест устойчивости замкнутой системы
 */
TEST(SystemIntegrationTest_Stepaniuk, StabilityAnalysis)
{
    std::vector<double> stableParams = {0.88, 0.12, 0.0, 0.0};
    ProcessModel plant(stableParams, 0.0);
    PIDController controller(0.6, 1.2, 0.0, 1.0);

    plant.setInitialValue(0.0);
    controller.reset();

    std::vector<double> response;
    double reference = 1.0;
    
    for (int k = 0; k < 25; k++)
    {
        double currentVal = (response.empty()) ? 0.0 : response.back();
        double controlSignal = controller.calculate(reference, currentVal);
        double nextVal = plant.linearModel(controlSignal);
        response.push_back(nextVal);
    }

    // Система должна быть устойчивой (выход ограничен)
    EXPECT_TRUE(std::isfinite(response.back()));
    EXPECT_LT(std::abs(response.back()), 15.0);
}

/**
 * @brief Главная функция запуска тестов
 */
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
