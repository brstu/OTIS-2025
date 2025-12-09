#include <iostream>
#include "functions.h"

int main() {
    const int steps = 15;
    double y_next = 0;
    double y_prev = 0;    // Для нелинейной модели
    double u = 1;  
    double u_prev = 1;    // Для нелинейной модели

    // Задаём параметры моделей
    LinearParams lp{0.8, 0.1};
    NonlinearParams nlp{0.8, 0.01, 0.05, 0.005};

    std::cout << "Linear model:" << std::endl;
    for (int i = 0; i < steps; i++) {
        y_next = linearModel(y_next, u, lp);
        std::cout << i << "\t" << y_next << std::endl;
    }

    std::cout << std::endl;
    y_next = 0;
    y_prev = 0;

    std::cout << "Nonlinear model:" << std::endl;
    for (int i = 0; i < steps; i++) {
        double y_temp = y_next;   // сохраняем текущее y для y_prev
        double u_temp = u;        // сохраняем текущее u для u_prev

        y_next = nonlinearModel(y_next, y_prev, u, u_prev, nlp);
        std::cout << i << "\t" << y_next << std::endl;

        y_prev = y_temp;  // обновляем y_prev для следующей итерации
        u_prev = u_temp;  // обновляем u_prev для следующей итерации
    }

    return 0;
}
