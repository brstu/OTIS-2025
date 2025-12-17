// Файл объявлений функций моделирования динамических систем
#ifndef SYSTEM_SIMULATORS_H
#define SYSTEM_SIMULATORS_H

#include <vector>

// Симулятор линейной системы первого порядка
std::vector<double> linearSystemSimulator(int iterationCount, 
                                         double initialState, 
                                         const std::vector<double>& externalInputs);

// Симулятор нелинейной системы с памятью
std::vector<double> nonlinearSystemSimulator(int iterationCount, 
                                            double initialState, 
                                            const std::vector<double>& externalInputs);

#endif // SYSTEM_SIMULATORS_H