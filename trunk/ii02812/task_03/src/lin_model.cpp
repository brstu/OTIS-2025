
/**
 * @file lin_model.cpp
 * @brief Реализация линейной динамической модели.
 */

#include "lin_model.h"

double linear_model(double y_prev, double u, double a, double b) {
	return a * y_prev + b * u;
}
