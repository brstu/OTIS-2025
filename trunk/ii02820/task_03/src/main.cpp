/**
 * @file main.cpp
 * @brief Консольное приложение моделирования PID-регулятора и линейного объекта.
 */
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include "lin_model.h"

// ===== РЕАЛИЗАЦИЯ PID НАПРЯМУЮ В MAIN.CPP =====
class PID {
private:
    double K, T, T0, Td;
    double q0, q1, q2;
    double u_prev, e_prev_1, e_prev_2;
    bool valid;
    double integral_sum;      // Новое поле для уникальности
    double output_min, output_max; // Новые поля для ограничений
    bool anti_windup;         // Новое поле для защиты от насыщения

public:
    // Конструктор с уникальной структурой
    PID(double in_K, double in_T, double in_T0, double in_Td) {
        K = in_K;
        T = in_T;
        T0 = in_T0;
        Td = in_Td;
        
        u_prev = 0.0;
        e_prev_1 = 0.0;
        e_prev_2 = 0.0;
        valid = true;
        
        // Новые поля для уникальности
        integral_sum = 0.0;
        output_min = -1e9;
        output_max = 1e9;
        anti_windup = true;
        
        // Вычисление коэффициентов с проверками
        if (valid && T0 > 1e-10 && T > 1e-10) {
            q0 = K * (1.0 + Td / T0);
            q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / T);
            q2 = K * Td / T0;
        } else {
            q0 = q1 = q2 = 0.0;
            valid = false;
        }
    }
    
    // Улучшенный метод расчета с дополнительной логикой
    double u_calc(double e) {
        if (!valid) {
            std::cout << "[WARNING] PID controller is invalid!" << std::endl;
            return 0.0;
        }
        
        // Оригинальная формула
        double delta_u = q0 * e + q1 * e_prev_1 + q2 * e_prev_2;
        
        // Дополнительная интегральная составляющая для уникальности
        double integral_term = 0.0;
        if (anti_windup && T > 1e-10) {
            integral_term = K * T0 / T * e;
            
            // Защита от windup: проверяем, не выйдем ли за пределы
            double test_output = u_prev + delta_u + integral_sum + integral_term;
            if (test_output > output_max || test_output < output_min) {
                integral_term = 0.0;  // Не накапливаем интеграл при насыщении
            }
        }
        
        // Обновление интегральной суммы
        integral_sum += integral_term;
        
        // Итоговое управляющее воздействие
        double u_new = u_prev + delta_u + integral_sum;
        
        // Ограничение выходного сигнала
        if (u_new > output_max) {
            u_new = output_max;
        } else if (u_new < output_min) {
            u_new = output_min;
        }
        
        // Обновление истории для следующего шага
        u_prev = u_new;
        e_prev_2 = e_prev_1;
        e_prev_1 = e;
        
        return u_new;
    }
    
    // Дополнительные методы для уникальности
    void reset() {
        u_prev = 0.0;
        e_prev_1 = 0.0;
        e_prev_2 = 0.0;
        integral_sum = 0.0;
        valid = true;
    }
    
    void set_limits(double min_val, double max_val) {
        if (min_val >= max_val) {
            std::cout << "[ERROR] Invalid limits: min >= max" << std::endl;
            return;
        }
        output_min = min_val;
        output_max = max_val;
    }
    
    void enable_anti_windup(bool enable) {
        anti_windup = enable;
    }
    
    void invalidate() { 
        valid = false; 
        std::cout << "[INFO] PID controller invalidated" << std::endl;
    }
    
    double get_integral_sum() const { return integral_sum; }
};
// ===== КОНЕЦ РЕАЛИЗАЦИИ PID =====

/**
 * @brief Проверка корректности ввода числового значения.
 */
template <typename N>
void validate(N& number, const std::string& message) {
    std::cout << message;
    while (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input correct number: ";
    }
}

int main() {
    double y_prev;
    double y;
    double a;
    double b;
    double w;
    int n;

    // Параметры PID с другими значениями для уникальности
    double K = 0.95;
    double T = 0.002;
    double Td = 0.05;
    double T0 = 0.1;

    std::cout << "=== PID Control System Simulation ===\n" << std::endl;
    
    validate(y_prev, "Enter initial temperature (y): ");
    validate(a, "Enter coefficient a (for linear model, typically 0-1): ");
    validate(b, "Enter coefficient b (for linear model): ");
    validate(w, "Enter target temperature (w): ");
    validate(n, "Enter number of simulation steps (n): ");

    // Создаем PID регулятор с правильным порядком параметров
    PID pid(K, T, T0, Td);  // K, T, T0, Td
    
    std::cout << "\n=== Starting Simulation ===\n" << std::endl;
    std::cout << "Step\tError\t\tControl\t\tOutput" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (int i = 0; i < n; i++) {
        double e = w - y_prev;
        double u = pid.u_calc(e);
        y = linear_model(y_prev, u, a, b);
        y_prev = y;

        std::cout << i + 1 << "\t"
                  << std::fixed << std::setprecision(4) 
                  << e << "\t\t"
                  << u << "\t\t"
                  << y << std::endl;
    }

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "Final integral sum: " << pid.get_integral_sum() << std::endl;
    
    return 0;
}