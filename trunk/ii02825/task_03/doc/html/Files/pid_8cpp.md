---
title: src/pid.cpp
summary: Реализация методов PID-регулятора. 

---

# src/pid.cpp

Реализация методов PID-регулятора. 




## Source code

```cpp


#include "pid.h"

PID::PID(double K_, double T_, double Td_, double T0_)
    : K(K_), T(T_), Td(Td_), T0(T0_)
{
    q0 = K * (1.0 + Td / T0);
    q1 = -K * (1.0 + 2.0 * Td / T0 - T0 / T);
    q2 = K * (Td / T0);
}

double PID::compute(double e)
{
    double du = q0 * e + q1 * e_prev1 + q2 * e_prev2;
    double u = u_prev + du;

    u_prev = u;
    e_prev2 = e_prev1;
    e_prev1 = e;

    return u;
}
```


-------------------------------

Updated on 2025-11-26 at 11:50:51 +0300
