#ifndef PID_H
#define PID_H 
#include <iostream>
#include <vector>
#include <cstdlib>
/**
 * \brief Класс для иметации PID регулятора
 * 
 */
class PID {
private:
	double q0;
	double q1;
	double q2;
	std::vector<double>deltU;
	std::vector<double>u;
	std::vector<double>y;
	std::vector<double>e;
	double w;
	double maxTemp;
	double k;
	double Td;
	double To;
	double T;
	double a;
	double b;
public:
	/**
	* \brief Конструктор для инцеализации переменных и векторов
	*/
	PID();
	/**
 * \brief Линейная функции имеющая вид: y[t] = a * y[t - 1] + b * u[t - 1]
 * \param place служит для определения температуры в определнный момент
 */
	void linear(int place);
	/**
  * \brief Функция для вычисления delta_u[place] delta_u переменная необходимая для вычисления U
  * \param place служит для определения температуры в определнный момент
  */
	void calcul_DeltU(int place);
	/**
* \brief Функция вычисления U
*  \param place служит для определения температуры в определнный момент
*/
	void calcul_U(int place);
	/**
* \brief Функция вычисления q0 q1 q2
* Переменные k, Td, To, T являются константами необходимыми для вычисления значений
*/
	void calcul_q0_q1_q2();
	/**
* \brief Функция вычисления ошибку e
*/
	void calcul_e(int place);
	/**
* \brief Основная функция иметирующая работу PID регулятора
*  \param place служит для определения температуры в определнный момент
*/
	void calcul_PID(int place);
	/**
* \brief Функция регулирующая значения констант а и b уменьшая их
* \param val значение на которое делится а
*  b делиться на 1.3
*/
	void RegCoefs(double val);
	/**
* \brief Функция для получения значений q0 q1 q2
* Вызывается в тестах для проверки работы программы
* \param val1 присваивает значение q0
* \param val2 присваивает значение q1
* \param val3 присваивает значение q2
*/
	void GetQs(double &val1,double &val2,double &val3) const;
};

#endif 

