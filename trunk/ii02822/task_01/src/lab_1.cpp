#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    double u, y, a, b, c, d;
    int count_steps;

    cout << "������� u(�������� �������) � y(�������� �����������): " << endl;
    cin >> u >> y;
    cout << "������� ��������� a, b, c, d: " << endl;
    cin >> a >> b >> c >> d;
    cout << "������� ���������� �����: " << endl;
    cin >> count_steps;
    double yl = y, ynl = y;
    for (int i = 0; i < count_steps; i++)
    {
        yl = a * yl + b * u;
        ynl = a * ynl - b * ynl * ynl + c * u + d * sin(u);
        cout << "��������� " << i + 1 << " ���� �������� �������: " << yl << ";\n";
        cout << "��������� " << i + 1 << " ���� ���������� �������: " << ynl << ";\n";
    }
    return 0;
}