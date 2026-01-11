<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Каневега К. А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# ЗАДАНИЕ #

Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\ii0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\ii0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2025/blob/b2d60c2765b369aed21af76af8fa4461da2c8da6/README.md?plain=1#L13).

## Код модульных тестов ##
```
TEST(LinemodelTest, BasicCase) {
    float y = 1.0f;
    float u = 2.0f;
    float a = 1.5f;
    float b = -0.5f;
    int steps = 1;

    auto result = Linemodel(y, u, steps, a, b);
    ASSERT_EQ(result.size(), 1);
    float expected = a * y + b * u;
    EXPECT_FLOAT_EQ(result[0], expected);
}

TEST(LinemodelTest, MultipleSteps) {
    float y = 1.0f;
    float u = 1.0f;
    float a = 2.0f;
    float b = 0.5f;
    int steps = 3;

    auto result = Linemodel(y, u, steps, a, b);
    ASSERT_EQ(result.size(), 3);
    EXPECT_FLOAT_EQ(result[0], 2.0f * 1.0f + 0.5f * 1.0f);  // 2.5
    EXPECT_FLOAT_EQ(result[1], 2.0f * 2.5f + 0.5f * 1.0f);  // 5.5
    EXPECT_FLOAT_EQ(result[2], 2.0f * 5.5f + 0.5f * 1.0f);  // 11.5
}

TEST(LinemodelTest, ZeroCoefficients) {
    auto result = Linemodel(5.0f, 4.0f, 2, 0.0f, 0.0f);
    for (float val : result) EXPECT_FLOAT_EQ(val, 0.0f);
}

TEST(UnLinemodelTest, BasicCase) {
    Params p{2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1};
    float y = 1.0f;
    float y0 = 0.0f;

    auto result = UnLinemodel(p, y, y0);
    ASSERT_EQ(result.size(), 1);

    float expected = p.a * y - p.b * y0 + p.c * p.u + p.d * sin(p.u);
    EXPECT_NEAR(result[0], expected, 1e-5);
}

TEST(UnLinemodelTest, ZeroCoefficients) {
    Params p{0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2};
    auto result = UnLinemodel(p, 2.0f, 1.0f);
    for (float val : result) EXPECT_FLOAT_EQ(val, 0.0f);
}

TEST(UnLinemodelTest, SinusoidalEffect) {
    Params p{0.0f, 0.0f, 0.0f, 2.0f, static_cast<float>(M_PI / 2), 1};
    auto result = UnLinemodel(p, 0.0f, 0.0f);
    ASSERT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 2.0f * std::sin(M_PI / 2), 1e-5);
}
```
## Тестовое покрытие

- Количество написанных тестов: 6

- Процент покрытия кода тестами: 100% (оценено с помощью инструмента gcovr)