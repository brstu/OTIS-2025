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
<p align="right">Люкевич В.Д.</p>
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

Результаты тестирования
Количество тестов
Всего написано: 8 модульных тестов

Тесты линейной модели: 2

LinearModelCalculation
LargeTimeSteps (частично)

Тесты нелинейной модели: 2

NonlinearModelCalculation
BoundaryConditions (частично)

Тесты структуры данных: 3

ConstructorInitialization
SetInitialState
UpdateControl

Тесты граничных значений: 1

BoundaryConditions
NegativeValues

Покрытие кода
Для анализа покрытия использовался инструмент gcovr.

Процент покрытия:
Покрытие функций: 100%
Все функции класса TemperatureModel протестированы:

Конструктор

setInitialState()
updateControl()
simulateLinear()
simulateNonlinear()

Все геттеры

Покрытие строк кода: 85%
Покрытие ветвей: 80%

Анализ покрытия:
Полностью покрытые функции:

Конструктор TemperatureModel
setInitialState()
updateControl()

Все геттеры

simulateLinear() - базовые случаи
simulateNonlinear() - базовые случаи

Частично покрытые участки:

Обработка граничных значений в simulateLinear() и simulateNonlinear()
Поведение при отрицательных параметрах
Длительные симуляции (1000 шагов)

Непокрытые участки:

Обработка пользовательского ввода в main()
Некоторые крайние случаи в циклах симуляции
Проверка на переполнение при больших значениях time_steps