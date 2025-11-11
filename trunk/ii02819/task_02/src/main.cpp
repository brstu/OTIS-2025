#include <iostream>
#include "models.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    double signalInput, startValue;
    cout << "Введите входной сигнал и начальное значение:" << endl;
    cin >> signalInput >> startValue;

    double alphaParam, betaParam, gammaParam, deltaParam;
    cout << "Введите параметры alpha, beta, gamma, delta: " << endl;
    cin >> alphaParam >> betaParam >> gammaParam >> deltaParam;

    int stepsCount;
    cout << "Введите количество итераций: " << endl;
    cin >> stepsCount;

    double linearState = startValue;
    double nonlinearState = startValue;

    for (int step = 0; step < stepsCount; step++) {
        linearState = computeLinear(linearState, signalInput, alphaParam, betaParam);
        nonlinearState = computeNonlinear(nonlinearState, signalInput,
                                          alphaParam, betaParam, gammaParam, deltaParam);

        cout << "Итерация " << step + 1 << " - Линейная модель: " << linearState << endl;
        cout << "Итерация " << step + 1 << " - Нелинейная модель: " << nonlinearState << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}

