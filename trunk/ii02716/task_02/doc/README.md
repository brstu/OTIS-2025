<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Написание модульных тестов для программы моделирования температуры”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Ничипорчик Д.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).

## Задание 2.##
В ходе выполнения было написано 4 теста. Было написано по два теста для каждой функции(Nonlinear,Linear). Покрытие программы составляет 28%. Замер производился с помощью программы OpenCppCoverage(https://github.com/OpenCppCoverage/OpenCppCoverage/releases).
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from TestFuns
[ RUN      ] TestFuns.LinearSystem_chek1
[       OK ] TestFuns.LinearSystem_chek1 (0 ms)
[ RUN      ] TestFuns.LinearSystem_chek2
[       OK ] TestFuns.LinearSystem_chek2 (0 ms)
[ RUN      ] TestFuns.NonLinearSystem_chek1
[       OK ] TestFuns.NonLinearSystem_chek1 (0 ms)
[ RUN      ] TestFuns.NonLinearSystem_chek2
[       OK ] TestFuns.NonLinearSystem_chek2 (0 ms)
[----------] 4 tests from TestFuns (5 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (8 ms total)
[  PASSED  ] 4 tests.

##Tests

![Test:](test.jpg)