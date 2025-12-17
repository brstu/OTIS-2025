#include "Linear.h"
#include <iostream>

using namespace std;

void input(Params &s) {
	cout << "Enter amount of iterations: ";
	cin >> s.k;
	s.u.resize(s.k + 1, 0);
	s.y.resize(s.k + 1, 0);
	cout << "\nEnter temperature: ";
	cin >> s.y.at(0);
	for (auto& warm : s.u) {
		cout << "\nEnter warm: ";
		cin >> warm;
	}
	
	cout << "Enter const a: ";

	cin >> s.a;

	cout << "Enter const b: ";

	cin >> s.b;

}
void linear(Params &s, const int& place) {
	    if(s.k >= 0){
			s.y.at(place + 1) = s.a * s.y.at(place) + s.b * s.u.at(place);
		}
}
