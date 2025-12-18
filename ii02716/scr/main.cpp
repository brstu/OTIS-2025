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
