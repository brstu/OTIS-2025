#ifndef LinearSystem_H
#define LinearSystem_H

class LinearSystem {
private:
    double a;
    double b;
    double u;

public:
    LinearSystem(double a_val, double b_val, double u_val)
        : a(a_val), b(b_val), u(u_val) {
    }

    double calculateNext(double y1) const;
};

#endif 

