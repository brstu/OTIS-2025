<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Модульное тестирование. Покрытие исходного кода тестами."</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Степанюк И.О.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii02720\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii02720\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).

## Описание программы

Программа моделирует температурную систему с использованием линейных и нелинейных моделей. Основные компоненты:

- **ISimulatedModel** - интерфейс для моделей симуляции
- **LinearModel** - реализация линейной модели температуры
- **NonLinearModel** - реализация нелинейной модели температуры
- **IFactoryModel** - интерфейс фабрики для создания моделей
- **FactoryLinearModel** - фабрика для создания линейных моделей
- **FactoryNonLinearModel** - фабрика для создания нелинейных моделей

### Линейная модель

Линейная модель использует формулу:
```
y(t+1) = a * y(t) + b * u(t)
```

Где:
- `y(t)` - текущая температура
- `u(t)` - входной сигнал (управляющее воздействие)
- `a = 0.8` - коэффициент предыдущего значения
- `b = 0.3` - коэффициент входного сигнала

### Нелинейная модель

Нелинейная модель использует формулу:
```
y(t+1) = a * y(t) - b * y(t-1)² + c * u(t) + d * sin(u(t-1))
```

Где:
- `y(t)` - текущая температура
- `y(t-1)` - предыдущая температура
- `u(t)` - входной сигнал
- `u(t-1)` - предыдущий входной сигнал
- `a = 0.8` - линейный коэффициент
- `b = 0.01` - нелинейный коэффициент
- `c = 0.4` - коэффициент входного сигнала
- `d = 0.1` - коэффициент синусоидальной компоненты

## Структура проекта

```
task_02/
├── src/
│   ├── main.cpp
│   ├── CMakeLists.txt
│   ├── model/
│   │   ├── isimulatedmodel.h
│   │   ├── linearmodel.h
│   │   └── nonlinearmodel.h
│   └── factory/
│       ├── ifactorymodel.h
│       ├── factorylinearmodel.h
│       └── factorynonlinearmodel.h
├── test/
│   ├── test.cpp
│   └── CMakeLists.txt
└── doc/
    └── README.md
```

## Модульные тесты

### Список реализованных тестов

Всего написано **14 модульных тестов**:

#### Тесты для LinearModel (6 тестов):
1. **SingleInputSimulation** - тест одиночного входного сигнала
2. **MultipleStepsSimulation** - тест последовательности входных сигналов
3. **ZeroInputSimulation** - тест с нулевым входным сигналом
4. **NegativeInputSimulation** - тест с отрицательным входным сигналом
5. **BoundaryConditions** - тест граничных условий (начальное значение = 0)
6. **OriginalSequenceTest** - тест с последовательностью из оригинальной программы

#### Тесты для LinearModelFactory (1 тест):
7. **FactoryCreation** - тест создания модели через фабрику

#### Тесты для NonLinearModel (6 тестов):
8. **SingleInputSimulation** - тест одиночного входного сигнала
9. **MultipleStepsSimulation** - тест последовательности входных сигналов с проверкой формулы
10. **ZeroInputSimulation** - тест с нулевым входным сигналом
11. **NegativeInputSimulation** - тест с отрицательным входным сигналом
12. **BoundaryConditions** - тест граничных условий (начальное значение = 0)
13. **OriginalSequenceTest** - тест с последовательностью из оригинальной программы

#### Тесты для NonLinearModelFactory (1 тест):
14. **FactoryCreation** - тест создания модели через фабрику

## Код модульных тестов

Основные тесты реализованы в файле `test/test.cpp`. Примеры ключевых тестов:

```cpp
// Тест линейной модели с множественными шагами
TEST(TestLinearModel, MultipleStepsSimulation)
{   
    const double a = 0.8;
    const double b = 0.3;
    const double initialY = 20.0;
    std::vector<double> inputs = {2.0, 3.0, 4.0};
    
    auto model = std::make_unique<LinearModel>(a, b, initialY);
    
    std::vector<double> expected_results = {20.0, 16.6, 14.18};
    
    for (size_t i = 0; i < inputs.size(); i++)
    {
        auto result = model->simulate(inputs[i]);
        EXPECT_EQ(result.size(), 1);
        EXPECT_NEAR(result[0], expected_results[i], 1e-5)
            << "Mismatch at step " << i;
    }
}

// Тест нелинейной модели с отрицательным входом
TEST(TestNonLinearModel, NegativeInputSimulation)
{   
    const double a = 0.8;
    const double b = 0.01;
    const double c = 0.4;
    const double d = 0.1;
    const double initialY = 20.0;
    const double u = -3.0;

    auto model = std::make_unique<NonLinearModel>(a, b, c, d, initialY);
    std::vector<double> result = model->simulate(u);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 20.0, 1e-5);
    
    // Calculate expected next value
    // result = 0.8*20.0 - 0.01*20.0^2 + 0.4*(-3.0) + 0.1*sin(0)
    double expected = 0.8 * 20.0 - 0.01 * 20.0 * 20.0 + 0.4 * (-3.0) + 0.1 * std::sin(0);
    result = model->simulate(u);
    EXPECT_NEAR(result[0], expected, 1e-5);
}
```

## Результаты тестирования

### Сборка и запуск тестов

```bash
cd task_02/test
mkdir build && cd build
cmake ..
make
./task_02_ii02720_test
```

### Результаты выполнения тестов (Google Test)

```
[==========] Running 14 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 6 tests from TestLinearModel
[ RUN      ] TestLinearModel.SingleInputSimulation
[       OK ] TestLinearModel.SingleInputSimulation (0 ms)
[ RUN      ] TestLinearModel.MultipleStepsSimulation
[       OK ] TestLinearModel.MultipleStepsSimulation (0 ms)
[ RUN      ] TestLinearModel.ZeroInputSimulation
[       OK ] TestLinearModel.ZeroInputSimulation (0 ms)
[ RUN      ] TestLinearModel.NegativeInputSimulation
[       OK ] TestLinearModel.NegativeInputSimulation (0 ms)
[ RUN      ] TestLinearModel.BoundaryConditions
[       OK ] TestLinearModel.BoundaryConditions (0 ms)
[ RUN      ] TestLinearModel.OriginalSequenceTest
[       OK ] TestLinearModel.OriginalSequenceTest (0 ms)
[----------] 6 tests from TestLinearModel (0 ms total)

[----------] 1 test from TestLinearModelFactory
[ RUN      ] TestLinearModelFactory.FactoryCreation
[       OK ] TestLinearModelFactory.FactoryCreation (0 ms)
[----------] 1 test from TestLinearModelFactory (0 ms total)

[----------] 6 tests from TestNonLinearModel
[ RUN      ] TestNonLinearModel.SingleInputSimulation
[       OK ] TestNonLinearModel.SingleInputSimulation (0 ms)
[ RUN      ] TestNonLinearModel.MultipleStepsSimulation
[       OK ] TestNonLinearModel.MultipleStepsSimulation (0 ms)
[ RUN      ] TestNonLinearModel.ZeroInputSimulation
[       OK ] TestNonLinearModel.ZeroInputSimulation (0 ms)
[ RUN      ] TestNonLinearModel.NegativeInputSimulation
[       OK ] TestNonLinearModel.NegativeInputSimulation (0 ms)
[ RUN      ] TestNonLinearModel.BoundaryConditions
[       OK ] TestNonLinearModel.BoundaryConditions (0 ms)
[ RUN      ] TestNonLinearModel.OriginalSequenceTest
[       OK ] TestNonLinearModel.OriginalSequenceTest (0 ms)
[----------] 6 tests from TestNonLinearModel (0 ms total)

[----------] 1 test from TestNonLinearModelFactory
[ RUN      ] TestNonLinearModelFactory.FactoryCreation
[       OK ] TestNonLinearModelFactory.FactoryCreation (0 ms)
[----------] 1 test from TestNonLinearModelFactory (0 ms total)

[----------] Global test environment tear-down
[==========] 14 tests from 4 test suites ran. (0 ms total)
[  PASSED  ] 14 tests.
```

**Результат: Все 14 тестов успешно пройдены! ✅**

## Анализ покрытия кода (gcovr)

### Команда для генерации отчета о покрытии:

```bash
cd task_02/test/build
gcovr --root .. --filter '../src/' --html --html-details -o ../../doc/coverage.html
```

### Результаты покрытия кода:

Для исходного кода проекта (без учета системных библиотек и Google Test):

| Файл | Покрытие строк |
|------|----------------|
| `src/model/isimulatedmodel.h` | **100%** |
| `src/model/linearmodel.h` | **100%** |
| `src/model/nonlinearmodel.h` | **100%** |
| `src/factory/ifactorymodel.h` | **100%** |
| `src/factory/factorylinearmodel.h` | **100%** |
| `src/factory/factorynonlinearmodel.h` | **100%** |
| `test/test.cpp` | **98%** |

**Общее покрытие кода проекта: ~99%**

### Детальный отчет покрытия:

```
File                                                    Lines    Exec  Cover
------------------------------------------------------------------------------
src/factory/factorylinearmodel.h                            7       7   100%
src/factory/factorynonlinearmodel.h                         9       9   100%
src/factory/ifactorymodel.h                                 1       1   100%
src/model/isimulatedmodel.h                                 1       1   100%
src/model/linearmodel.h                                    10      10   100%
src/model/nonlinearmodel.h                                 15      15   100%
test/test.cpp                                             172     170    98%
------------------------------------------------------------------------------
TOTAL (project files)                                     215     213    99%
```

## Выводы

1. **Успешно реализовано 14 модульных тестов** для всех основных компонентов программы
2. **Все тесты проходят успешно**, что подтверждает корректность реализации
3. **Покрытие кода тестами составляет ~99%**, что является отличным показателем
4. Использован фреймворк **Google Test** для написания модульных тестов
5. Использован инструмент **gcovr** для анализа покрытия кода
6. Программа рефакторирована с применением паттернов проектирования:
   - **Factory Pattern** для создания моделей
   - **Interface/Abstract Class** для полиморфизма
   - **Header-only implementation** для простоты использования

## Инструкция по сборке

### Сборка основной программы:
```bash
cd task_02/src
mkdir build && cd build
cmake ..
make
./task_02_ii02720_src
```

### Сборка и запуск тестов:
```bash
cd task_02/test
mkdir build && cd build
cmake ..
make
./task_02_ii02720_test
```

### Генерация отчета о покрытии:
```bash
cd task_02/test/build
gcovr --root .. --filter '../src/' --html --html-details -o ../../doc/coverage.html
# Откройте coverage.html в браузере для просмотра детального отчета
```

