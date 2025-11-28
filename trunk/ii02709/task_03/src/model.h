#ifndef MODEL_H
#define MODEL_H

class Model {
    double a{0.1};
    double b{1.0};
    double T_room{0.0};
    double dt{0.1};
    double T{0.0};

public:
    explicit Model(double aa = 0.1, double bb = 1.0, double t_room = 0.0, double dtt = 0.1);

    double update(double u);
    double getTemperature() const { return T; }
    void reset(double val = 0.0) { T = val; }
};

#endif