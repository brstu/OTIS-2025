#include "main.h"
#include <iostream>
#include  <cmath>

using namespace std;

int main(){
    
    double y;
    double a;
    double b;
    double c;
    double u;
    double d;
    cout << "Input y: ";
    cin >> y;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    cout << "Input c: ";
    cin >> c;
    cout << "Input u: ";
    cin >> u;
    cout << "Input d: ";
    cin >> d; 

    double y1 = y;
    double yx = y;
    double y2 = y;

    cout << "\nInput n: ";
    int n;
    cin >> n;

    cout << "\nn\ty1\ty2" << endl;
    for(int i = 0; i < n; i++){
        y1 = x(y1, u, a, b);
        double yb = y2;
        y2 = x1(y2, u, a, b, c, d, yx);
        yx = yb;

        cout <<i+1<< "\t"<<  y1 << "\t" << y2 << endl;
    }
    cout << endl;
    system ("pause");
    return 0;
}
