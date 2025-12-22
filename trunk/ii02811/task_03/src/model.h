#ifndef MODEL_H
#define MODEL_H

/**
 * @class Model
 * @brief Модель объекта управления
 */
class Model {
private:
    double a;        
    double b;         
    double c;        
    double d;        
    
    double y_prev1;  
    double y_prev2;  
    double u_prev1;  
    double u_prev2;  
    
public:
    /**
     * @brief Конструктор модели
     * @param a_val Коэффициент a (по умолчанию 0.2)
     * @param b_val Коэффициент b (по умолчанию 0.3)
     * @param c_val Коэффициент c (по умолчанию 0.4)
     * @param d_val Коэффициент d (по умолчанию 0.5)
     */
    explicit Model(double a_val = 0.2, double b_val = 0.3, 
                   double c_val = 0.4, double d_val = 0.5);
    
    /**
     * @brief Инициализация начальных условий
     * @param y0 Начальное значение y[k-2]
     * @param y1 Начальное значение y[k-1]
     * @param u0 Начальное значение u[k-2]
     * @param u1 Начальное значение u[k-1]
     */
    void init(double y0, double y1, double u0, double u1);
    
    /**
     * @brief Линейная модель объекта
     * @param u Текущее управляющее воздействие
     * @return Текущее значение выхода
     */
    double linearModel(double u);
    
    /**
     * @brief Нелинейная модель объекта
     * @param u Текущее управляющее воздействие
     * @return Текущее значение выхода
     * @warning Включает ограничение выходных значений ±1000
     */
    double nonlinearModel(double u);
    
    /**
     * @brief Получение текущего значения выхода
     * @return Текущее значение y[k-1]
     */
    double getCurrentValue() const { return y_prev1; }
    
    /**
     * @brief Установка текущего значения выхода
     * @param value Новое значение
     */
    void setCurrentValue(double value) { y_prev1 = value; }
};

#endif