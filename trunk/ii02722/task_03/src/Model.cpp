#include "Model.h"
#include <iostream>

void Model::find_e() {
	e_past2 = e_past;
	e_past = e;
	e = target - y;
}
void Model::find_u(const Qs& q) {
	if (y > target) {
		condition = true;
	}
	u_d = q.q0 * e + q.q1 * e_past + q.q2 * e_past2;
	if (condition) {
		u_d = -15.0;
		condition = false;
	}
	u_next = u + u_d;
	std::cout << "U = " << u << std::endl;
	u = u_next;

}
void Model::lin(const Const_& c) {
	std::cout << "Y = " << y << std::endl;
	y_next = c.a * y + c.b * u_next;
	y = y_next;

}
void PID_model(const Qs& q, const Const_& c) {
	double s;
	double t;
	double n;
	std::cout << "Enter start temp: " << std::endl;
	std::cin >> s;
	std::cout << "Enter target temp: " << std::endl;
	std::cin >> t;
	std::cout << "Enter amout of iterations: " << std::endl;
	std::cin >> n;
	Model m(s, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, t, 300, false);
	for (int i = 0; i < n; i++) {
		std::cout << "Iteration " << i << std::endl;
		m.find_e();
		m.find_u(q);
		m.lin(c);
	}
}
void find_Qs(Qs& q, const Const_& c) {
	q.q0 = c.k * (1 + c.Td / c.To);
	q.q1 = -c.k * (1 + (2 * (c.Td / c.To)) - (c.To / c.T));
	q.q2 = c.k * (c.Td / c.To);
}