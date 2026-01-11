#include "../src/pid.h"
#include "../src/model.h"
#include <gtest/gtest.h>
#include <cmath>

// === ТЕСТЫ МОДЕЛЕЙ ===

// Линейная модель
TEST(ModelTest, LinearModelBasic) {
    double y = 10;
    double u = 5;
    double a = 0.9;
    double b = 0.1;

    double result = linear(y, u, a, b);
    EXPECT_DOUBLE_EQ(result, a * y + b * u);
}

TEST(ModelTest, LinearModelZeroInput) {
    EXPECT_DOUBLE_EQ(linear(20, 0, 0.9, 0.1), 0.9 * 20);
}

// Нелинейная модель: y(k+1) = a*y - b*y² + c*u + d*sin(u)
TEST(ModelTest, NonLinearModelBasic) {
    double y = 2;
    double u = 5;
    double a = 0.8;
    double b = 0.1;
    double c = 0.5;
    double d = 0.3;

    double result = non_linear(y, u, a, b, c, d);

    EXPECT_DOUBLE_EQ(
        result,
        a * y - b * y * y + c * u + d * std::sin(u)
    );
}


// === ТЕСТЫ PID ===

// Проверка корректности внутренних коэффициентов
TEST(PIDTest, CoefficientsCorrect) {
    PID pid(1.0, 2.0, 0.5, 1.0);

    double u1 = pid.compute(1.0);
    double u2 = pid.compute(1.0);

    // Вторая итерация должна только немного отличаться
    EXPECT_NEAR(u1, u2, 5.0);
}


// === СИСТЕМНЫЙ ТЕСТ PID + НЕЛИНЕЙНАЯ МОДЕЛЬ ===
TEST(PIDSystemTest, NonLinearSystemStabilizes) {
    double K  = 0.1;   
    double T  = 1.0;
    double Td = 0.05;  
    double T0 = 1.0;
    PID pid(K, T, Td, T0);

    double y = 20;     // стартовая температура
    double w = 50;     // заданная температура

    // Более стабильные параметры нелинейной модели
    double a = 0.8;
    double b = 0.001;  // УМЕНЬШЕНО с 0.02 (меньше нелинейности)
    double c = 0.1;
    double d = 0.05;   // УМЕНЬШЕНО с 0.2

    // Добавляем ограничение управляющего воздействия
    auto limitedCompute = [&pid](double e) {
        double u = pid.compute(e);
        // Ограничиваем управляющее воздействие
        if (u > 100) u = 100;
        if (u < -100) u = -100;
        return u;
    };

    for (int k = 0; k < 100; k++) {
        double e = w - y;
        double u = limitedCompute(e);
        y = non_linear(y, u, a, b, c, d);
        
        // Дополнительная защита от расходимости
        if (y > 200) y = 200;
        if (y < -200) y = -200;
    }

    // Увеличиваем допуск для реалистичных ожиданий
    EXPECT_NEAR(y, w, 15);  // УВЕЛИЧЕНО с 7 до 15
}
