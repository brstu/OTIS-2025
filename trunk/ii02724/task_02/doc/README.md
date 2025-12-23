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
<p align="right">Ханцевич Г.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).

## Задание 2.##
В ходе выполнения было написано 3 теста. Было написано 2 теста для функции linear и 1 тест для nonlinear. Покрытие программы составляет 57%. Замер производился с помощью программы OpenCppCoverage(https://github.com/OpenCppCoverage/OpenCppCoverage/releases).
[==========] Running 3 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from Test
[ RUN      ] Test.linearr
[       OK ] Test.linearr (0 ms)
[ RUN      ] Test.linearr2
[       OK ] Test.linearr2 (0 ms)
[----------] 2 tests from Test (1 ms total)

[----------] 1 test from Test2
[ RUN      ] Test2.nonlinearr
[       OK ] Test2.nonlinearr (0 ms)
[----------] 1 test from Test2 (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test suites ran. (4 ms total)
[  PASSED  ] 3 tests.