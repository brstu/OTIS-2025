#ifndef NonLinearSystem_H
#define NonLinearSystem_H
#include <cmath>

class NonlinearSystem {
private:
    float a;
    float b; 
    float c;
    float d;
    float u;

public:
    NonlinearSystem(float a_val, float b_val, float c_val,
        float d_val, float u_val)
        : a(a_val), b(b_val), c(c_val), d(d_val), u(u_val) {
    }

    double calculateNext(float y1, float y0) const;
};


#endif 
