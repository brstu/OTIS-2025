<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Ничипорчик Д.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02302**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
3. Выполнить рецензирование ([review](https://linearb.io/blog/code-review-on-github), [checklist](https://linearb.io/blog/code-review-checklist)) запросов других студентов (минимум 2-е рецензии).
4. Отразить выполнение работы в файле readme.md в соответствующей строке (например, для студента под порядковым номером 1 - https://github.com/brstu/OTIS-2023/edit/main/readme.md?#L17-L17).

## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warmth; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.


## Код программы:
```C++
#include <iostream>
#include <cmath>

using namespace std;

// Константы системы
struct SystemConstants {
    const float a = 0.5f;
    const float b = 0.2f;
    const float c = 0.15f;
    const float d = 0.3f;
    const float u = 1.2f;
};

// Класс для линейной системы
class LinearSystem {
private:
    float a, b, u;
    
public:
    LinearSystem(float a_val, float b_val, float u_val) 
        : a(a_val), b(b_val), u(u_val) {}
    
    float calculateNext(float y1) {
        return a * y1 + b * u;
    }
};

// Класс для нелинейной системы
class NonlinearSystem {
private:
    float a, b, c, d, u;
    
public:
    NonlinearSystem(float a_val, float b_val, float c_val, 
                   float d_val, float u_val) 
        : a(a_val), b(b_val), c(c_val), d(d_val), u(u_val) {}
    
    float calculateNext(float y1, float y0) {
        return a * y1 - b * y0 * y0 + c * u + d * sin(u);
    }
};

// Функция для вывода результатов
void printResult(const string& title, int iteration, float value) {
    cout << title << " t" << iteration + 1 << " = " << value << endl;
}

// Основная функция симуляции
void simulateSystem(float initialY1, int iterations) {
    SystemConstants constants;
    
    // Инициализация систем
    LinearSystem linearSys(constants.a, constants.b, constants.u);
    NonlinearSystem nonlinearSys(constants.a, constants.b, 
                                constants.c, constants.d, constants.u);
    
    // Переменные для состояний
    float y0 = initialY1;
    float y1 = initialY1;
    float y2;
    
    // Линейная система
    cout << "\nLinear system simulation:" << endl;
    for (int i = 0; i < iterations; i++) {
        y2 = linearSys.calculateNext(y1);
        printResult("", i, y2);
        y0 = y1;
        y1 = y2;
    }
    
    // Сброс состояний для нелинейной системы
    y0 = initialY1;
    y1 = initialY1;
    
    // Нелинейная система
    cout << "\nNonlinear system simulation:" << endl;
    for (int i = 0; i < iterations; i++) {
        y2 = nonlinearSys.calculateNext(y1, y0);
        printResult("", i, y2);
        y0 = y1;
        y1 = y2;
    }
}

int main() {
    const int ITERATIONS = 10;
    float initialY1;
    
    // Ввод начального условия
    cout << "Enter initial value y1 = ";
    cin >> initialY1;
    
    // Запуск симуляции
    simulateSystem(initialY1, ITERATIONS);
    
    return 0;
}

```

## Результат программы:
y1 = ?
1

Linear
t1 = 1.3
t2 = 0.91
t3 = 0.757
t4 = 0.6785
t5 = 0.63925
t6 = 0.619625
t7 = 0.609812
t8 = 0.604906
t9 = 0.602453
t10 = 0.601227

Nonlinear
t1 = 1.3
t2 = 0.8775
t3 = 0.697019
t4 = 0.613212
t5 = 0.573222
t6 = 0.553837
t7 = 0.544073
t8 = 0.539191
t9 = 0.536751
t10 = 0.535531
