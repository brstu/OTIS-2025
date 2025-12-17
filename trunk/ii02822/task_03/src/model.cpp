#include <cmath>

class ModelState {
private:
    static double& getK() {
        inline static double K_obj = 1.0;
        return K_obj;
    }

    static double& getT() {
        inline static double T_obj = 0.5;
        return T_obj;
    }

    static double& getYPrev() {
        inline static double y_prev = 0.0;
        return y_prev;
    }

public:
    static void init(double K, double T) {
        getK() = K;
        getT() = T;
        getYPrev() = 0.0;
    }

    static double update(double u, double dt) {
        double a = 0.0;
        double b = 0.0;

        if (getT() > 0.0) {
            a = 1.0 - dt / getT();
            b = getK() * dt / getT();
        }
        else {
            a = 0.0;
            b = getK();
        }

        const double y = a * getYPrev() + b * u;
        getYPrev() = y;

        return y;
    }

    static void reset() {
        getYPrev() = 0.0;
    }

    static void setParameters(double K, double T) {
        getK() = K;
        getT() = T;
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