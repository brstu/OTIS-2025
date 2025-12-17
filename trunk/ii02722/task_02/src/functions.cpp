#include <cmath>
#include <vector>
#include "functions.h"

// Параметры системы
const double alpha_param = 0.9;
const double beta_param = 0.1;
const double gamma_param = 0.05;
const double delta_param = 0.02;

// Функция моделирования линейной динамической системы
std::vector<double> linearSystemSimulator(int iterationCount, 
                                         double initialState, 
                                         const std::vector<double>& externalInputs) {
    // Проверка некорректных условий
    if (iterationCount <= 0 || externalInputs.empty()) {
        return std::vector<double>();
    }
    
    // Обработка частного случая одного шага
    if (iterationCount == 1) {
        return std::vector<double>(1, initialState);
    }

    // Проверка достаточности входных данных
    if (externalInputs.size() < static_cast<size_t>(iterationCount - 1)) {
        return std::vector<double>();
    }

    // Инициализация вектора результатов
    std::vector<double> systemResponse(iterationCount);
    systemResponse[0] = initialState;

    // Основной цикл моделирования
    for (int currentStep = 1; currentStep < iterationCount; ++currentStep) {
        systemResponse[currentStep] = alpha_param * systemResponse[currentStep - 1] + 
                                     beta_param * externalInputs[currentStep - 1];
    }

    return systemResponse;
}

// Функция моделирования нелинейной динамической системы
std::vector<double> nonlinearSystemSimulator(int iterationCount, 
                                            double initialState, 
                                            const std::vector<double>& externalInputs) {
    // Проверка нулевого количества итераций
    if (iterationCount == 0) {
        return std::vector<double>();
    }
    
    // Обработка частного случая одного шага
    if (iterationCount == 1) {
        return std::vector<double>(1, initialState);
    }

    // Инициализация вектора результатов
    std::vector<double> systemResponse(iterationCount);
    systemResponse[0] = initialState;
    
    // Вычисление первого шага (линейный случай)
    systemResponse[1] = alpha_param * systemResponse[0] + beta_param * externalInputs[0];

    // Основной цикл моделирования с нелинейными эффектами
    for (int currentStep = 2; currentStep < iterationCount; ++currentStep) {
        double quadraticTerm = beta_param * std::pow(systemResponse[currentStep - 2], 2);
        double sinusoidalTerm = delta_param * std::sin(externalInputs[currentStep - 2]);
        
        systemResponse[currentStep] = alpha_param * systemResponse[currentStep - 1] - 
                                     quadraticTerm + 
                                     gamma_param * externalInputs[currentStep - 1] + 
                                     sinusoidalTerm;
    }

    return systemResponse;
}