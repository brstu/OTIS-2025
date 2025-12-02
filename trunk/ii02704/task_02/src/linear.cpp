#include "linear.h"

#include <iostream>
#include <vector>

using namespace std;

void input(int& k, vector<double> &u, vector<double> &y, double& a, double& b) {
	cout << "Enter amount of iterations: ";
	cin >> k;
	u.resize(k + 1, 0);
	y.resize(k + 1, 0);
	cout << "\nEnter temperature: ";
	cin >> y.at(0);
	for (auto& warm : u) {
		cout << "\nEnter warm: ";
		cin >> warm;
	}
	
	cout << "Enter const a: ";

	cin >> a;

	cout << "Enter const b: ";

	cin >> b;

}

void linear(const int& place, const int& k, vector<double>& y, const vector<double>& u, const double& b, const double& a) {
	    if(k > 0){
		y.at(place + 1) = a * y.at(place) + b * u.at(place);
		}
}
