/// @file models.h
/// @brief Линейная и нелинейная функции

/**
 * @brief Линейная функция
 * @param y текущее состояние
 * @param u количество тепла
 * @param a коэффициент 
 * @param b коэффициент 
 * @return новое состояние
 */
double linear_model(double y, double u, double a, double b);

/**
 * @brief Нелинейная модель объекта
 * @param y текущее состояние
 * @param y_prev предыдущее состояние
 * @param u количество тепла
 * @param u_prev предыдущее количество тепла
 * @param a коэффициент 
 * @param b коэффициент 
 * @param c коэффициент
 * @param d коэффициент 
 * @return новое состояние
 */
double non_linear_model(double y, double& y_prev, double u, double& u_prev,
                        double a, double b, double c, double d);

