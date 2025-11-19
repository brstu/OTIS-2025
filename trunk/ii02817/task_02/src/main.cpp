#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class DynamicSystem
{
private:
    double alpha, beta, gamma, delta;
    double state_x, state_y, input_u, input_v;
    double memory_cell;

public:
    // Конструкторы с уникальными начальными состояниями
    DynamicSystem() : alpha(0.8), beta(0.3), gamma(0.5), delta(0.2),
                      state_x(1.5), state_y(0.5), input_u(2.0), input_v(1.0), memory_cell(0.0) {}

    DynamicSystem(double a, double b, double c, double d) : alpha(a), beta(b), gamma(c), delta(d),
                                                            state_x(std::abs(a) + 0.1), state_y(std::abs(b) + 0.1),
                                                            input_u(std::abs(c) + 0.1), input_v(std::abs(d) + 0.1), memory_cell(0.0) {}

    // Уникальный метод установки состояний с валидацией
    void configure_states(double x, double y, double u, double v)
    {
        state_x = (std::abs(x) > 1e-10) ? x : 0.1;
        state_y = (std::abs(y) > 1e-10) ? y : 0.1;
        input_u = u;
        input_v = v;
        memory_cell = (x + y) * 0.5; // Инициализация ячейки памяти
    }

    // Линейная динамика с уникальной двухкомпонентной системой
    std::vector<double> compute_linear_dynamics(int iterations) const
    {
        if (iterations <= 0)
            return {};

        std::vector<double> trajectory;
        trajectory.reserve(iterations);

        double x = state_x;
        double y = state_y;

        for (int i = 0; i < iterations; ++i)
        {
            // Уникальное линейное преобразование с двумя состояниями
            double new_x = alpha * x + beta * y + gamma * input_u;
            double new_y = beta * x - alpha * y + delta * input_v;

            trajectory.push_back(new_x + new_y); // Комбинированный выход

            // Обновление состояний
            x = new_x;
            y = new_y;
        }

        return trajectory;
    }

    // Нелинейная динамика с уникальными преобразованиями
    std::vector<double> compute_nonlinear_dynamics(int iterations) const
    {
        if (iterations <= 0)
            return {};

        std::vector<double> trajectory;
        trajectory.reserve(iterations);

        double x1 = state_x;
        double x2 = state_y;
        double m = memory_cell;

        for (int i = 0; i < iterations; ++i)
        {
            // Уникальное нелинейное преобразование с памятью
            double nonlinear_term = gamma * std::tanh(input_u * x1) + delta * std::cos(input_v * x2);
            double coupling = beta * std::sin(x1 * x2) * std::exp(-std::abs(m));

            double new_x1 = alpha * x1 - coupling + nonlinear_term;
            double new_x2 = delta * x2 + coupling - nonlinear_term;
            m = 0.9 * m + 0.1 * (new_x1 * new_x2); // Адаптивная память

            trajectory.push_back(new_x1 + new_x2 + m);

            x1 = new_x1;
            x2 = new_x2;
        }

        return trajectory;
    }

    // Уникальный метод для анализа стабильности системы
    double analyze_stability() const
    {
        double jacobian_det = alpha * delta - beta * gamma;
        double trace = alpha + delta;

        // Критерий устойчивости для дискретной системы
        return std::abs(trace) - std::abs(jacobian_det) - 1.0;
    }

    // Метод для получения текущих параметров
    void get_parameters(double &a, double &b, double &c, double &d) const
    {
        a = alpha;
        b = beta;
        c = gamma;
        d = delta;
    }

    // Уникальный метод сброса с сохранением параметров
    void soft_reset()
    {
        state_x = (std::abs(alpha) + 0.1) * 0.5;
        state_y = (std::abs(beta) + 0.1) * 0.5;
        memory_cell = 0.0;
    }
};