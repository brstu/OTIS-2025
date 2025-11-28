#include <iostream>
#include <vector>

using namespace std;


void input(int& k, vector<double> u, vector<double> y, double& y0, double& a, double& b, double& c, double& d, double& c1, double& rc) {
	cout << "Enter amount of iterations: ";
	cin >> k;
	u.resize(k, 0);
	y.resize(k, 0);
	cout << "\nEnter temperature: ";
	cin >> y.at(0);
	for (auto& warm : u) {
		cout << "\nEnter warm: ";
		cin >> warm;
	}
	u.resize(k + 1, 0);
	y.resize(k + 1, 0);
	cout << "\nEnter room temperature: ";

	cin >> y0;

	cout << "Enter const a: ";

	cin >> a;

	cout << "Enter const b: ";

	cin >> b;

	cout << "Enter const c: ";

	cin >> c;

	cout << "Enter const d: ";

	cin >> d;

	cout << "Enter const c1: ";

	cin >> c1;

	cout << "Enter const rc: ";

	cin >> rc;

}
void linear(const int& place, const int& k, vector<double>& y, const vector<double>& u, const double& b, const double& a) {
	if (place <= k && place >= 0) {
		y.at(place + 1) = a * y.at(place) + b * u.at(place);
	}
	else {
		cout << "\nEntered place out of range";
	}

}
int main()
{
	int k = 4;
	int t = 0;
	vector<double> y;
	vector<double> u;
	u.resize(k + 1, 0);
	y.resize(k + 1, 0);
	double y0 = 25;
	double a = 1;
	double b = 1;
	double c = 1;
	double d = 1;
	double c1 = 1;
	double rc = 1;
	//input(k, u, y, y0, a, b, c, d, c1, rc);
	for (int i = 0; i < k; i++) {
		linear(i, k, y, u, b, a);
	}
	for (auto n : y) {
		cout << n << endl;
	}
	return 0;
}
