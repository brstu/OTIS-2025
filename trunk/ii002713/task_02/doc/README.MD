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
<p align="right">Лыщенко К.В.</p>
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
```C++
#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// Тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 0.15, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(Linear(0.2, 0.4, 2.0, 1.0), 1.0, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0); // u, uPrev, y, yPrev
    double expected = p.c * 0.15 + p.d * std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2); // u, uPrev, y, yPrev
    double expected = 0.5 * 0.5 - 0.2 * (0.2 * 0.2) + 0.3 * 0.4 + 0.1 * std::sin(0.3);
    EXPECT_NEAR(result, expected, 1e-6);
}

```
## Результаты юнит-тестирования (GoogleTest)
[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from LinearModelTest
[ RUN      ] LinearModelTest.BaseCase
[       OK ] LinearModelTest.BaseCase (0 ms)
[ RUN      ] LinearModelTest.WithNonZeroY
[       OK ] LinearModelTest.WithNonZeroY (0 ms)
[----------] 2 tests from LinearModelTest (26 ms total)

[----------] 2 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.BaseCase
[       OK ] NonlinearModelTest.BaseCase (0 ms)
[ RUN      ] NonlinearModelTest.WithPreviousValues
[       OK ] NonlinearModelTest.WithPreviousValues (0 ms)
[----------] 2 tests from NonlinearModelTest (33 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (116 ms total)
[  PASSED  ] 4 tests.

## Покрытие тестами (gcovr)
src/build/_deps/googletest-src/googletest/src/gtest_main.cc
                                               4       4   100%
src/model.cpp                                 25      25   100%
src/task_02.cpp                               11      11   100%
test/test.cpp                                 30      30   100%
------------------------------------------------------------------------------
TOTAL                                       6381    1374    21%
------------------------------------------------------------------------------

## Сломанные тесты
```C++
#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

// Тесты для линейной модели
TEST(LinearModelTest, BaseCase) {
    EXPECT_NEAR(Linear(0.1, 0.3, 0.5, 0.0), 999.0, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(Linear(0.2, 0.4, 2.0, 1.0), -123.0, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, BaseCase) {
    NonlinearParams p{0.7, 0.9, 0.11, 0.13};
    double result = Nonlinear(p, 0.15, 0.0, 0.0, 0.0);
    double expected = 0.0;
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams p{0.5, 0.2, 0.3, 0.1};
    double result = Nonlinear(p, 0.4, 0.3, 0.5, 0.2);
    double expected = .0;
    EXPECT_NEAR(result, expected, 1e-6);
}
```
## Объяснение
1. Удалил папку build.
2. С помощью команды `cmake -S ./ -B build -G "MinGW Makefiles"` сконфигурировал проект.
3. С помощью команды `cmake --build build`  собрал проект (получил два .exe файла).
4. Перешел в папку build.
5. С помощью команды `.\runTests_ii002713.exe` запустил тесты.

## Результат
[==========] Running 4 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from LinearModelTest
[ RUN      ] LinearModelTest.BaseCase
C:\Users\kvimi\OTIS-2025\trunk\ii002713\task_02\test\test.cpp:7: Failure
The difference between Linear(0.1, 0.3, 0.5, 0.0) and 999.0 is 998.85000000000002, which exceeds 1e-6, where
Linear(0.1, 0.3, 0.5, 0.0) evaluates to 0.14999999999999999,
999.0 evaluates to 999, and
1e-6 evaluates to 9.9999999999999995e-07.

[  FAILED  ] LinearModelTest.BaseCase (7 ms)
[ RUN      ] LinearModelTest.WithNonZeroY
C:\Users\kvimi\OTIS-2025\trunk\ii002713\task_02\test\test.cpp:11: Failure
The difference between Linear(0.2, 0.4, 2.0, 1.0) and -123.0 is 124, which exceeds 1e-6, where
Linear(0.2, 0.4, 2.0, 1.0) evaluates to 1,
-123.0 evaluates to -123, and
1e-6 evaluates to 9.9999999999999995e-07.

[  FAILED  ] LinearModelTest.WithNonZeroY (7 ms)
[----------] 2 tests from LinearModelTest (19 ms total)

[----------] 2 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.BaseCase
C:\Users\kvimi\OTIS-2025\trunk\ii002713\task_02\test\test.cpp:19: Failure
The difference between result and expected is 0.016500000000000001, which exceeds 1e-6, where
result evaluates to 0.016500000000000001,
expected evaluates to 0, and
1e-6 evaluates to 9.9999999999999995e-07.

[  FAILED  ] NonlinearModelTest.BaseCase (8 ms)
[ RUN      ] NonlinearModelTest.WithPreviousValues
C:\Users\kvimi\OTIS-2025\trunk\ii002713\task_02\test\test.cpp:26: Failure
The difference between result and expected is 1111111110.608448, which exceeds 1e-6, where
result evaluates to 0.39155202066613393,
expected evaluates to 1111111111, and
1e-6 evaluates to 9.9999999999999995e-07.

[  FAILED  ] NonlinearModelTest.WithPreviousValues (7 ms)
[----------] 2 tests from NonlinearModelTest (20 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 2 test suites ran. (50 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 4 tests, listed below:
[  FAILED  ] LinearModelTest.BaseCase
[  FAILED  ] LinearModelTest.WithNonZeroY
[  FAILED  ] NonlinearModelTest.BaseCase
[  FAILED  ] NonlinearModelTest.WithPreviousValues

 4 FAILED TESTS

## Причины почему не получалось
1. Не сконфигурировал проект командой `cmake -S ./ -B build -G "MinGW Makefiles"`.
2. Вводил неправильную команду сборки проекта `cmake --build`, вместо правильной `cmake --build build`.
3. Вводил неправильную команду запуска тестов `.\runTests.exe`, вместо правильной `.\runTests_ii002713.exe`.