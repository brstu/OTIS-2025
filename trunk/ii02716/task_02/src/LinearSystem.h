#ifndef LinearSystem_H
#define LinearSystem_H

class LinearSystem {
private:
    float a, b, u;

public:
    LinearSystem(float a_val, float b_val, float u_val)
        : a(a_val), b(b_val), u(u_val) {
    }

    float calculateNext(float y1) const;
};

#endif 

