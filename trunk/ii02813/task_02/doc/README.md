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
<p align="right">Группы ИИ-28</p>
<p align="right">Ковалевич Е.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).


## Код юнит-тестов [ test/test.cpp ]
```C++
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "../src/factory/factorylinearmodel.h"
#include "../src/factory/factorynonlinearmodel.h"

class LinearModelTest : public ::testing::Test {
protected:
    const double INITIAL_VALUE = 0;       // Начальное состояние системы
    const double INPUT_SIGNAL = 1;        // Входное воздействие
    const int SIMULATION_DURATION = 5;    // Временной интервал симуляции
};

TEST_F(LinearModelTest, SimulatesCorrectlyOverFiveTimeSteps) {
    // Создаем фабрику и модель линейной системы
    auto linearFactory = std::make_unique<FactoryLinearModel>();
    auto linearModel = linearFactory->getModel();
    
    // Выполняем моделирование
    std::vector<double> simulationResults = linearModel->simulate(
        INITIAL_VALUE, INPUT_SIGNAL, SIMULATION_DURATION);
    
    // Ожидаемые результаты для каждого временного шага
    std::vector<double> expectedValues = {
        0, 0.5, 0.75, 0.875, 0.9375, 0.96875
    };

    // Проверяем соответствие размеров результата
    ASSERT_EQ(simulationResults.size(), expectedValues.size());
    
    // Поэлементное сравнение с заданной точностью
    for (size_t iteration = 0; iteration < simulationResults.size(); ++iteration) {
        const double tolerance = 1e-5;
        EXPECT_NEAR(simulationResults[iteration], expectedValues[iteration], tolerance)
            << "Расхождение на шаге " << iteration;
    }
}

class NonlinearModelTest : public ::testing::Test {
protected:
    const double INITIAL_VALUE = 0;       
    const double INPUT_SIGNAL = 1;       
    const int SIMULATION_DURATION = 5;   
};

TEST_F(NonlinearModelTest, SimulatesCorrectlyOverFiveTimeSteps) {
    auto nonlinearFactory = std::make_unique<FactoryNonLinearModel>();
    auto nonlinearModel = nonlinearFactory->getModel();
    
    std::vector<double> simulationResults = nonlinearModel->simulate(
        INITIAL_VALUE, INPUT_SIGNAL, SIMULATION_DURATION);
    
    std::vector<double> expectedValues = {
        0, 0.499999, 0.989713, 1.29059, 1.15428, 0.698974
    };


    ASSERT_EQ(simulationResults.size(), expectedValues.size());
    
    for (size_t iteration = 0; iteration < simulationResults.size(); ++iteration) {
        const double tolerance = 1e-5;
        EXPECT_NEAR(simulationResults[iteration], expectedValues[iteration], tolerance)
            << "Расхождение на шаге " << iteration;
    }
}
```

## Результаты юнит-тестирования (GoogleTest)
![GoogleTest Output](img/gtest.png)

## Покрытие тестами (gcovr)
!['gcovr' Output](img/gcovr.png)

## Reviews
VL-lab-bit
<br>
![Review for VL-lab-bit:](img/VL-lab-bit.png)
<br>
RisomUV
<br>
![Review for RisomUV:](img/RisomUV.png)