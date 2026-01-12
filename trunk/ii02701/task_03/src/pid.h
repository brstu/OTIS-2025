#ifndef PID_H
#define PID_H

struct PID {
    double q0;      
    double q1;      
    double q2;       

    double u_prev;   
    double e_prev1;  
    double e_prev2;  
};

void initPID(PID& pid, double q0, double q1, double q2);

double updatePID(PID& pid, double e);

#endif