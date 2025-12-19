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
<p align="right">Господарик Я.Р.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk/ii02821/task_02/test**.  
3. Исходный код модифицированной программы разместить в каталоге: **trunk/ii02821/task_02/src**.  
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (например, с помощью [gcovr](https://gcovr.com/en/stable/)).  
5. Также необходимо отразить выполнение работы в общем [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке.

---

# Код юнит-тестов [ test/test.cpp ]

```cpp
#include <gtest/gtest.h>
#include "../src/models.hpp" 
#include <cmath>


TEST(LinearModelTest, BasicCalculation) {
    double result = linear_model(10.0, 10.0, 0.5, 0.5);
    EXPECT_DOUBLE_EQ(result, 10.0);
}

TEST(LinearModelTest, ZeroInputs) {
    double result = linear_model(0.0, 0.0, 0.5, 0.5);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(LinearModelTest, NegativeCoefficients) {
    double result = linear_model(10.0, 10.0, -1.0, 1.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}


TEST(NonlinearModelTest, BasicCalculation) {
    double y_curr = 10.0;
    double y_prev = 5.0;  
    double u = 2.0;
    double u_prev = 0.0;
    
    double a = 1.0;
    double b = 0.1;
    double c = 0.5;
    double d = 1.0;

    double result = nonlinear_model(y_curr, y_prev, u, u_prev, a, b, c, d);
    EXPECT_DOUBLE_EQ(result, 8.5);
}

TEST(NonlinearModelTest, SinusImpact) {
    double u_prev = 1.57079632679; 
    double d = 10.0;
    double result = nonlinear_model(0, 0, 0, u_prev, 0, 0, 0, d);
    
    EXPECT_NEAR(result, 10.0, 0.0001);
}
```
## Результаты юнит-тестирования (GoogleTest)
```txt
[==========] Running 5 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from LinearModelTest
[ RUN      ] LinearModelTest.BasicCalculation
[       OK ] LinearModelTest.BasicCalculation (0 ms)
[ RUN      ] LinearModelTest.ZeroInputs
[       OK ] LinearModelTest.ZeroInputs (0 ms)
[ RUN      ] LinearModelTest.NegativeCoefficients
[       OK ] LinearModelTest.NegativeCoefficients (0 ms)
[----------] 3 tests from LinearModelTest (14 ms total)

[----------] 2 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.BasicCalculation
[       OK ] NonlinearModelTest.BasicCalculation (0 ms)
[ RUN      ] NonlinearModelTest.SinusImpact
[       OK ] NonlinearModelTest.SinusImpact (0 ms)
[----------] 2 tests from NonlinearModelTest (10 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 2 test suites ran. (32 ms total)
[  PASSED  ] 5 tests.

``## Покрытие тестами (OpenCppCoverage)
```txt
В результате проверки с помощью OpenCppCoverage, процент покрытия тестов - 100%.