#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    setlocale(LC_ALL, "Russian");

    const int steps = 10;
    std::vector<double> y(steps);
    std::vector<double> u(steps);
    double a, b, c, d;

    std::cout << "������� �� �������� ������\n";
    std::cout << "������� ����������� a: ";
    std::cin >> a;
    std::cout << "������� ����������� b: ";
    std::cin >> b;
    std::cout << "������� ��������� ����������� ������� y(0): ";
    std::cin >> y[0];
    std::cout << "������� ��������� ����������� ������� u(0): ";
    std::cin >> u[0];

    for (int i = 1; i < steps; i++)
    {
        y[i] = a * y[i - 1] + b * u[i - 1];
        u[i] = u[i - 1] * 0.8;
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }

    std::cout << "������� �� ���������� ������\n";
    std::cout << "������� ����������� a: ";
    std::cin >> a;
    std::cout << "������� ����������� b: ";
    std::cin >> b;
    std::cout << "������� ����������� c: ";
    std::cin >> c;
    std::cout << "������� ����������� d: ";
    std::cin >> d;
    std::cout << "������� ��������� ����������� ������� y(0): ";
    std::cin >> y[0];
    std::cout << "������� ��������� ����������� ������� y(1): ";
    std::cin >> y[1];
    std::cout << "������� ��������� ����������� ������� u: ";
    std::cin >> u[0];
    u[1] = u[0] * 0.8;

    for (int i = 1; i < steps - 1; i++)
    {
        y[i + 1] = a * y[i] - b * y[i - 1] / 2.0 + c * u[i] + d * sin(u[i - 1]);
        u[i + 1] = u[i] * 0.8;
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }
}

