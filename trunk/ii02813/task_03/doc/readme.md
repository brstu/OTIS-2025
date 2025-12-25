<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование системы автоматического управления с ПИД-регулятором для объекта теплового класса.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28/24</p>
<p align="right">Ковалевич Е.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

**Задание.**
1. Написать отчет по выполненной лабораторной работе №3 в .md формате (*readme.md*) и разместить его в следующем каталоге: **trunk\ii0xxyy\task_03\doc**.
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_03\src**.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4. Документировать исходный код программы с помощью комментариев в стиле **Doxygen**. Полученную документацию разместить в каталоге: **trunk\ii0xxyy\task_03\doc\html**. Настроить `GitHub Pages` для автоматической публикации документации из этого каталога.
5. Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием **Google Test**. Тесты разместить в каталоге: **trunk\ii0xxyy\task_03\test**.

На **C++** реализовать программу, моделирующую рассмотренный выше ПИД-регулятор.  В качестве объекта управления использовать математическую модель, полученную в предыдущей работе.
В отчете также привести графики для разных заданий температуры объекта, пояснить полученные результаты.


## Код программы
```C++
#include <iostream>
#include "models.h"
#include "pid.h"


int main()
{
    const double K01  = 0.06; 
    const double T01  = 20.0; 
    const double Td01 = 0.0; 
    const double T001 = 1.0;
    
    pid_coeffs coeffs(K01, T01, Td01, T001);
    pid PID(coeffs, 1, 2, 3);

    const double a01_lin = 0.8; 
    const double b01_lin = 0.1; 

    NonLinearCoeffs coeffs_nl;
    coeffs_nl.a01 = 0.8;  
    coeffs_nl.b01 = 0.0;  
    coeffs_nl.c01 = 0.1;  
    coeffs_nl.d01 = 0.05;

    double y01;
    double w01; 
    int n01;    

    std::cout << "Enter initial temperature -> ";
    std::cin >> y01;
    std::cout << "Enter target temperature -> ";
    std::cin >> w01;
    std::cout << "Enter number of steps -> ";
    std::cin >> n01;

    double e01; 
    double u01; 

    double y01_nl = y01;
    double y01_prev = 0;
    double u01_prev = 0;

    for (int i01 = 0; i01 < n01; i01++)
    {
        e01 = w01 - y01;              
        u01 = PID.process(e01);    

        y01 = linear(y01, u01, a01_lin, b01_lin); 

        y01_nl = non_linear(y01_nl, y01_prev, u01, u01_prev, coeffs_nl); 
        y01_prev = y01_nl;
        u01_prev = u01;

        std::cout << "Step " << i01 + 1 
                  << " - e = " << e01 
                  << ", u = " << u01
                  << ", y_lin = " << y01 
                  << ", y_nonlin = " << y01_nl 
                  << ";\n";
    }

    return 0;
}
```

## График работы программы
![result](images/graph.png)

## Ссылка на документацию
[https://tstepannovikov.github.io/OTIS-2025](https://tstepannovikov.github.io/OTIS-2025/)

## Код тестов
```C++
#define _USE_MATH_DEFINES
#include <gtest/gtest.h>
#include "../src/models.h"
#include "../src/pid.h"
#include <cmath>

TEST(LinearModelTest, BasicCase) {
    double y01 = 2.0;
    double u01 = 3.0;
    double a01 = 1.5;
    double b01 = -0.5;
    double expected01 = a01 * y01 + b01 * u01;

    EXPECT_DOUBLE_EQ(linear(y01, u01, a01, b01), expected01);
}

TEST(LinearModelTest, ZeroCoefficients) {
    EXPECT_DOUBLE_EQ(linear(5.0, 4.0, 0.0, 0.0), 0.0);
}

TEST(LinearModelTest, NegativeInputs) {
    EXPECT_DOUBLE_EQ(linear(-2.0, -3.0, 1.0, 2.0), -2.0 + (-3.0 * 2.0));
}

TEST(NonLinearModelTest, BasicCase) {
    double y01   = 1.0;
    double y01_p = 0.0;
    double u01   = 0.5;
    double u01_p = 0.2;
    NonLinearCoeffs coeffs{2.0, 1.0, 0.5, 1.0};
    double expected01 = coeffs.a01 * y01 - coeffs.b01 * y01_p * y01_p + coeffs.c01 * u01 + coeffs.d01 * std::sin(u01_p);

    EXPECT_DOUBLE_EQ(non_linear(y01, y01_p, u01, u01_p, coeffs), expected01);
}

TEST(NonLinearModelTest, ZeroCoefficients) {
    double y01   = 2.0;
    double y01_p = 1.0;
    double u01   = 1.0;
    double u01_p = 0.5;
    NonLinearCoeffs coeffs{0.0, 0.0, 0.0, 0.0};

    EXPECT_DOUBLE_EQ(non_linear(y01, y01_p, u01, u01_p, coeffs), 0.0);
}

TEST(NonLinearModelTest, SinusoidalEffect) {
    double y01   = 0.0;
    double y01_p = 0.0;
    double u01   = 0.0;
    double u01_p = M_PI / 2;
    NonLinearCoeffs coeffs{0.0, 0.0, 0.0, 2.0};

    EXPECT_DOUBLE_EQ(non_linear(y01, y01_p, u01, u01_p, coeffs), 2.0);
}

TEST(PidTest, Initialization) {
    pid_coeffs coeffs(2.0, 1.0, 0.5, 0.1);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double e01 = 1.0;
    double expected01 = PID.process(e);

    EXPECT_DOUBLE_EQ(expected01, 12.0);
}

TEST(PidTest, StateUpdate) {
    pid_coeffs coeffs(1.0, 1.0, 1.0, 1.0);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double u101 = PID.process(1.0);
    double u201 = PID.process(2.0);

    EXPECT_NE(u101, u201);
}

TEST(PidTest, ZeroCoefficients) {
    pid_coeffs coeffs(0.0, 1.0, 1.0, 1.0);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double result01 = PID.process(5.0);

    EXPECT_DOUBLE_EQ(result01, 0.0);
}

TEST(PidTest, MultipleSteps) {
    pid_coeffs coeffs(1.0, 2.0, 0.5, 0.1);
    pid PID(coeffs, 0.0, 0.0, 0.0);
    double u101 = PID.process(1.0);
    double u201 = PID.process(1.0);
    double u301 = PID.process(1.0);

    EXPECT_NE(u101, u201);
    EXPECT_NE(u201, u301);
}

```

## Результаты тестирования (GoogleTest)
![GTest](images/test.png)

