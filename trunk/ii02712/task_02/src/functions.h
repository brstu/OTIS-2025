#pragma once

const double a = -0.1;
const double b = 0.5;
const double c = -0.2;
const double d = 0.4;

double linearModel(double y, double u);
double nonlinearModel(double y, double u, double y_pred, double u_pred);