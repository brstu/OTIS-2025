#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

// Первый тест: проверка линейной системы
TEST(SystemTests, LinearSystemTest) {
    // Тест 1: Базовый расчет
    EXPECT_NEAR(linearStep(0.4, 0.3, 0.5, 0.0), 0.15, 1e-6);

    // Тест 2: Проверка нескольких итераций (как в main)
    double y = 0.0;
    y = linearStep(0.4, 0.3, 0.5, y); // y[1]
    EXPECT_NEAR(y, 0.15, 1e-6);

    y = linearStep(0.4, 0.3, 0.5, y); // y[2]
    EXPECT_NEAR(y, 0.21, 1e-6);

    y = linearStep(0.4, 0.3, 0.5, y); // y[3]
    EXPECT_NEAR(y, 0.234, 1e-6);

    // Тест 3: Проверка с нулевым входом
    EXPECT_NEAR(linearStep(0.4, 0.3, 0.0, 1.0), 0.4, 1e-6);
}

// Второй тест: проверка нелинейной системы
TEST(SystemTests, NonlinearSystemTest) {
    // Тест 1: Первый шаг из main
    double result = nonlinearStep(0.5, 0.2, 0.1, 0.3, 26.0, 25.0, 2.0, 1.0);
    double expected = 0.5 * 26.0 - 0.2 * (25.0 * 25.0) + 0.1 * 2.0 + 0.3 * std::sin(1.0);
    EXPECT_NEAR(result, expected, 1e-6);

    // Тест 2: Проверка нескольких итераций
    double y_prev = 25.0;
    double y_curr = 26.0;
    double u_prev = 1.0;
    double u_curr = 2.0;
    const double u_offset = 0.3;

    // Первая итерация
    double y_next = nonlinearStep(0.5, 0.2, 0.1, 0.3, y_curr, y_prev, u_curr, u_prev);

    // Обновление для второй итерации
    y_prev = y_curr;
    y_curr = y_next;
    u_prev = u_curr;
    u_curr += u_offset;

    // Вторая итерация
    y_next = nonlinearStep(0.5, 0.2, 0.1, 0.3, y_curr, y_prev, u_curr, u_prev);
    // Проверяем, что результат является числом (не NaN и не бесконечным)
    EXPECT_TRUE(std::isfinite(y_next));

    // Тест 3: Проверка граничного случая
    EXPECT_NEAR(nonlinearStep(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), 0.0, 1e-6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}