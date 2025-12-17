---
title: src/pid.h

---

# src/pid.h



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[PID](Classes/class_p_i_d.md)** <br>Класс дискретного ПИД-регулятора.  |




## Source code

```cpp

class PID {
private:
    double K;      
    double T;      
    double Td;     
    double T0;     

    double q0;     
    double q1;     
    double q2;     

    double u_prev; 
    double e_prev1;
    double e_prev2;

public:
    PID(double K_, double T_, double Td_, double T0_);

    double compute(double e);
};
```


-------------------------------

Updated on 2025-11-26 at 11:50:51 +0300
