#include <iostream>
#include <vector>
#include "C:\Users\Boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\linaer.h"
#include "C:\Users\Boss\Desktop\OTIS-2025\trunk\ii02714\task_03\src\Class.h"


class PID : public Obj {
private:
    std::vector<double> e;
    std::vector<double> yP;
    std::vector<double> w;//целевое значение
    std::vector<double> u;
    std::vector<double> deltU;
    double Td;//постоянная дефф
    double To;//шаг по кванту
    double T;//шаг
    double q0;
    double q1;
    double q2;
    double k;//кэф передачи
    int iter;
public:
    PID() {
        this->iter = 10;
        this->T = 0.01;
        this->To = 0.01;
        this->k = 0.1;
        this->Td = 1;
        this->u[0] = 0;
        ++iter;
        e.resize(iter);
        yP.resize(iter);
        w.resize(iter);
        u.resize(iter);
        deltU.resize(iter);
        setE(0);
        setE(1);
        setE(2);
        Obj::input();
        SetQs();
        for (auto meanW : w) {
            std::cout << "Enter w:" << std::endl;
            std::cin >> meanW;
        }
    }
    void SetY(int place) {
        Obj::linear(place);
        this->yP[place] = getY(place);
    }
    void setE(int place) {
        e[place] = w[place] - yP[place];
    }
    void SetQs() {
        this->q0 = k * (1 + Td / To);
        this->q1 = -k * (1 + 2 * (Td / To) - To / T);
        this->q2 = k * (Td / To);
    }
    void SetU(int place) {
        int placeE = 0;
        if (place == 0 || place == 1) {
            placeE = 2;
        }
        if (place > 2) {
            setE(place);
        }
        deltU[place] = q0 * e[placeE] + q1 * e[placeE - 1] + q2 * e[placeE - 2];
        u[place] = u[place - 1] + deltU[place];
    }
    int iterGet() {
        --iter;
        return iter;
    }

};