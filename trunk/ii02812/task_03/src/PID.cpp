/**
 * @file PID.cpp
<<<<<<< HEAD
 * @brief Ðåàëèçàöèÿ äèñêðåòíîãî PID-ðåãóëÿòîðà.
=======
 * @brief Ð ÐµÐ°Ð»Ð¸Ð·Ð°Ñ†Ð¸Ñ Ð´Ð¸ÑÐºÑ€ÐµÑ‚Ð½Ð¾Ð³Ð¾ PID-Ñ€ÐµÐ³ÑƒÐ»ÑÑ‚Ð¾Ñ€Ð°.
>>>>>>> 235f543de1e891ea0b5921e2b58d0728432e8324
 */

#include "PID.h"
#include <iostream>

PID::PID(double in_K, double in_T, double in_T0, double in_Td) : 
	K(in_K), T(in_T), T0(in_T0), Td(in_Td), valid(true) {
	q0 = K * (1.0 + Td / T0);
	q1 = -K * (1 + 2 * Td / T0 - T0 / T);
	q2 = K * Td / T0;
}


double PID::u_calc(double e) {
	if (valid) {
		double delta_u = q0 * e + q1 * e_prev_1 + q2 * e_prev_2;
		double u = u_prev + delta_u;
		u_prev = u;
		e_prev_2 = e_prev_1;
		e_prev_1 = e;
		return u;
	}
	std::cout << "Not valid value of 'q' !\n";
	return 0.0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 235f543de1e891ea0b5921e2b58d0728432e8324
