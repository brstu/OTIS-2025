// test/pid_test.cpp
#include <gtest/gtest.h>
#include "pid_controller.h"
#include "model.h"

// Тест 1 — просто создаём объекты, ничего не ломается
TEST(Basic, CanCreateObjects)
{
    PIDController pid(1.0, 1.0, 0.0, 0.1);
    Model plant;
    EXPECT_TRUE(true);  // просто чтобы тест был зелёный
}

// Тест 2 — регулятор что-то выдаёт
TEST(PIDController, ReturnsSomeValue)
{
    PIDController pid(10.0, 1.0, 0.0, 0.1);
    double u = pid.compute(1.0);
    EXPECT_GT(u, 0.0);  // u должен быть положительным при положительной ошибке
}

// Тест 3 — модель меняет температуру
TEST(Model, TemperatureChanges)
{
    Model plant(0.1, 1.0, 0.0, 0.1);
    plant.update(10.0);  // подаём нагрев
    double t1 = plant.getTemperature();
    plant.update(10.0);
    double t2 = plant.getTemperature();
    EXPECT_GT(t2, t1);
}

// Тест 4 — сброс работает
TEST(PIDController, ResetClearsState)
{
    PIDController pid(5.0, 1.0, 0.0, 0.1);
    pid.compute(1.0);
    pid.reset();
    double u = pid.compute(1.0);
    EXPECT_NEAR(u, 5.5, 0.1);  // K*(1 + dt/Ti) = 5.5
}