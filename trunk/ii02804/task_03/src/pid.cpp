#include "pid.h"
#include <iostream>

PID::PID(double in_K, double in_T, double in_Td, double in_T0)
    : K(in_K),
      T(in_T),
      Td(in_Td),
      T0(in_T0),
      q0(K * (1.0 + Td / T0)),
      q1(-K * (1.0 + 2.0 * Td / T0 - T0 / T)),
      q2(K * Td / T0),
      u_prev(0.0),
      e_prev_1(0.0),
      e_prev_2(0.0),
      valid(true)
{
    
}

double PID::u_calc(double e) {
    if (valid) {
        double delta_u = q0 * e + q1 * e_prev_1 + q2 * e_prev_2;
        double u = u_prev + delta_u;

        u_prev = u;
        e_prev_2 = e_prev_1;
        e_prev_1 = e;

        return u;
    }

    std::cout << "Not valid value of 'q'!\n";
    return 0.0;
}
