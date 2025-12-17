#ifndef MODEL_H
#define MODEL_H

#include <stdexcept>
#include <cmath>

class LinearModel {
private:
    double a;
    double b;
    double y_prev;
    
public:
    LinearModel(double a, double b, double initial_y);
    double calculate(double u);
    
    // Методы для тестирования (ДОБАВЛЕНО)
    double getPreviousY() const { return y_prev; }
    void reset(double initial_y) { y_prev = initial_y; }
};

class NonlinearModel {
private:
    double a;
    double b;
    double c;
    double d;
    double y_prev;
    double y_prev_prev;
    
public:
    NonlinearModel(double a, double b, double c, double d, double initial_y);
    double calculate(double u);
    
    // Методы для тестирования (ДОБАВЛЕНО)
    double getPreviousY() const { return y_prev; }
    double getPreviousPreviousY() const { return y_prev_prev; }
    void reset(double initial_y) { 
        y_prev = initial_y; 
        y_prev_prev = initial_y;
    }
};

#endif
