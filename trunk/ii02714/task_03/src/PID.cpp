#include <iostream>
#include <vector>
#include "../src/Class.h"
#include "../src/PID.h"

	PID::PID(double data, double data2)
	{
		e.resize(iter);
		yP.resize(iter);
		w.resize(iter);
		u.resize(iter);
		deltU.resize(iter);
		SetW(3, data);
		PID::SetY(3, data2);
		this->u[0] = 1;
		this->e[0] = 0;
		this->e[1] = 0;
		this->e[2] = 0;
	}
	PID::PID() 
	{
		e.resize(iter);
		yP.resize(iter);
		w.resize(iter);
		u.resize(iter);
		deltU.resize(iter);
		this->u[0] = 0;
		this->e[0] = 0;
		this->e[1] = 0;
		this->e[2] = 0;
		Obj::input();
		SetQs();
	}
	void PID::SetW() {
		for (int i = 0; i < 10; i++) {
			std::cout << "Enter w:" << std::endl;
			std::cin >> w[i];
		}
	}
	void PID::SetY(int place) {
		Obj::linear(place);
		this->yP[place] = getY(place);
	}
	void PID::SetY(int place, double data) {
		this->yP[place] = data;
	}
	void PID::setE(int place) {
		e[place] = w[place] - yP[place];
	}
	void PID::SetQs() {
		this->q0 = k * (1 + Td / To);
		this->q1 = -k * (1 + 2 * (Td / To) - To / T);
		this->q2 = k * (Td / To);
	}
	void PID::SetUl(int place) {
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
	int PID::iterGet() {
		--iter;
		return iter;
	}
	double PID::GetE(int place) const {
		return this->e[place];
	}
	double PID::GetYp(int place) const{ 
		return this->yP[place];
	}
	double PID::GetUP(int place) const{
		return this->u[place];
	}
	void PID::SetW(int place, double data) {
		this->w[place] = data;
	}
	double PID::GetQs0() const{
		return this->q0;
	}
    double PID::GetQs1() const {
		return this->q1;
	}
	double PID::GetQs2() const{
		return this->q2;
	}
