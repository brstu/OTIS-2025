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
<p align="right">Литовкин Н.А.</p>
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


## Код тестов
```C++
#include <gtest/gtest.h>
#include "../src/functions.h"

TEST(TestLinearModel, WhenStepsIsFour)
{   
    const int steps = 4;
    double y_next = 0;
    double u = 1;
    std::vector<double> results;
    for (int i = 0; i < steps; i++) {
        y_next = linearModel(y_next, u);
        results.push_back(y_next);
    }

    std::vector<double> accepted_results
    { 0.5, 0.45, 0.455, 0.4545 };
    EXPECT_EQ(results.size(), accepted_results.size());
    for (int i = 0; i < results.size(); i++)
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2) << "Not equal at" << i;
    }
}

TEST(TestNonLinearModel, WhenStepsIsFour)
{   
    const int steps = 4;
    double y_next = 0;
    double u = 1;
    std::vector<double> results;
    for (int i = 0; i < steps; i++) {
        double y_pred = y_next;
        double u_pred = u;
        y_next = nonlinearModel(y_next, u, y_pred, u_pred);
        results.push_back(y_next);
    }

    std::vector<double> accepted_results
    {  0.136588, 0.113601, 0.118776, 0.117657 };
    EXPECT_EQ(results.size(), accepted_results.size());  
    for (int i = 0; i < results.size(); i++) 
    {
        EXPECT_NEAR(results[i], accepted_results[i], 1e-2) << "Not equal at" << i;
    }
}
```

## Результаты тестирования
![GoogleTest Output](img/gtest.png)

## Покрытие кода тестами
!['gcovr' Output](img/gcovr.png)

## Reviews
igor7123
![Review igor7123](img/igor7123.png)
v1tyokkk
![Review v1tyokkk](img/v1tyokkk.png)

Вывод: Научился писать модульные тесты для программы, разработанной в лабораторной работе №1.