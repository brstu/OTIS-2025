<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Моделирование температуры объекта"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Степанюк И.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

## Задание
Написать программу на C++, моделирующую температуру объекта управления.

Линейная модель:
$$y_{\tau+1} = a \cdot y_{\tau} + b \cdot u_{\tau}$$

Нелинейная модель:
$$y_{\tau+1} = a \cdot y_{\tau} - b \cdot y_{\tau-1}^2 + c \cdot u_{\tau} + d \cdot \sin(u_{\tau-1})$$

## Код программы
```cpp
#include <iostream>
#include <cmath>
#include <vector>

class TempSimulator {
    double coefA, coefB, coefC, coefD;
    double prevY, prevPrevY, prevU;

public:
    TempSimulator(double a, double b, double c, double d, double startTemp)
        : coefA(a), coefB(b), coefC(c), coefD(d), 
          prevY(startTemp), prevPrevY(startTemp), prevU(0) {}

    double computeLinear(double u) {
        prevY = coefA * prevY + coefB * u;
        return prevY;
    }

    double computeNonLinear(double u) {
        double result = coefA * prevY - coefB * prevPrevY * prevPrevY 
                      + coefC * u + coefD * std::sin(prevU);
        prevPrevY = prevY;
        prevY = result;
        prevU = u;
        return result;
    }
};

int main() {
    const double A = 0.8, B_LIN = 0.3, B_NLIN = 0.01;
    const double C = 0.4, D = 0.1, START_TEMP = 20.0;
    
    std::vector<double> inputs = {2.0, 3.0, 4.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.5, 0.0};
    
    TempSimulator linSim(A, B_LIN, 0, 0, START_TEMP);
    TempSimulator nlinSim(A, B_NLIN, C, D, START_TEMP);
    
    std::cout << "Step\tLinear\tNonLinear\n";
    
    for (size_t i = 0; i < inputs.size(); ++i) {
        double lin = linSim.computeLinear(inputs[i]);
        double nlin = nlinSim.computeNonLinear(inputs[i]);
        std::cout << i << "\t" << lin << "\t" << nlin << "\n";
    }
    
    return 0;
}
```

## Результаты
Программа выводит значения температуры для линейной и нелинейной моделей на каждом шаге моделирования.

