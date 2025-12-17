/**
 * @file main_ruslan.cpp
 * @brief Главный файл программы - симулятор PID регулятора
 * @author Ruslan
 * @date 2024
 */

#include "pid_ruslan.h"
#include <iostream>
#include <string>

/**
 * @brief Глобальные константы для моделей
 */
constexpr double TIME_STEP = 0.05;
constexpr double NONLINEAR_COEFF = 0.01;

/**
 * @brief Шаблонная модель динамической системы.
 * @tparam UpdateRule Правило обновления состояния системы
 */
template <typename UpdateRule>
class SystemModel {
public:
    /**
     * @brief Оператор вызова для обновления состояния системы
     * @param input Входное воздействие
     * @return Текущее состояние системы
     */
    double operator()(double input) {
        state = updateRule(state, input);
        return state;
    }

private:
    double state = 0.0;        ///< Текущее состояние системы
    UpdateRule updateRule;     ///< Правило обновления состояния
};

/**
 * @brief Линейная система: y(t+1) = y(t) + T * u
 * Простая тепловая модель без нелинейностей
 */
struct LinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input;
    }
};

/**
 * @brief Нелинейная система: y(t+1) = y(t) + T*u + α*u²
 * Ускоряет рост при больших входных воздействиях
 */
struct NonlinearUpdate {
    double operator()(double state, double input) const {
        return state + TIME_STEP * input + NONLINEAR_COEFF * input * input;
    }
};

using LinearModel    = SystemModel<LinearUpdate>;      ///< Линейная модель
using NonlinearModel = SystemModel<NonlinearUpdate>;   ///< Нелинейная модель

/**
 * @brief Универсальная функция для симуляции системы с PID регулятором
 * @tparam Model Тип модели системы
 * @param model Модель системы
 * @param steps Количество шагов симуляции
 * @param controller PID регулятор
 * @param name Название симуляции
 */
template <typename Model>
void runSimulation(Model model, int steps, PID_ruslan& controller, const std::string& name)
{
    std::cout << "=== " << name << " ===\n";

    double measured = 0.0;
    const double setpoint = 1.0;

    for (int i = 0; i < steps; ++i) {
        double control = controller.compute(setpoint, measured);
        measured = model(control);

        std::cout << "Step " << i
                  << " | Setpoint: " << setpoint
                  << " | Control: " << control
                  << " | Output: " << measured << "\n";
    }

    std::cout << name << " simulation finished.\n\n";
}

/**
 * @brief Главная функция программы
 * @return Код завершения
 */
int main() {
    PID_ruslan linearPID(1.0, 0.1, 0.05);
    PID_ruslan nonlinearPID(1.0, 0.1, 0.05);

    const int steps = 50;

    runSimulation(LinearModel{}, steps, linearPID, "Linear Model");
    runSimulation(NonlinearModel{}, steps, nonlinearPID, "Nonlinear Model");

    std::cout << "Simulations completed.\n";
    return 0;
}