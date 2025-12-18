#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

// Тест 1: Инициализация модели
TEST(ModelTest, Initialization) {
    Model model;
    EXPECT_DOUBLE_EQ(model.getLinearOutput(), 23.0);
    EXPECT_DOUBLE_EQ(model.getNonlinearOutput(), 23.0);
    EXPECT_DOUBLE_EQ(model.getPrevNonlinearOutput(), 23.0);
}

// Тест 2: Линейная модель с известными параметрами
TEST(ModelTest, LinearModelCalculation) {
    Model model(0.95, 0.002, 0.05, 0.1, 23.0);
    
    double result = model.calculateLinear(10.0);
    double expected = 0.95 * 23.0 + 0.002 * 10.0;
    
    EXPECT_NEAR(result, expected, 1e-10);
}

// Тест 3: Несколько итераций линейной модели
TEST(ModelTest, MultipleLinearCalculations) {
    Model model(0.95, 0.002, 0.05, 0.1, 23.0);
    
    double inputs[] = {10, 15, 20};
    double expected[] = {
        0.95 * 23.0 + 0.002 * 10.0,
        0.95 * (0.95 * 23.0 + 0.002 * 10.0) + 0.002 * 15.0,
        0.95 * (0.95 * (0.95 * 23.0 + 0.002 * 10.0) + 0.002 * 15.0) + 0.002 * 20.0
    };
    
    for (int i = 0; i < 3; i++) {
        double result = model.calculateLinear(inputs[i]);
        EXPECT_NEAR(result, expected[i], 1e-10);
    }
}

// Тест 4: Нелинейная модель (первый шаг)
TEST(ModelTest, NonlinearModelFirstStep) {
    Model model(0.95, 0.002, 0.05, 0.1, 23.0);
    
    double result = model.calculateNonlinear(10.0);
    double no = 0.95 * 23.0;
    double ss = 0.002 * 23.0 * 23.0;
    double co = 0.05 * 10.0;
    double si = 0.1 * sin(0.0);  // u_prev = 0
    
    double expected = no - ss + co + si;
    
    EXPECT_NEAR(result, expected, 1e-10);
}

// Тест 5: Нелинейная модель (второй шаг)
TEST(ModelTest, NonlinearModelSecondStep) {
    Model model(0.95, 0.002, 0.05, 0.1, 23.0);
    
    // Первый шаг
    model.calculateNonlinear(10.0);
    double first_result = model.getNonlinearOutput();
    
    // Второй шаг
    double result = model.calculateNonlinear(15.0);
    
    double no = 0.95 * first_result;
    double ss = 0.002 * 23.0 * 23.0;  // y_nonlinear_prev из первого шага
    double co = 0.05 * 15.0;
    double si = 0.1 * sin(10.0);
    
    double expected = no - ss + co + si;
    
    EXPECT_NEAR(result, expected, 1e-10);
}

// Тест 6: Сброс модели
TEST(ModelTest, ResetFunction) {
    Model model;
    
    // Выполним несколько вычислений
    model.calculateLinear(10.0);
    model.calculateNonlinear(15.0);
    
    // Сбросим
    model.reset(23.0);
    
    EXPECT_DOUBLE_EQ(model.getLinearOutput(), 23.0);
    EXPECT_DOUBLE_EQ(model.getNonlinearOutput(), 23.0);
    EXPECT_DOUBLE_EQ(model.getPrevNonlinearOutput(), 23.0);
}

// Тест 7: Установка начальных условий
TEST(ModelTest, SetInitialConditions) {
    Model model;
    
    model.setInitialConditions(10.0, 20.0);
    
    EXPECT_DOUBLE_EQ(model.getLinearOutput(), 10.0);
    EXPECT_DOUBLE_EQ(model.getNonlinearOutput(), 20.0);
    EXPECT_DOUBLE_EQ(model.getPrevNonlinearOutput(), 20.0);
}

// Тест 8: Проверка граничных значений (нулевые коэффициенты)
TEST(ModelTest, ZeroCoefficients) {
    Model model(0.0, 0.0, 0.0, 0.0, 100.0);
    
    double linear_result = model.calculateLinear(50.0);
    EXPECT_DOUBLE_EQ(linear_result, 0.0);  // 0 * 100 + 0 * 50 = 0
    
    model.reset(100.0);
    double nonlinear_result = model.calculateNonlinear(50.0);
    EXPECT_DOUBLE_EQ(nonlinear_result, 0.0);  // 0*100 - 0*100*100 + 0*50 + 0*sin(0) = 0
}

// Тест 9: Проверка работы синуса
TEST(ModelTest, SinusComponent) {
    Model model(0.0, 0.0, 0.0, 0.5, 0.0);
    
    // Устанавливаем предыдущее значение u
    model.calculateNonlinear(3.14159); // u = π, sin(π) ≈ 0
    
    // Следующий шаг должен использовать sin(π)
    model.calculateNonlinear(0.0);
    
    // Так как все коэффициенты кроме d нулевые, результат должен быть d * sin(π) ≈ 0
    double result = model.getNonlinearOutput();
    EXPECT_NEAR(result, 0.0, 1e-10);
}

// Тест 10: Последовательность вычислений
TEST(ModelTest, SequenceOfOperations) {
    Model model;
    
    double u[] = {10, 15, 20, 25};
    double linear_expected[] = {
        0.95*23.0 + 0.002*10.0,
        0.0, // будет вычислено
        0.0, // будет вычислено
        0.0  // будет вычислено
    };
    
    // Вычисляем ожидаемые значения
    for (int i = 1; i < 4; i++) {
        linear_expected[i] = 0.95 * linear_expected[i-1] + 0.002 * u[i];
    }
    
    // Выполняем расчеты
    for (int i = 0; i < 4; i++) {
        double result = model.calculateLinear(u[i]);
        EXPECT_NEAR(result, linear_expected[i], 1e-10);
    }
}

int main(int argc, char **argv) {
    std::cout << "==========================================" << std::endl;
    std::cout << "Google Test для лабораторной работы №2" << std::endl;
    std::cout << "Модель линейной и нелинейной системы" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}