#include <cmath>

class ModelState {
private:
    inline static double K_obj = 1.0;
    inline static double T_obj = 0.5;
    inline static double y_prev = 0.0;

public:
    static void init(double K, double T) {
        K_obj = K;
        T_obj = T;
        y_prev = 0.0;
    }

    static double update(double u, double dt) {
        double a = 0.0;
        double b = 0.0;

        if (T_obj > 0.0) {
            a = 1.0 - dt / T_obj;
            b = K_obj * dt / T_obj;
        }
        else {
            a = 0.0;
            b = K_obj;
        }

        const double y = a * y_prev + b * u;
        y_prev = y;

        return y;
    }

    static void reset() {
        y_prev = 0.0;
    }

    static void setParameters(double K, double T) {
        K_obj = K;
        T_obj = T;
        reset();
    }
};


void modelInit(double K, double T) {
    ModelState::init(K, T);
}

double modelUpdate(double u, double dt) {
    return ModelState::update(u, dt);
}

void modelReset() {
    ModelState::reset();
}

void modelSetParameters(double K, double T) {
    ModelState::setParameters(K, T);
}