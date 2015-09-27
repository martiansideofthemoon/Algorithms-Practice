#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
int num_lanes=0, width=0, u_ships=0, u_ferry=0, t1=0, t2=0;

struct lane {
	char direction;
	int position;
	int num_ships;
	vector<vector<double> > ships;
	double forbidden1=0;
	double forbidden2=0;
	double offset=0;
	vector<int> forbidden_time(int ship_no) 
	{
		vector<int> ship = ships[ship_no];
		if (direction=='E')
		{
			forbidden1=-1*ship[1]/u_ships;
			forbidden2=forbidden1+ship[0]/u_ships;
			offset=position*width/u_ferry;
			forbidden1+=offset;
			forbidden2+=offset;
		}
		else if (direction=='W')
		{
			forbidden1=ship[1]/u_ships;
			forbidden2=forbidden1+ship[0]/u_ships;
			offset=position*width/u_ferry;
			forbidden1+=offset;
			forbidden2+=offset;
		}
		vector<double> result;
		result.pushback(forbidden1);
		result.pushback(forbidden2);
		return result;
	}
};

int main()
{
	cin >> num_lanes >> width >> u_ships >> u_ferry >> t1 >> t2;
	vector<lane> lanes;
	for (int i=0;i<num_lanes;i++)
	{
		lane l1;
		cin >> l1.direction >> l1.num_ships;
		l1.position=i;
		for (int j=0;j<l1.num_ships;j++)
		{
			vector <int> v1;
			int len,pos;
			cin >> len >> pos;
			v1.pushback(len);
			v1.pushback(pos);
			l1.ships.pushback(v1);
			lanes.pushback(l1);
		}
	}
}