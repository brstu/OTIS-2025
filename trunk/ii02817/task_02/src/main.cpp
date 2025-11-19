#include <iostream>
#include <vector>
#include <cmath>

class func
{
private:
    double a;      // Коэффициент для текущего состояния
    double b;      // Коэффициент для предыдущего состояния
    double c;      // Коэффициент управления
    double d;      // Коэффициент нелинейности
    double t_curr; // Текущее значение температуры/состояния
    double t_prev; // Предыдущее значение температуры/состояния
    double u_curr; // Текущее управляющее воздействие
    double u_prev; // Предыдущее управляющее воздействие

public:
    // Конструктор по умолчанию - инициализация безопасными значениями
    func() : a(1), b(1), c(1), d(1), t_curr(1), t_prev(0), u_curr(1), u_prev(0) {}

    // Параметризованный конструктор для кастомной настройки системы
    func(double a, double b, double c, double d) : a(a), b(b), c(c), d(d),
                                                   t_curr(3), t_prev(2), u_curr(3), u_prev(2) {}

    // Установка начальных условий системы
    void value_set(double tcurr, double tprev, double ucurr, double uprev)
    {
        t_curr = tcurr; // Установка текущего состояния
        t_prev = tprev; // Установка предыдущего состояния
        u_curr = ucurr; // Текущее управляющее воздействие
        u_prev = uprev; // Предыдущее управляющее воздействие
    }

    // Линейная модель системы: x[k] = a*x[k-1] + b*u
    std::vector<double> linear(int steps) const
    {
        // Проверка корректности количества шагов
        if (steps <= 0)
            return {}; // Возвращаем пустой вектор для некорректного ввода

        std::vector<double> ans(steps); // Вектор для хранения результатов

        // Инициализация первого элемента текущим состоянием
        if (steps >= 1)
        {
            ans[0] = t_curr;
        }

        // Итеративное вычисление линейной динамики системы
        for (int i = 1; i < steps; i++)
        {
            // Рекуррентное соотношение: новое состояние = a*предыдущее + b*управление
            ans[i] = a * ans[i - 1] + b * u_curr;
        }
        return ans; // Возврат траектории системы
    }

    // Нелинейная модель системы с квадратичной и тригонометрической составляющими
    std::vector<double> nonlinear(int steps) const
    {
        // Проверка корректности количества шагов
        if (steps <= 0)
            return {}; // Возвращаем пустой вектор для некорректного ввода

        std::vector<double> ans(steps); // Вектор для хранения результатов

        // Инициализация истории состояний
        if (steps >= 1)
        {
            ans[0] = t_prev; // Начинаем с предпредыдущего состояния
        }
        if (steps >= 2)
        {
            ans[1] = t_curr; // Затем предыдущее состояние
        }

        // Вычисление нелинейной динамики системы
        for (int i = 2; i < steps; i++)
        {
            // Сложное рекуррентное соотношение с нелинейностями:
            // x[k] = a*x[k-1] - b*x[k-2]^2 + c*u_curr + d*sin(u_prev)
            ans[i] = a * ans[i - 1] - b * pow(ans[i - 2], 2) + c * u_curr + d * sin(u_prev);
        }
        return ans; // Возврат нелинейной траектории системы
    }

    // Метод для демонстрации работы класса (не изменяет логику)
    void debug_info() const
    {
        std::cout << "System parameters: a=" << a << ", b=" << b
                  << ", c=" << c << ", d=" << d << std::endl;
        std::cout << "Current state: t_curr=" << t_curr << ", t_prev=" << t_prev
                  << ", u_curr=" << u_curr << ", u_prev=" << u_prev << std::endl;
    }
};