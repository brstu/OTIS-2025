#include <iostream>
#include <iomanip>
#include "pid.h"
#include "plant.h"

int main() {
    constexpr double dt = 0.1; //Шаг времени
    constexpr int N = 100; //Длина симуляции
    constexpr double ref = 50.0; //Заданное значение

    LinearPlant sys(0.98, 0.05, 0.0);
    PID controller(10.0, 0.1, 0.01, dt);

    std::cout << "+-------+----------+----------+----------+----------+\n";
    std::cout << "|   t   |   ref    |    y     |    u     |    e     |\n";
    std::cout << "+-------+----------+----------+----------+----------+\n";

    double time = 0.0;

    for (int i = 0; i < N; ++i) {
        const double y = sys.y();
        const double err = ref - y;
        const double ctrl = controller.update(err);

        sys.step(ctrl);

        std::cout << "| "
                  << std::setw(5) << std::fixed << std::setprecision(2) << time << " | "
                  << std::setw(8) << ref << " | "
                  << std::setw(8) << sys.y() << " | "
                  << std::setw(8) << ctrl << " | "
                  << std::setw(8) << err << " |\n";

        time += dt;
    }

    std::cout << "+-------+----------+----------+----------+----------+\n";
    return 0;
}