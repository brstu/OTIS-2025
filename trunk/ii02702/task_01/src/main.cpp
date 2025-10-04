#include <iostream>
#include <cmath>

// Функция симуляции линейной модели
void simulateLinearModel(double y, double u, int t, double a, double b) {
    for (int i = 0; i <= t; i++) {
        std::cout << i << ' ' << y << std::endl;
        y = a * y + b * u;
    }
}

// Функция симуляции нелинейной модели
void simulateNonLinearModel(double y, double u, int t, double a, double b, double c, double d) {
    // Инициализируем предыдущие выходные и входные значения с помощью смещений.
    // Смещения (yOffset и uOffset) представляют собой разницу между начальным и предыдущим состояниями,
    // позволяя нелинейной модели начать с заданной истории для y и u.
    const double y_offset = 0.1;
    const double u_offset = 0.1;

    const double u_step = 0.5;       // шаг изменения для переменной u в нелинейной модели

    double prevY = y - y_offset;
    double prevU = u - u_offset;

    for (int i = 0; i <= t; i++) {
        std::cout << i << ' ' << y << std::endl;
        double nextY = a * y - b * prevY * prevY + c * u + d * sin(prevU);
        prevU += u_step;
        prevY = y;
        y = nextY;
    }
}

int main() {
    // Начальные условия системы
    const double y = 0;        // начальное значение выходной переменной (состояние системы)
    const double u = 1;        // входное воздействие (управляющий сигнал)
    const int t = 25;          // время симуляции (количество шагов)

    // Параметры для линейной модели
    double linear_a = 0.4;     // коэффициент при предыдущем значении y
    double linear_b = 0.5;     // коэффициент при входном воздействии u

    // Параметры для нелинейной модели
    double nonlinear_a = 0.5;  // линейный коэффициент при y
    double nonlinear_b = 0.5;  // коэффициент при квадрате предыдущего значения y (нелинейность)
    double nonlinear_c = 0.3;  // коэффициент при входном воздействии u
    double nonlinear_d = 0.5;  // коэффициент при синусоидальном члене
    
    std::cout << "Linear simulation:" << std::endl;
    simulateLinearModel(y, u, t, linear_a, linear_b);
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl;
    simulateNonLinearModel(y, u, t, nonlinear_a, nonlinear_b, nonlinear_c, nonlinear_d);
    std::cout << std::endl;

    return 0;
}