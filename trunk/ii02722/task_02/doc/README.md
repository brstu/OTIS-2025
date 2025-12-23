<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Туз Г.С.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk/ii02801/task_02/test**.  
3. Исходный код модифицированной программы разместить в каталоге: **trunk/ii02801/task_02/src**.  
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (например, с помощью [gcovr](https://gcovr.com/en/stable/)).  
5. Также необходимо отразить выполнение работы в общем [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке.

---

# Код юнит-тестов [ test/test.cpp ]

```cpp

#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "functions.h"

// Тестовый набор для линейного симулятора
class LinearSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        testInput = {5.0, 5.0, 5.0, 5.0};
    }
    std::vector<double> testInput;
};

// Тест на обработку пустого ввода
TEST_F(LinearSystemTest, EmptyInputReturnsEmptyResult) {
    std::vector<double> emptyInput;
    auto simulationResult = linearSystemSimulator(5, 10.0, emptyInput);
    EXPECT_TRUE(simulationResult.empty());
}

// Тест на обработку одного шага
TEST_F(LinearSystemTest, SingleIterationPreservesInitialState) {
    std::vector<double> minimalInput = {1.0};
    auto simulationResult = linearSystemSimulator(1, 10.0, minimalInput);
    
    ASSERT_EQ(simulationResult.size(), 1);
    EXPECT_DOUBLE_EQ(simulationResult[0], 10.0);
}

// Тест корректности вычислений
TEST_F(LinearSystemTest, ComputationsFollowDynamicEquation) {
    auto simulationResult = linearSystemSimulator(5, 10.0, testInput);
    
    ASSERT_EQ(simulationResult.size(), 5);
    EXPECT_NEAR(simulationResult[1], 0.9 * 10.0 + 0.1 * 5.0, 1e-6);
    EXPECT_NEAR(simulationResult[2], 0.9 * simulationResult[1] + 0.1 * 5.0, 1e-6);
}

// Тестовый набор для нелинейного симулятора
class NonlinearSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        testInput = {5.0, 5.0, 5.0};
    }
    std::vector<double> testInput;
};

// Тест на нулевое количество итераций
TEST_F(NonlinearSystemTest, ZeroIterationsYieldsEmptyVector) {
    auto simulationResult = nonlinearSystemSimulator(0, 10.0, testInput);
    EXPECT_TRUE(simulationResult.empty());
}

// Тест на единственную итерацию
TEST_F(NonlinearSystemTest, SingleIterationReturnsInitialValue) {
    auto simulationResult = nonlinearSystemSimulator(1, 10.0, testInput);
    
    ASSERT_EQ(simulationResult.size(), 1);
    EXPECT_DOUBLE_EQ(simulationResult[0], 10.0);
}

// Тест корректности нелинейных вычислений
TEST_F(NonlinearSystemTest, NonlinearDynamicsProduceCorrectValues) {
    auto simulationResult = nonlinearSystemSimulator(3, 10.0, testInput);
    
    ASSERT_EQ(simulationResult.size(), 3);
    EXPECT_NEAR(simulationResult[1], 0.9 * 10.0 + 0.1 * 5.0, 1e-6);
    
    double expectedSecondStep = 0.9 * simulationResult[1] - 
                               0.1 * std::pow(10.0, 2) + 
                               0.05 * 5.0 + 
                               0.02 * std::sin(5.0);
    EXPECT_NEAR(simulationResult[2], expectedSecondStep, 1e-6);
}

```