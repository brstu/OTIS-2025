/**
 * @file    test.cpp
 * @brief   Тесты для классов PID и Model
 * @details Модульные тесты, использующие Google Test framework
 *          для проверки корректности работы ПИД-регулятора и моделей.
 * @author  Vladimir
 * @date    2025-12-09
 * @version 1.0
 */

#include <gtest/gtest.h>
#include "pid.h"
#include "model.h"
#include <cmath>

/**
 * @defgroup TestsGroup Группа тестов
 * @brief Все модульные тесты проекта
 */

/**
 * @ingroup TestsGroup
 * @class PIDTest
 * @brief Тесты для класса PID
 * 
 * Набор тестов для проверки корректности работы ПИД-регулятора:
 * - Инициализация параметров
 * - Ограничение выходного сигнала
 * - Корректность расчетов
 */
class PIDTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Код инициализации перед каждым тестом
    }
    
    void TearDown() override {
        // Код очистки после каждого теста
    }
};

/**
 * @test PIDTest.ConstructorParameters
 * @brief Тест конструктора и получения параметров
 * 
 * Проверяет, что параметры ПИД-регулятора корректно сохраняются
 * и могут быть получены через метод getParameters().
 */
TEST(PIDTest, ConstructorParameters) {
    // Создание ПИД-регулятора с заданными параметрами
    PID pid(1.0, 2.0, 0.5, 1.0);

    double K;   ///< Коэффициент усиления
    double Ti;  ///< Постоянная времени интегрирования
    double Td;  ///< Постоянная времени дифференцирования
    
    // Получение параметров регулятора
    pid.getParameters(K, Ti, Td);

    // Проверка корректности параметров
    EXPECT_DOUBLE_EQ(K, 1.0);   ///< K должен быть равен 1.0
    EXPECT_DOUBLE_EQ(Ti, 2.0);  ///< Ti должен быть равен 2.0
    EXPECT_DOUBLE_EQ(Td, 0.5);  ///< Td должен быть равен 0.5
}

/**
 * @test PIDTest.OutputSaturation
 * @brief Тест ограничения выходного сигнала
 * 
 * Проверяет, что выходной сигнал ПИД-регулятора ограничен
 * диапазоном [0, 100] независимо от величины ошибки.
 */
TEST(PIDTest, OutputSaturation) {
    // Создание ПИД-регулятора с большим коэффициентом усиления
    PID pid(100.0, 0.1, 10.0, 1.0);

    // Расчет управляющего воздействия для большой ошибки
    double u = pid.calculate(1000.0, 0.0);

    // Проверка ограничения выходного сигнала
    EXPECT_GE(u, 0.0);    ///< Выход должен быть >= 0
    EXPECT_LE(u, 100.0);  ///< Выход должен быть <= 100
}

/**
 * @ingroup TestsGroup
 * @class ModelTest
 * @brief Тесты для класса Model
 * 
 * Набор тестов для проверки корректности работы моделей:
 * - Линейная модель
 * - Корректность расчетов
 * - Инициализация состояния
 */
class ModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Код инициализации перед каждым тестом
    }
    
    void TearDown() override {
        // Код очистки после каждого теста
    }
};

/**
 * @test ModelTest.LinearModelCorrect
 * @brief Тест корректности линейной модели
 * 
 * Проверяет, что линейная модель правильно вычисляет выход
 * по разностному уравнению: y[k] = a*y[k-1] + b*u[k]
 */
TEST(ModelTest, LinearModelCorrect) {
    // Создание линейной модели с заданными коэффициентами
    // a = 0.2, b = 0.3, c и d не используются в линейной модели
    Model model(0.2, 0.3, 0.0, 0.0);
    
    // Инициализация начальных условий
    // y[k-2] = 10.0, y[k-1] = 10.0
    model.init(10.0, 10.0, 0.0, 0.0);

    // Расчет выхода для входного сигнала u = 10.0
    double y = model.linearModel(10.0);
    
    // Ожидаемое значение: 0.2*10.0 + 0.3*10.0 = 5.0
    double expected = 0.2 * 10.0 + 0.3 * 10.0;
    
    // Проверка с допуском 1e-6
    EXPECT_NEAR(y, expected, 1e-6);
}

/**
 * @test ModelTest.NonlinearModelBounds
 * @brief Тест ограничений нелинейной модели
 * 
 * Проверяет, что нелинейная модель корректно ограничивает
 * выходные значения в заданном диапазоне.
 */
TEST(ModelTest, NonlinearModelBounds) {
    // Создание нелинейной модели
    Model model(10.0, 10.0, 10.0, 10.0);
    
    // Инициализация
    model.init(0.0, 0.0, 0.0, 0.0);
    
    // Расчет выхода с большим входным сигналом
    double y = model.nonlinearModel(1000.0);
    
    // Проверка ограничения выходного значения
    EXPECT_LE(y, 1000.0);   ///< Выход должен быть <= 1000.0
    EXPECT_GE(y, -1000.0);  ///< Выход должен быть >= -1000.0
}

/**
 * @test ModelTest.GetSetCurrentValue
 * @brief Тест методов получения и установки текущего значения
 * 
 * Проверяет корректность работы методов getCurrentValue() и setCurrentValue().
 */
TEST(ModelTest, GetSetCurrentValue) {
    Model model(0.2, 0.3, 0.4, 0.5);
    model.init(10.0, 20.0, 0.0, 0.0);
    
    // Проверка начального значения
    EXPECT_DOUBLE_EQ(model.getCurrentValue(), 20.0);
    
    // Установка нового значения
    model.setCurrentValue(30.0);
    
    // Проверка установленного значения
    EXPECT_DOUBLE_EQ(model.getCurrentValue(), 30.0);
}

/**
 * @brief Основная функция запуска тестов
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения тестовой программы
 * 
 * Функция инициализирует и запускает все тесты Google Test.
 */
int main(int argc, char **argv) {
    // Инициализация Google Test framework
    ::testing::InitGoogleTest(&argc, argv);
    
    // Запуск всех тестов
    return RUN_ALL_TESTS();
}