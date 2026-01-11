#include "PID.h"
#include <iostream>
using namespace std;

PID::PID() {
    temp.resize(500, 0);
    err.resize(500, 0);
    ctrl.resize(500, 0);
    d_ctrl.resize(500, 0);
    cout << "Enter start temp" << endl;
    cin >> temp[0];
    cout << "Enter max temp" << endl;
    cin >> limit;
    cout << "Enter needed temp" << endl;
    cin >> target;
    setup();
}

void PID::setup() {
    a = 0.85;
    b = 0.05;
    Kp = 1.5;
    Ts = 1.3;
    Td = 1.3;
    Ti = 1.5;
    q0 = 0;
    q1 = 0;
    q2 = 0;
    ctrl[0] = 0;
    d_ctrl[0] = 0;
    d_ctrl[1] = 0;
    err[0] = 0;
    err[1] = 0;
}

void PID::calcErr(int idx) {
    err[idx] = target - temp[idx];
}

void PID::calcQs() {
    q0 = Kp * (1 + Td / Ts);
    q1 = -Kp * (1 + 2 * (Td / Ts) - Ts / Ti);
    q2 = Kp * Td / Ts;
}

void PID::getQs(double& r0, double& r1, double& r2) const {
    r0 = q0;
    r1 = q1;
    r2 = q2;
}

void PID::calcCtrl(int idx) {
    if (idx >= 2) {
        d_ctrl[idx] = q0 * err[idx] + q1 * err[idx - 1] + q2 * err[idx - 2];
    }
    ctrl[idx + 1] = ctrl[idx] + d_ctrl[idx];
}

void PID::modelPlant(int idx) {
    temp[idx + 1] = a * temp[idx] + b * ctrl[idx];
}

void PID::simulate() {
    calcQs();
    for (int i = 0; i < 200; i++) {
        cout << "Step " << i + 1 << endl;
        calcErr(i);
        cout << "Error: " << err[i] << endl;
        calcCtrl(i);
        modelPlant(i);
        cout << "Temperature: " << temp[i] << endl;
        if (temp[i] > target) {
            d_ctrl[i] = 10.0;
        }
        if (temp[i] > limit) {
            cout << "Max temp reached" << endl;
            break;
        }
        cout << "########################" << endl;
    }
}