#include <iostream>
#include <cmath>

using namespace std;

double computeLinear(double state, double signal, double factorA, double factorB);
double computeNonlinear(double state, double signal, double factorA, double factorB, double factorC, double factorD);

int main()
{
    setlocale(LC_ALL, "RU");

    double signalInput;
    double startValue;
    cout << "Введите входной сигнал и начальное значение:" << endl;
    cin >> signalInput >> startValue;

    double alphaParam;
    double betaParam;
    double gammaParam;
    double deltaParam;
    cout << "Введите параметры alpha, beta, gamma, delta: " << endl;
    cin >> alphaParam >> betaParam >> gammaParam >> deltaParam;

    int stepsCount;
    cout << "Введите количество итераций: " << endl;
    cin >> stepsCount;

    double linearState = startValue;
    double nonlinearState = startValue;

    for (int step = 0; step < stepsCount; step++)
    {
        linearState = computeLinear(linearState, signalInput, alphaParam, betaParam);
        nonlinearState = computeNonlinear(nonlinearState, signalInput, alphaParam, betaParam, gammaParam, deltaParam);

        cout << "Итерация " << step + 1 << " - Линейная модель: " << linearState << endl;
        cout << "Итерация " << step + 1 << " - Нелинейная модель: " << nonlinearState << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}

double computeLinear(double state, double signal, double factorA, double factorB)
{
    return factorA * state + factorB * signal;
}

double computeNonlinear(double state, double signal, double factorA, double factorB, double factorC, double factorD)
{
    double quadraticPart = factorB * state * state;
    double sinusPart = factorD * sin(signal);
    return factorA * state - quadraticPart + factorC * signal + sinusPart;
}
