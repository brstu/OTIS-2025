/**
 * @file lab3main.cpp
 * @brief Главная программа для моделирования САУ с ПИД-регулятором
 * @author Степанюк Илья Сергеевич (ii02720)
 * @date 2025
 * 
 * Программа демонстрирует работу системы автоматического управления
 * с ПИД-регулятором на линейной и нелинейной моделях теплового объекта.
 * Лабораторная работа №3 по дисциплине ОТИС.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "pid.h"
#include "model.h"

/**
 * @brief Моделирует работу замкнутой САУ с ПИД-регулятором
 * @param pidRegulator Ссылка на объект ПИД-регулятора
 * @param thermalObject Ссылка на модель теплового объекта
 * @param targetValues Вектор заданных значений температуры
 * @param useNonlinearMode Флаг выбора нелинейной модели
 * @return Вектор выходных значений системы
 * 
 * Функция реализует цикл моделирования замкнутой системы управления,
 * где на каждом шаге вычисляется ошибка, управляющее воздействие
 * и новое значение выхода объекта управления.
 */
std::vector<double> runSimulation(PIDController& pidRegulator, ProcessModel& thermalObject, 
                                  const std::vector<double>& targetValues, bool useNonlinearMode = false) {
    std::vector<double> outputHistory;
    
    for (double targetTemp : targetValues) {
        // Получаем текущее значение выхода (или 0 в начале)
        double currentOutput = (outputHistory.empty()) ? 0.0 : outputHistory.back();
        
        // Рассчитываем управляющее воздействие через ПИД-регулятор
        double controlAction = pidRegulator.calculate(targetTemp, currentOutput);
        
        // Вычисляем новое значение выхода объекта
        double nextOutput;
        if (useNonlinearMode) {
            nextOutput = thermalObject.nonlinearModel(controlAction);
        } else {
            nextOutput = thermalObject.linearModel(controlAction);
        }
        
        outputHistory.push_back(nextOutput);
    }
    
    return outputHistory;
}

/**
 * @brief Точка входа в программу
 * @return Код возврата (0 при успешном выполнении)
 * 
 * Создает модель теплового объекта и ПИД-регулятор с заданными параметрами,
 * выполняет моделирование для линейного и нелинейного режимов,
 * выводит результаты в консоль.
 */
int main() {
    // Настройка локали для корректного вывода русских символов
    setlocale(LC_ALL, "");
    
    // Параметры модели теплового объекта [a, b, c, d]
    // a=0.87 - коэффициент инерции, b=0.012 - коэффициент входа (линейный)
    // c=0.17 - коэффициент входа (нелинейный), d=0.012 - амплитуда синусоиды
    std::vector<double> thermalParams = {0.87, 0.012, 0.17, 0.012};
    
    // Создание модели с начальной температурой 12°C
    ProcessModel thermalProcess(thermalParams, 12.0);
    
    // Параметры ПИД-регулятора (настроены для данного объекта)
    double Kp = 0.75;      // Пропорциональный коэффициент
    double Ti = 3.5;       // Постоянная интегрирования
    double Td_coef = 0.06; // Постоянная дифференцирования
    double Ts = 1.0;       // Период квантования (1 секунда)
    
    // Инициализация ПИД-регулятора
    PIDController pidController(Kp, Ti, Td_coef, Ts);
    
    // Формирование вектора заданий (желаемая температура 22°C)
    const int simulationSteps = 25;
    std::vector<double> temperatureSetpoints(simulationSteps, 22.0);
    
    // Моделирование с линейной моделью объекта
    auto linearSimResults = runSimulation(pidController, thermalProcess, temperatureSetpoints, false);
    
    // Сброс регулятора и модели для нового эксперимента
    pidController.reset();
    thermalProcess.setInitialValue(0.0);
    
    // Моделирование с нелинейной моделью объекта
    auto nonlinearSimResults = runSimulation(pidController, thermalProcess, temperatureSetpoints, true);
    
    // Вывод результатов в табличном формате
    std::cout << "=== Результаты моделирования САУ (Степанюк И.С., ii02720) ===" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Шаг\t\tЗадание\t\tЛинейная\tНелинейная\n";
    std::cout << "------------------------------------------------------------\n";
    
    for (size_t step = 0; step < temperatureSetpoints.size(); ++step) {
        std::cout << step << "\t\t" << temperatureSetpoints[step] << "\t\t" 
                << linearSimResults[step] << "\t\t" << nonlinearSimResults[step] << "\n";
    }
    
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Моделирование завершено успешно." << std::endl;
    
    return 0;
}
