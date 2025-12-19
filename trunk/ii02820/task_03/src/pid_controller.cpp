#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PID {
private:
    double K, T, T0, Td;
    double q0, q1, q2;
    double u_prev, e_prev_1, e_prev_2;
    bool valid;
    double integral_sum;     // ЕДИНСТВЕННОЕ новое поле
    double output_min, output_max;
    bool anti_windup;

public:
    PID(double in_K, double in_T, double in_T0, double in_Td);
    double u_calc(double e);
    void reset();
    void set_limits(double min_val, double max_val);
    void enable_anti_windup(bool enable);
    void invalidate() { valid = false; }
    double get_integral_sum() const { return integral_sum; }
};

#endif