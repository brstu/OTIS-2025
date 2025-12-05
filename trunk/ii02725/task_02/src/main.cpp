#include <iostream>
#include <vector>
#include <cmath>
#include <locale>
#include "module.h"

int main()
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    int steps_count;
    
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> steps_count;
    
    bool invalid_count = steps_count >= 100;

    if (bool negative_count = steps_count < 0; invalid_count || negative_count)
    {
        std::cout << "Ошибка: N должно быть в диапазоне 0 <= N < 100\n";
        return 1;
    }

    double parameter_a;
    
    double parameter_b;
    
    double parameter_c;
    
    double parameter_d;
    
    std::cout << "Введите константы a, b, c, d через пробел: ";
    std::cin >> parameter_a;
    std::cin >> parameter_b;
    std::cin >> parameter_c;
    std::cin >> parameter_d;

    std::vector<double> input_values(steps_count);
    
    if (steps_count > 0)
    {
        std::cout << "Введите значения u(t) для t = 0." << steps_count - 1 << ":\n"; 
        
        for (int current_time = 0; current_time < steps_count; ++current_time)
        {
            std::cout << "u[" << current_time << "] = ";
            std::cin >> input_values[current_time];
        }
    }

    std::vector<double> linear_output(steps_count + 1, 0.0);
    
    std::vector<double> nonlinear_output(steps_count + 1, 0.0);

    if (steps_count > 0)
    {
        std::cout << "Введите начальную температуру y[0]: ";
        std::cin >> linear_output[0];
        nonlinear_output[0] = linear_output[0];
    }

    if (bool need_second_value = steps_count > 1; need_second_value)
    {
        std::cout << "Введите y[1] для нелинейной модели: ";
        std::cin >> nonlinear_output[1];
    }

    if (steps_count > 0)
    {
        calculate_linear_model(steps_count, parameter_a, parameter_b, input_values, linear_output);
        
        if (bool calculate_nonlinear = steps_count > 1; calculate_nonlinear)
        {
            calculate_nonlinear_model(steps_count, parameter_a, parameter_b, parameter_c, parameter_d, input_values, nonlinear_output);
        }
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t\ty_lin\ty_nl\n";
    
    for (int output_time = 0; output_time <= steps_count; ++output_time)
    {
        std::cout << output_time << "\t" << linear_output[output_time] << "\t" << nonlinear_output[output_time] << "\n";
    }

    return 0;
}