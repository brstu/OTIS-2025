#include  <iostream>
#include  <cmath>

using  namespace  std;

double linear(double  y, double  u, double  a, double  b)
{
    return  a  *  y  +  b  *  u;
}

double nonlinear(double  y, double  u, double  a, double  b, double  c, double  d)
{
    return  a  *  y  -  b  *  y  *  y  +  c  *  u  +  d  *  sin(u);
}

int  main()
{
	double  y, u, a, b, c, d;
	cout  <<  "y, u = ";
	cin  >>  y  >>  u;
	cout  <<  "а, b, c, d = ";
	cin  >>  a  >>  b  >>  c  >>  d;

	int  n;
	cout  <<  "n = ";
	cin  >>  n;

	double  y1  =  y, y2  =  y;
	for (int  i  =  0; i  <  n; i++)
	{
        y1 = linear(y1, u, a, b);
		y2  =  nonlinear(y2, u, a, b, c, d);
		cout << "Step "  <<  i+1  <<  ", linear y = "  <<  y1  <<  ", n-linear y = "  <<  y2  <<  endl;
	}

	return  0;
}