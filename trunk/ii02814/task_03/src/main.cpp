/**
 * @file main.cpp
 * @brief Главный файл программы с ПИД-регулятором для управления температурой
 * @author Козловский Е.Ю. ИИ-28
 * @date 2025
 * 
 * @mainpage Документация ПИД-регулятора
 * 
 * @section intro Введение
 * Программа реализует ПИД-регулятор для управления нелинейным объектом (температурой).
 * Используется дискретная форма ПИД-регулятора и нелинейная модель объекта.
 * 
 * @section algorithm Алгоритм работы
 * 1. Ввод параметров модели объекта и ПИД-регулятора
 * 2. Расчет коэффициентов ПИД-регулятора в дискретной форме
 * 3. Циклическое моделирование системы управления
 * 4. Расчет ошибки, управляющего воздействия и новой температуры
 * 5. Вывод результатов моделирования
 */
#include <iostream>
#include <iomanip>
#include <array>
#include "module.h"

/**
 * @brief Основная функция программы
 * @return Код завершения программы
 * 
 * Функция выполняет моделирование системы управления с ПИД-регулятором.
 * Последовательность работы:
 * - Ввод параметров модели и регулятора
 * - Инициализация переменных состояния
 * - Расчет коэффициентов ПИД-регулятора
 * - Цикл моделирования на 50 шагов
 * - Вывод промежуточных результатов
 * 
 * @note Используется нелинейная модель объекта: 
 *       y(k) = a*y(k-1) - b*y(k-2)^2 + c*u(k-1) + d*sin(u(k-2))
 */
int main() {
    // === 1. Ввод параметров модели объекта (из 1 лабы) ===
    /// @brief Параметры нелинейной модели объекта a, b, c, d
    double a;
    double b;
    double c;
    double d;
    std::cout << "Parameters for modeling a,b,c,d: ";
    std::cin >> a >> b >> c >> d;

    // === 2. Ввод начальных условий ===
    /// @brief Начальные значения температуры y[0] и y[1]
    double y0;
    double y1;
    std::cout << "Nachalnie uslovia y[0], y[1]: ";
    std::cin >> y0 >> y1;

    // === 3. Ввод параметров ПИД-регулятора ===
    /// @brief Параметры ПИД-регулятора: K - коэффициент усиления, T - постоянная времени, Td - постоянная времени дифференцирования
    double K;
    double T;
    double Td;
    std::cout << "Parameters PID K,T,Td: ";
    std::cin >> K >> T >> Td;

    // === 4. Ввод желаемой температуры ===
    /// @brief Заданное значение температуры (уставка)
    double setpoint;
    std::cout << "Zelaemaya temperatura: ";
    std::cin >> setpoint;

    // === 5. Инициализация переменных ===
    /// @brief Массив температур: y[0], y[1], y[2] - история температур (y(k), y(k-1), y(k-2))
    std::array<double, 3> y = { y0, y1 };
    /// @brief Массив управлений: u[0], u[1] - история управляющих воздействий (u(k), u(k-1))
    std::array<double, 2> u = { 0, 0 };

    /// @brief Предыдущее управляющее воздействие u(k-1)
    double u_prev = 0;
    /// @brief Предыдущая ошибка регулирования e(k-1)
    double e_prev = 0;
    /// @brief Предпредыдущая ошибка регулирования e(k-2)
    double e_prev2 = 0;
    /// @brief Шаг квантования (время дискретизации)
    double T0 = 1.0;

    // === 6. Вычисление коэффициентов ПИД ===
    /// @brief Коэффициенты ПИД-регулятора в дискретной форме
    double q0;
    double q1;
    double q2;
    calculatePidCoefficients(K, T, Td, T0, q0, q1, q2);

    std::cout << "Koeficienti PID: q0=" << q0 << ", q1=" << q1 << ", q2=" << q2 << std::endl;

    // === 7. Основной цикл моделирования ===
    /// @brief Основной цикл моделирования системы управления на 50 шагов
    std::cout << "\nStart modeling...\n";

    for (int k = 1; k <= 500; k++) {
        // Расчет ошибки
        /// @brief Текущая ошибка регулирования e(k) = setpoint - y(k-1)
        double e_k = calculateError(setpoint, y[1]);

        // Расчет управления
        /// @brief Управляющее воздействие u(k) = u(k-1) + q0*e(k) + q1*e(k-1) + q2*e(k-2)
        ControlParams controlParams = {q0, q1, q2, e_k, e_prev, e_prev2, u_prev};
        u[1] = calculateControl(controlParams);

        // Расчет новой температуры
        /// @brief Новая температура по нелинейной модели y(k) = a*y(k-1) - b*y(k-2)^2 + c*u(k-1) + d*sin(u(k-2))
        ModelParams modelParams = {a, b, c, d, y[1], y[0], u[1], u[0]};
        y[2] = calculateNonlinearModel(modelParams);

        // Вывод в консоль
        /// @brief Вывод результатов каждые 10 шагов для мониторинга
        if (k % 10 == 0) {
            std::cout << "Shag " << k << ": Temperatura = " << std::fixed << std::setprecision(4) << y[1]
                << ", Upravlenie = " << u[1]
                << ", Oshibka = " << e_k << std::endl;
        }

        // Обновление переменных состояния
        /// @brief Обновление истории температур, управлений и ошибок для следующего шага
        StateVariables state = {y, u, e_prev, e_prev2, u_prev, e_k};
        updateStateVariables(state);
        y = state.y;
        u = state.u;
        e_prev = state.e_prev;
        e_prev2 = state.e_prev2;
        u_prev = state.u_prev;
    }

    std::cout << "\nModelirovanie zaversheno!" << std::endl;
    return 0;
}