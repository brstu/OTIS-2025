#include <iostream>
#include "pid.h"
#include "model.h"

/**
 * @brief Пример использования PID-регулятора для управления простой моделью.
 */
int main() {
    // Настройки PID: можно менять и смотреть, как влияет
    PID pid(1.0, 0.1, 0.01);

    // Модель с начальным состоянием 0 и коэффициентом a = 1
    Model model(0.0, 1.0);

    double setpoint = 10.0;  // целевое значение
    double dt = 0.01;        // шаг по времени
    int steps = 1000;        // количество шагов моделирования

    for (int i = 0; i < steps; ++i) {
        double measurement = model.getState();
        double control = pid.compute(setpoint, measurement, dt);
        double new_state = model.update(control, dt);

        if (i % 100 == 0) {
            std::cout << "t = " << i * dt
                      << "  x = " << new_state
                      << "  u = " << control
                      << std::endl;
        }
    }

    return 0;
}
