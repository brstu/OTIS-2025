<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирования температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Каневега К. А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# ЗАДАНИЕ #

1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (pull request) разместить его в следующем каталоге: trunk\ii0xxyy\task_01\doc (где xx - номер группы, yy - номер студента, например ii02302).
2. Исходный код написанной программы разместить в каталоге: trunk\ii0xxyy\task_01\src.

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

---

# ВЫПОЛНЕНИЕ ЗАДАНИЯ #

Код программы:
```C++
#include <iostream>;
#include <cmath>;

using namespace std;

void Linemodel(float y, float u, float t, float a, float b, int i) {
    if (i <= t) {
        Linemodel(a * y + b * u, u, t, a, b, i + 1);
        cout << "y" << i << " = " << y << endl;
    }
    else cout << "end_Linemodel\n";
}

void UnLinemodel(float a, float b, float c, float d, float y, float y0, float u, int i, float t) {
    if (i <= t) {
        float y_next = a * y - b * y0 * y0 + c * u + d * sin(u);

        UnLinemodel(a, b, c, d, y_next, y, u, i + 1, t);

        cout << "y" << i << " = " << y << endl;
    }
    else {
        cout << "end_UnLinemodel" << endl;
    }
}

int main() {
    cout << "Write constants(a,b,c,d,y,u,t):\n";
    float a, b, c, d, y, u, t;
    int i = 1;
    cin >> a >> b >> c >> d >> y >> u >> t;
    cout << "Linemodel: \n";
    Linemodel(y, u, t, a, b, i);
    cout << "UnLinemodel: \n";
    UnLinemodel(a, b, c, d, y, y, u, i, t);
}
```

Вывод программы:

Write constants(a,b,c,d,y,u,t):
1
1
2
2
5
6
3
Linemodel:
end_Linemodel
y3 = 17
y2 = 11
y1 = 5
UnLinemodel:
end_UnLinemodel
y3 = -22.1177
y2 = -8.55883
y1 = 5