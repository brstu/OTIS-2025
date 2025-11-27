#include "pid.h"

PID::PID(double K, double T, double Td, double T0)
    : K(K), T(T), Td(Td), T0(T0), prev_e(0), integral(0) {}

double PID::compute(double e) {
    integral += e * T0;
    double derivative = (e - prev_e) / T0;
    prev_e = e;
    return K * (e + integral / T + Td * derivative);
}
