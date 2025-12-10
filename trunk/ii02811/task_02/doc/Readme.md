<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Климахович К.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk/ii0xxyy/task_02/test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk/ii0xxyy/task_02/src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

```cpp
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/main.h"
#include <cmath>

struct NonLinearParams {
    double a, b, c, d;
};

TEST(LinearModel_ii02811, ComputesCorrectly) {
    double y = 2.3;
    double u = 3.7;
    double a = 1.5;
    double b = -0.8;
    double expected = a * y + b * u;
    EXPECT_NEAR(x(y, u, a, b), expected, 1e-9);
}

TEST(LinearModel_ii02811, ZeroCoefficientsReturnZero) {
    EXPECT_DOUBLE_EQ(x(5.1, 4.2, 0.0, 0.0), 0.0);
}

TEST(LinearModel_ii02811, HandlesNegativeInputs) {
    EXPECT_DOUBLE_EQ(x(-1.2, -2.3, 1.0, 2.0), -1.2 + (-2.3 * 2.0));
}

TEST(NonLinearModel_ii02811, ComputesExpectedValue) {
    double y = 1.0;
    double u = 0.5;
    double yx = 0.0;
    NonLinearParams p{2.0, 1.0, 0.6, 1.1};

    double expected = p.a * y - p.b * y * yx + p.c * u + p.d * sin(u);
    
    double result = x1(y, u, p.a, p.b, p.c, p.d, yx);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(NonLinearModel_ii02811, ZeroCoefficientsReturnZero) {
    double y = 2.4;
    double u = 1.2;
    double yx = 0.0;
    NonLinearParams p{0.0, 0.0, 0.0, 0.0};
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), 0.0);
}

TEST(NonLinearModel_ii02811, SinComponentOnlyWorks) {
    double y = 0.0;
    double u = M_PI / 4;
    double yx = 0.0;
    NonLinearParams p{0.0, 0.0, 0.0, 2.5};

    double result = x1(y, u, p.a, p.b, p.c, p.d, yx);
    double expected = 2.5 * sin(u);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(NonLinearModel_ii02811, OnlyLinearYComponent) {
    double y = 3.0;
    double u = 0.0;
    double yx = 0.0;
    NonLinearParams p{2.0, 0.0, 0.0, 0.0};
    
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), 2.0 * 3.0);
}

TEST(NonLinearModel_ii02811, OnlyQuadraticComponent) {
    double y = 3.0;
    double u = 0.0;
    double yx = 2.0; 
    NonLinearParams p{0.0, 1.0, 0.0, 0.0};
    
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), -6.0);
}

TEST(NonLinearModel_ii02811, OnlyLinearUComponent) {
    double y = 0.0;
    double u = 4.0;
    double yx = 0.0;
    NonLinearParams p{0.0, 0.0, 3.0, 0.0};
    
    EXPECT_DOUBLE_EQ(x1(y, u, p.a, p.b, p.c, p.d, yx), 3.0 * 4.0);
}

TEST(NonLinearModel_ii02811, CombinedComponents) {
    double y = 2.0;
    double u = 1.5;
    double yx = 3.0;
    NonLinearParams p{1.5, 0.5, 2.0, 1.0};
    
    double expected = 3.0 - 3.0 + 3.0 + sin(1.5);
    EXPECT_NEAR(x1(y, u, p.a, p.b, p.c, p.d, yx), expected, 1e-9);
}
```
## Результаты тестирования ##
![Результаты тестирования:](img/Снимок%20экрана%202025-12-02%20214308.png)
## Покрытие тестами ##
![Покрытие тестами:](img/Снимок%20экрана%202025-12-02%20212020.png)