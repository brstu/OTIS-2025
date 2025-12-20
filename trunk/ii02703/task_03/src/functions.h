#pragma once
#include <vector>
#include <string>


/* ===== ПАРАМЕТРЫ ОБЪЕКТА ===== */
const double A = 0.85;
const double B = 0.0;
const double C = 0.9;
const double D = -0.4;

/* ===== ПАРАМЕТРЫ ПИД ===== */
const double Kp = 0.01;
const double Ts = 1.0;
const double Td = 10.0;
const double Ti = 0.5;

/* ===== КОЭФФИЦИЕНТЫ ПИД ===== */
const double Q0 = Kp * (1.0 + Td / Ts);
const double Q1 = -Kp * (1.0 + 2.0 * Td / Ts - Ts / Ti);
const double Q2 = Kp * Td / Ts;

double linearPlant(double y, double u);
double nonlinearPlant(double y, double u, double y_prev, double u_prev);
std::vector<double> runSimulation(double setpoint, int steps);
void saveToCSV(const std::string& filename,
               const std::vector<double>& data);