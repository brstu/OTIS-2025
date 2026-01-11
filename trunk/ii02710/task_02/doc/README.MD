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
<p align="right">Куцко Р.Р.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk/ii0xxyy/task_02/test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk/ii0xxyy/task_02/src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

## Код юнит-тестов [ test/test.cpp ]
#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

// Первый тест: проверка линейной системы
TEST(SystemTests, LinearSystemTest) {
    // Тест 1: Базовый расчет
    EXPECT_NEAR(linearStep(0.4, 0.3, 0.5, 0.0), 0.15, 1e-6);
    
    // Тест 2: Проверка нескольких итераций (как в main)
    double y = 0.0;
    y = linearStep(0.4, 0.3, 0.5, y); // y[1]
    EXPECT_NEAR(y, 0.15, 1e-6);
    
    y = linearStep(0.4, 0.3, 0.5, y); // y[2]
    EXPECT_NEAR(y, 0.21, 1e-6);
    
    y = linearStep(0.4, 0.3, 0.5, y); // y[3]
    EXPECT_NEAR(y, 0.234, 1e-6);
    
    // Тест 3: Проверка с нулевым входом
    EXPECT_NEAR(linearStep(0.4, 0.3, 0.0, 1.0), 0.4, 1e-6);
}

// Второй тест: проверка нелинейной системы
TEST(SystemTests, NonlinearSystemTest) {
    // Тест 1: Первый шаг из main
    double result = nonlinearStep(0.5, 0.2, 0.1, 0.3, 26.0, 25.0, 2.0, 1.0);
    double expected = 0.5 * 26.0 - 0.2 * (25.0 * 25.0) + 0.1 * 2.0 + 0.3 * std::sin(1.0);
    EXPECT_NEAR(result, expected, 1e-6);
    
    // Тест 2: Проверка нескольких итераций
    double y_prev = 25.0;
    double y_curr = 26.0;
    double u_prev = 1.0;
    double u_curr = 2.0;
    const double u_offset = 0.3;
    
    // Первая итерация
    double y_next = nonlinearStep(0.5, 0.2, 0.1, 0.3, y_curr, y_prev, u_curr, u_prev);
    
    // Обновление для второй итерации
    y_prev = y_curr;
    y_curr = y_next;
    u_prev = u_curr;
    u_curr += u_offset;
    
    // Вторая итерация
    y_next = nonlinearStep(0.5, 0.2, 0.1, 0.3, y_curr, y_prev, u_curr, u_prev);
    // Проверяем, что результат является числом (не NaN и не бесконечным)
    EXPECT_TRUE(std::isfinite(y_next));
    
    // Тест 3: Проверка граничного случая
    EXPECT_NEAR(nonlinearStep(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), 0.0, 1e-6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```
## Результаты юнит-тестирования (GoogleTest)
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from SystemTests
[ RUN      ] SystemTests.LinearSystemTest
[       OK ] SystemTests.LinearSystemTest (0 ms)
[ RUN      ] SystemTests.NonlinearSystemTest
[       OK ] SystemTests.NonlinearSystemTest (0 ms)
[----------] 2 tests from SystemTests (2 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (7 ms total)
[  PASSED  ] 2 tests.
PS D:\OTIS-2025\trunk\ii02710\task_02\build\test> 
## gtest coverage 
GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/model.cpp                                  4       4   100%
test/test.cpp                                 38      38   100%
------------------------------------------------------------------------------
TOTAL                                         42      42   100%
------------------------------------------------------------------------------
PS D:\OTIS-2025\trunk\ii02710\task_02> 