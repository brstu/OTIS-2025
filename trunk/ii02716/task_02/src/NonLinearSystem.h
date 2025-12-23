#ifndef NonLinearSystem_H
#define NonLinearSystem_H
#include <cmath>

class NonlinearSystem {
private:
    double a;
    double b; 
    double c;
    double d;
    double u;

public:
    NonlinearSystem(double a_val, double b_val, double c_val,
        double d_val, double u_val)
        : a(a_val), b(b_val), c(c_val), d(d_val), u(u_val) {
    }

    double calculateNext(double y1, double y0) const;
};


#endif 
