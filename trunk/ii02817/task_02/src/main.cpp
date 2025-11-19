#include <iostream>
#include <vector>
#include <cmath>

class QuantumDynamicModel
{
private:
    double quantum_flux;      // Коэффициент квантового потока
    double temporal_echo;     // Коэффициент временного эха
    double control_resonance; // Коэффициент резонанса управления
    double chaos_factor;      // Коэффициент хаотичности
    double phase_current;     // Текущая фаза колебаний
    double phase_previous;    // Предыдущая фаза колебаний
    double impulse_current;   // Текущий импульс возбуждения
    double impulse_previous;  // Предыдущий импульс возбуждения

public:
    // Конструктор по умолчанию - инициализация квантовыми значениями
    QuantumDynamicModel() : quantum_flux(1), temporal_echo(1), control_resonance(1), chaos_factor(1),
                            phase_current(1), phase_previous(0), impulse_current(1), impulse_previous(0) {}

    // Параметризованный конструктор для тонкой настройки квантовой системы
    QuantumDynamicModel(double qf, double te, double cr, double cf) : quantum_flux(qf), temporal_echo(te), control_resonance(cr), chaos_factor(cf),
                                                                      phase_current(3), phase_previous(2), impulse_current(3), impulse_previous(2) {}

    // Установка квантовых состояний системы
    void configure_quantum_states(double p_curr, double p_prev, double i_curr, double i_prev)
    {
        phase_current = p_curr;    // Установка текущей квантовой фазы
        phase_previous = p_prev;   // Установка предыдущей квантовой фазы
        impulse_current = i_curr;  // Текущий квантовый импульс
        impulse_previous = i_prev; // Предыдущий квантовый импульс
    }

    // Линейная квантовая динамика: ψ[k] = quantum_flux*ψ[k-1] + temporal_echo*impulse
    std::vector<double> compute_quantum_wavefunction(int oscillations) const
    {
        // Проверка корректности количества осцилляций
        if (oscillations <= 0)
            return {}; // Возвращаем пустой вектор для некорректного ввода

        std::vector<double> quantum_states(oscillations); // Вектор для хранения квантовых состояний

        // Инициализация первого элемента текущей квантовой фазой
        if (oscillations >= 1)
        {
            quantum_states[0] = phase_current;
        }

        // Итеративное вычисление линейной квантовой динамики
        for (int i = 1; i < oscillations; i++)
        {
            // Квантовое рекуррентное соотношение: новое состояние = quantum_flux*предыдущее + temporal_echo*импульс
            quantum_states[i] = quantum_flux * quantum_states[i - 1] + temporal_echo * impulse_current;
        }
        return quantum_states; // Возврат траектории квантовой системы
    }

    // Нелинейная квантовая динамика с хаотическими и резонансными составляющими
    std::vector<double> compute_chaotic_resonance(int oscillations) const
    {
        // Проверка корректности количества осцилляций
        if (oscillations <= 0)
            return {}; // Возвращаем пустой вектор для некорректного ввода

        std::vector<double> resonance_states(oscillations); // Вектор для хранения резонансных состояний

        // Инициализация истории квантовых состояний
        if (oscillations >= 1)
        {
            resonance_states[0] = phase_previous; // Начинаем с предпредыдущей квантовой фазы
        }
        if (oscillations >= 2)
        {
            resonance_states[1] = phase_current; // Затем предыдущая квантовая фаза
        }

        // Вычисление нелинейной квантовой динамики с хаосом
        for (int i = 2; i < oscillations; i++)
        {
            // Сложное квантовое рекуррентное соотношение с нелинейностями:
            // ψ[k] = quantum_flux*ψ[k-1] - temporal_echo*ψ[k-2]^2 + control_resonance*impulse_current + chaos_factor*sin(impulse_previous)
            resonance_states[i] = quantum_flux * resonance_states[i - 1] - temporal_echo * pow(resonance_states[i - 2], 2) + control_resonance * impulse_current + chaos_factor * sin(impulse_previous);
        }
        return resonance_states; // Возврат хаотической траектории квантовой системы
    }

    // Метод для визуализации квантовых параметров системы
    void display_quantum_parameters() const
    {
        std::cout << "Quantum System Parameters: flux=" << quantum_flux << ", echo=" << temporal_echo
                  << ", resonance=" << control_resonance << ", chaos=" << chaos_factor << std::endl;
        std::cout << "Quantum States: phase_current=" << phase_current << ", phase_previous=" << phase_previous
                  << ", impulse_current=" << impulse_current << ", impulse_previous=" << impulse_previous << std::endl;
    }
};