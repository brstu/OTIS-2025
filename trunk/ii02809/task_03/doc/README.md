<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №3</p>
<p align="center">по дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “ПИД-регуляторы.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Заремская Е.П.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание

Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc.
2. Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4. Документировать исходный код программы с помощью комментариев в стиле Doxygen. Полученную документацию разместить в каталоге: trunk\ii0xxyy\task_03\doc\html. Настроить GitHub Pages для автоматической публикации документации из этого каталога.
5. Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием Google Test. Тесты разместить в каталоге: trunk\ii0xxyy\task_03\test.

# Выполнение задания

Код программы:

```
#include <iostream>
#include "functions.h"

int main() {
    double a, b, c, d;
    std::cout << "Enter model parameters a, b, c, d: ";
    std::cin >> a >> b >> c >> d;

    double K, Ti, Td, To;
    std::cout << "Enter PID parameters K, Ti, Td, To: ";
    std::cin >> K >> Ti >> Td >> To;

    double w;
    std::cout << "Enter desired value w: ";
    std::cin >> w;

    int model_type;
    std::cout << "Enter model type (1: linear, 2: nonlinear): ";
    std::cin >> model_type;

    int num_steps;
    std::cout << "Enter number of steps: ";
    std::cin >> num_steps;

    double y = 0.0;

    PID pid(K, Ti, Td, To);

    std::cout << "step,y,u,e" << std::endl;

    for (int k = 0; k < num_steps; ++k) {
        double e = w - y;
        double u = pid.compute(e);
        if (model_type == 1) {
            y = linear(y, u, a, b);
        } else {
            y = nonlinear(y, u, a, b, c, d);
        }
        std::cout << k << "," << y << "," << u << "," << e << std::endl;
    }

    return 0;
}

```

Результаты тестов:

![[image/covr1.png]]

![[image/covr2.png]]

![[image/google.png]]

### Вид документации Doxygen

![[image/doxygen.png]]
