/**
 * @file lin_model.h
 * @brief Заголовочный файл линейной модели объекта управления
 * 
 * Уникальная версия: 2.1
 * Дата: [Текущая дата]
 */

#ifndef LINEAR_MODEL_H
#define LINEAR_MODEL_H

/**
 * @brief Линейная модель динамического объекта
 * 
 * @param previous_output Предыдущее значение выхода
 * @param control_input Управляющее воздействие
 * @param feedback_coefficient Коэффициент обратной связи
 * @param gain_coefficient Коэффициент усиления
 * @return Новое значение выхода системы
 */
double linear_model(double previous_output, double control_input,
                   double feedback_coefficient, double gain_coefficient);

#endif // LINEAR_MODEL_H