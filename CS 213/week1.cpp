#include <iostream>
#include <cmath>
using namespace std;
int p,a,b,c,d;
double arr[2];
double f(long int i)
{
	return p * (sin(a*i+b) + cos(c*i+d) + 2);
}

void compute_fall(long int n)
{

	int i=2;
	double max = f(1);
	double fall=0;
	double previous = max;
	double max_rate = 0;
	while (i<=n)
	{
		
		double current = f(i);
		if (current>max)
			max=current;
		if (current <= previous)
		{
			double this_fall = max-current;
			double new_max_rate = current-previous;
			if (this_fall>fall)
			{
				fall=this_fall;
			}
			if (new_max_rate>max_rate)
				max_rate = new_max_rate;
		}
		i++;
		previous = current;
	}
	
	arr[0]=fall;
	arr[1]=max_rate;
	
}

int main()
{
	long int n;
	cin >> p >> a >> b >> c >> d >> n;
	compute_fall(n);
	cout << arr[0] << endl;
	cout << arr[1] << endl;
}
