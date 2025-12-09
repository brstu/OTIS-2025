#ifndef MODEL_H
#define MODEL_H

class Model {
private:
    double a, b, c, d;
    double y_prev1, y_prev2;
    double u_prev1, u_prev2;
    
public:
    Model(double a_val = 0.2, double b_val = 0.3, 
          double c_val = 0.4, double d_val = 0.5);
    
    void init(double y0, double y1, double u0, double u1);
    
    double linearModel(double u);
    
    double nonlinearModel(double u);
    
    double getCurrentValue() const { return y_prev1; }
    
    void setCurrentValue(double value) { y_prev1 = value; }
};

#endif