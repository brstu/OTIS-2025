#pragma once

#include <iostream>
#include <cmath>

const double first_funct_const = 0.1;
const double second_funct_const = 0.2;
const double third_funct_const = 0.3;
const double LINEAR_COEFFICIENT_A = 0.1;
const double LINEAR_COEFFICIENT_B = 0.2;
const double LINEAR_COEFFICIENT_C = 0.3;
void nonliner_funct(double& y2, double& y_previous, bool& second_iteration);
/**
 * @brief Applies a linear transformation to the input value.
 *
 * This function modifies the value of y1 by applying a linear function,
 * typically using a predefined constant.
 *
 * @param y1 Reference to a double value to be transformed.
 */
void liner_funcnt(double& y1);
/**
 * @brief Applies a nonlinear transformation to the input value.
 *
 * This function modifies y2 based on its previous value (y_previous) and
 * whether it is the second iteration. The transformation may involve
 * nonlinear operations such as exponentiation or trigonometric functions.
 *
 * @param y2 Reference to a double value to be transformed.
 * @param y_previous Reference to the previous value of y2.
 * @param second_iteration Reference to a boolean indicating if this is the second iteration.
 */