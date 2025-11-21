#include <iostream>
#include <vector>
#include "../src/linaer.h"
#include "../src/Class.h"
#include "../src/PID.h"

	PID::PID(double data, double data2) {
		this->iter = 10;
		e.resize(iter);
		yP.resize(iter);
		w.resize(iter);
		u.resize(iter);
		deltU.resize(iter);
		SetW(3, data);
		SetY(3, data2);
		this->T = 0.01;
		this->To = 0.01;
		this->k = 0.1;
		this->Td = 1;
		this->u[0] = 1;
		this->e[0] = 0;
		this->e[1] = 0;
		this->e[2] = 0;
	}
	PID::PID() {
		this->iter = 10;
		e.resize(iter);
		yP.resize(iter);
		w.resize(iter);
		u.resize(iter);
		deltU.resize(iter);
		this->T = 0.01;
		this->To = 0.01;
		this->k = 0.1;
		this->Td = 1;
		this->u[0] = 0;
		this->e[0] = 0;
		this->e[1] = 0;
		this->e[2] = 0;
		Obj::input();
		SetQs();
	}
	PID::void SetW() {
		for (int i = 0; i < 10; i++) {
			std::cout << "Enter w:" << std::endl;
			std::cin >> w[i];
		}
	}
	PID::void SetY(int place) {
		Obj::linear(place);
		this->yP[place] = getY(place);
	}
	PID::void SetY(int place, double data) {
		this->yP[place] = data;
	}
	PID::void setE(int place) {
		e[place] = w[place] - yP[place];
	}
	PID::void SetQs() {
		this->q0 = k * (1 + Td / To);
		this->q1 = -k * (1 + 2 * (Td / To) - To / T);
		this->q2 = k * (Td / To);
	}
	PID::void SetU(int place) {
		int placeE = 0;
		int placeQ = 0;
		if (place == 0) {
			placeQ = 1;
		}
		else {
			placeQ = place;
		}

		if (place == 0 || place == 1) {
			placeE = 2;
		}
		else if (place > 2) {
			setE(place);
		}
		deltU[place] = q0 * e[placeE] + q1 * e[placeE - 1] + q2 * e[placeE - 2];
		u[placeQ] = u[placeQ - 1] + deltU[place];
	}
	PID::int iterGet() {
		--iter;
		return iter;
	}
	PID::double GetE(int place) {
		return this->e[place];
	}
	PID::double GetYp(int place) {
		return this->yP[place];
	}
	PID::double GetUP(int place) {
		return this->u[place];
	}
	PID::void SetW(int place, double data) {
		this->w[place] = data;
	}
	PID::double GetQs0() {
		return this->q0;
	}
	PID::double GetQs1() {
		return this->q1;
	}
	PID::double GetQs2() {
		return this->q2;
	}
