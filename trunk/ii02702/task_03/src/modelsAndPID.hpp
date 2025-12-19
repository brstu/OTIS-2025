#pragma once
#include <vector>
#include <string>
#include "pid.hpp"


/**
 * @struct SimulationConfig
 * @brief Конфигурация симуляции
 */
struct SimulationConfig {
    std::string filename;     ///< Имя файла для сохранения результатов
    double initial_y = 20.0;  ///< Начальное значение выхода
    double initial_u = 0.0;   ///< Начальное управляющее воздействие
    int simulation_time = 100;///< Время симуляции (шаги)
    double setpoint = 25.0;   ///< Заданное значение (уставка)
};

/**
 * @struct NonlinearModelParams
 * @brief Параметры нелинейной модели
 */
struct NonlinearModelParams {
    double a = 0.85;   ///< Линейный коэффициент при y
    double b = 0.01;   ///< Коэффициент при квадрате предыдущего значения y
    double c = 0.25;   ///< Коэффициент при входном воздействии u
    double d = 0.05;   ///< Коэффициент при синусоидальном члене
};

/**
 * @brief Моделирование линейной системы первого порядка
 * @param y Начальное значение выходной переменной
 * @param u Входное воздействие (управляющий сигнал)
 * @param t Время симуляции (количество шагов)
 * @param a Коэффициент при предыдущем значении y
 * @param b Коэффициент при входном воздействии u
 * @return Вектор значений выходной переменной на каждом шаге
 */
std::vector<double> simulateLinearModel(double y, double u, int t, double a, double b);

/**
 * @brief Моделирование нелинейной системы
 * @param y Начальное значение выходной переменной
 * @param u Входное воздействие (управляющий сигнал)
 * @param t Время симуляции (количество шагов)
 * @param a Линейный коэффициент при y
 * @param b Коэффициент при квадрате предыдущего значения y (нелинейность)
 * @param c Коэффициент при входном воздействии u
 * @param d Коэффициент при синусоидальном члене
 * @return Вектор значений выходной переменной на каждом шаге
 */
std::vector<double> simulateNonLinearModel(double y, double u, int t, double a, double b, double c, double d);

/**
 * @brief Сохранение данных в CSV файл
 * @param filename Имя файла для сохранения
 * @param time Вектор временных меток
 * @param values Вектор значений
 * @param controls Вектор управляющих воздействий (опционально)
 * @param setpoint Заданное значение (уставка) (опционально)
 */
void saveToCSV(const std::string& filename, 
               const std::vector<int>& time,
               const std::vector<double>& values,
               const std::vector<double>& controls = {},
               double setpoint = 0.0);

/**
 * @brief Моделирование линейной системы без ПИД-регулятора
 * @param filename Имя файла для сохранения результатов
 * @param initial_y Начальное состояние системы
 * @param constant_u Постоянное входное воздействие
 * @param simulation_time Время симуляции
 * @param a Коэффициент при предыдущем значении y
 * @param b Коэффициент при входном воздействии u
 */
void simulateLinearSystemWithoutPID(const std::string& filename,
                                    double initial_y,
                                    double constant_u,
                                    int simulation_time,
                                    double a, double b);

/**
 * @brief Моделирование линейной системы с ПИД-регулятором
 * @param filename Имя файла для сохранения результатов
 * @param setpoint Заданное значение температуры
 * @param initial_y Начальное состояние системы
 * @param simulation_time Время симуляции
 * @param a Коэффициент при предыдущем значении y
 * @param b Коэффициент при входном воздействии u
 * @param pid ПИД-регулятор
 */
void simulateLinearSystemWithPID(const std::string& filename,
                                 double setpoint,
                                 double initial_y,
                                 int simulation_time,
                                 double a, double b,
                                 PIDController& pid);

/**
 * @brief Моделирование нелинейной системы без ПИД-регулятора
 * @param config Конфигурация симуляции
 * @param params Параметры нелинейной модели
 */
void simulateNonLinearSystemWithoutPID(const SimulationConfig& config,
                                       const NonlinearModelParams& params);

/**
 * @brief Моделирование нелинейной системы с ПИД-регулятором
 * @param config Конфигурация симуляции
 * @param params Параметры нелинейной модели
 * @param pid ПИД-регулятор
 */
void simulateNonLinearSystemWithPID(const SimulationConfig& config,
                                    const NonlinearModelParams& params,
                                    PIDController& pid);