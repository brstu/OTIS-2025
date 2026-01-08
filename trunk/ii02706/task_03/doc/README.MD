<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа N3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Гурин М.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

<hr>


# Выполнение задания #

Код тестов:
```
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "../src/functions.h"

using namespace std;

TEST(TestLinear, WhenStepsAreFive)
{   
    const int n = 5;    // Simulation time steps

    vector<double> accepted_results
    { 0.36, 0.096, 0.0696, 0.06696, 0.066696 };
    double y = 3;
    for (int i = 0; i < n; i++)
	{
        liner_funcnt(y);
        EXPECT_NEAR(y, accepted_results[i], 1e-5)
            << "Mismatch at index " << i;
	}
}
TEST(TestNonLinear, WhenStepsAreFive)
{   
    const int n = 5;    // Simulation time steps

    vector<double> accepted_results
    { 0.538208, -1.47842, 0.0619846, -0.163186, 0.250673 };
    double y = 3;
    double y_previous;
	bool second_iteration = true;
    for (int i = 0; i < n; i++)
	{
        nonliner_funct(y, y_previous, second_iteration);
        EXPECT_NEAR(y, accepted_results[i], 1e-5)
            << "[Mismatch at index]: " << i;
	}
}

TEST(TestPIDRegulatorUsingNonLinearModel, WhenStepsIsFive)
 {
    unsigned int step = 5;
    double w = 100;
    std::vector<double> results = simulatePIDRegulatorByNonLinearModel(w, step);

    std::vector<double> accepted_results
    { 7.15507, 13.7002, -5.47014, -66.113};
    EXPECT_EQ(results.size(), accepted_results.size());  
    for (int i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2) << "Not equal at" << i;
    }
} 

``` 

## GoogleTest Results

![GoogleTest](img/googletest.png)

## gcovr

![gcovr](img/gcovr.png)



