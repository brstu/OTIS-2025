#include <iostream>
#include  <cmath>

using namespace std;

double x(double  y, double  u, double  a, double  b)
{
    return  a  *  y  +  b  *  u;
}

double x1(double  y, double  u, double  a, double  b, double  c, double  d)
{
    return  a  *  y  -  b  *  y  *  y  +  c  *  u  +  d  *  sin(u);
}

int main(){
    cout << "Git";
    
    double y, a, b, c, u, d;
    cin >> y >> a >> b >> c >> u >> d; 

    double y1 = y;
    double y2 = y;

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        y1 = x(y1, u, a, b);
        y2 = x1(y2, u, a, b, c, d);
        cout << "\n" << y1 << "\t" << y2 << endl;
    }

    return 0;
}