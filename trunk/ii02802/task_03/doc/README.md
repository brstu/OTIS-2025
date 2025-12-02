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
<p align="right">Асташёнок Д.С.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>


<hr>


# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Написать отчет по выполненной лабораторной работе №3 в .md формате (readme.md) и разместить его в следующем каталоге: trunk\ii0xxyy\task_03\doc.
2. Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_03\src.
3. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/edit/main/readme.md?#L17-L17).
4. Документировать исходный код программы с помощью комментариев в стиле Doxygen. Полученную документацию разместить в каталоге: trunk\ii0xxyy\task_03\doc\html. Настроить GitHub Pages для автоматической публикации документации из этого каталога.
5. Разработанная программа также должна быть покрыта модульными тестами, написанными с использованием Google Test. Тесты разместить в каталоге: trunk\ii0xxyy\task_03\test.

# Выполнение задания #
Код программы:
```
#include <iostream>
#include "function.h"

int main() {
    double K = 10.0;
    double T = 0.1;
    double TD = 0.05;
    double T0 = 1.0;
    double tau = 10.0;
    double K_obj = 1.0;

    PID pid(K, T, TD, T0);
    Object obj(tau, K_obj, T0);

    double w = 1.0;
    double y = 0.0;
    double u = 0.0;

    for (int k = 0; k < 200; ++k) {
        if (k == 100) w = 2.0;
        double e = w - y;
        u = pid.compute(e);
        y = obj.update(u);
        std::cout << "k=" << k << ", w=" << w << ", y=" << y << ", u=" << u << std::endl;
    }

    return 0;
}

```
Результаты тестов:


![[../img/google_test.png]]


![[../img/doxygen.png]]