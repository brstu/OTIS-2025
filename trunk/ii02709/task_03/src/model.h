// src/model.h
#ifndef MODEL_H
#define MODEL_H

class Model {
    double a, b, T_room, dt;
    double T;  // текущая температура

public:
    Model(double aa = 0.1, double bb = 1.0, double t_room = 0.0, double dtt = 0.1);

    double update(double u);
    double getTemperature() const;
    void reset(double val = 0.0);
};

#endif