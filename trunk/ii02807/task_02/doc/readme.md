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
<p align="right">Деркач Е.В.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание

Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

## Исходный код

### Файл: `trunk/ii02807/task_02/src/model.h`

```cpp
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <cmath>
#include <stdexcept>

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
    double u;
    double uPrev;
    double y;
    double yPrev;
};

double nextLinear(double a, double b, double u, double y);
void simulateLinear(double a, double b, double u, int steps);
double nextNonlinear(const NonlinearParams& p);
void simulateNonlinear(double a, double b, double c, double d, double u, int steps);

#endif // MODEL_H
```

### Файл: `trunk/ii02807/task_02/src/model.cpp`

```cpp
#include "model.h"

double nextLinear(double a, double b, double u, double y)
{
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps)
{
    if (steps <= 0) {
        throw std::invalid_argument("Number of steps must be positive");
    }

    std::cout << "Линейная модель" << std::endl;
    double y_val = 0.0;
    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << y_val << std::endl;
        y_val = nextLinear(a, b, u, y_val);
    }
}

double nextNonlinear(const NonlinearParams& p)
{
    return p.a * p.y - p.b * (p.yPrev * p.yPrev) + p.c * p.u + p.d * sin(p.uPrev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps)
{
    if (steps <= 0) {
        throw std::invalid_argument("Number of steps must be positive");
    }

    std::cout << "Нелинейная модель" << std::endl;

    NonlinearParams p;
    p.a = a;
    p.b = b;
    p.c = c;
    p.d = d;
    p.u = u;
    p.uPrev = 0.0;
    p.y = 0.0;
    p.yPrev = 0.0;

    for (int i = 0; i < steps; i++)
    {
        std::cout << "t = " << i << ", y = " << p.y << std::endl;

        double yNext = nextNonlinear(p);

        p.yPrev = p.y;
        p.y = yNext;
        p.uPrev = p.u;
    }
}
```

### Файл: `trunk/ii02807/task_02/src/main.cpp`

```cpp
#include "model.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "RU");

    try
    {
        std::locale rus_locale("ru_RU.UTF-8");
        std::cout.imbue(rus_locale);
    }
    catch (const std::runtime_error&)
    {
        std::cerr << "Russian locale ru_RU.UTF-8 not available, using default locale." << std::endl;
    }

    try {
        double a1 = 0.3;
        double b1 = 0.3;
        double u1 = 0.9;
        int n1 = 10;
        simulateLinear(a1, b1, u1, n1);

        std::cout << std::endl;

        double a2 = 0.1;
        double b2 = 0.2;
        double c2 = 0.4;
        double d2 = 0.2;
        double u2 = 0.8;
        int n2 = 10;
        simulateNonlinear(a2, b2, c2, d2, u2, n2);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

### Файл: `trunk/ii02807/task_02/src/CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.15)
project(OtisTask02)

set(CMAKE_CXX_STANDARD 17)

# Основная программа
add_executable(simulation_main main.cpp model.cpp)

# Настройка для тестов
enable_testing()

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Тестовый исполняемый файл
add_executable(
  unit_tests
  ../test/test_model.cpp
  model.cpp
)

target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  unit_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
```

### Файл: `trunk/ii02807/task_02/test/test_model.cpp`

```cpp
#include "../src/model.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(LinearModelTest, NextLinearBasicCalculation) {
    double result = nextLinear(0.5, 0.5, 1.0, 2.0);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST(LinearModelTest, NextLinearZeroInput) {
    double result = nextLinear(0.3, 0.7, 0.0, 5.0);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST(LinearModelTest, NextLinearBothZero) {
    double result = nextLinear(0.2, 0.8, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, NextNonlinearBasicCalculation) {
    NonlinearParams p;
    p.a = 0.1; p.b = 0.2; p.c = 0.3; p.d = 0.4;
    p.u = 1.0; p.uPrev = 0.5; p.y = 2.0; p.yPrev = 1.0;

    double result = nextNonlinear(p);
    double expected = 0.1*2.0 - 0.2*(1.0*1.0) + 0.3*1.0 + 0.4*sin(0.5);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, NextNonlinearAllZero) {
    NonlinearParams p;
    p.a = 0.0; p.b = 0.0; p.c = 0.0; p.d = 0.0;
    p.u = 0.0; p.uPrev = 0.0; p.y = 0.0; p.yPrev = 0.0;

    double result = nextNonlinear(p);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, NextNonlinearOnlyLinearPart) {
    NonlinearParams p;
    p.a = 0.5; p.b = 0.0; p.c = 0.5; p.d = 0.0;
    p.u = 2.0; p.uPrev = 0.0; p.y = 3.0; p.yPrev = 0.0;

    double result = nextNonlinear(p);
    EXPECT_DOUBLE_EQ(result, 2.5);
}
```
Запуск основной программы:
.\build\trunk\ii02807\task_02\src\Debug\simulation_main.exe

Результат программы:
![Программа](img/Снимок экрана 2025-11-07 195817.png) 


Запуск тестов:
.\build\trunk\ii02807\task_02\src\Debug\unit_tests.exe

Результат выполнения тестов:
![Тесты](img/Снимок экрана 2025-11-07 195859.png) 
 

Анализ покрытия кода:
![Покрытие кода](img/Снимок экрана 2025-11-07 200502.png) 

Вывод:
В ходе лабораторной работы успешно разработаны модульные тесты для программы. Все 6 тестов проходят успешно, что подтверждает корректность работы программы.

