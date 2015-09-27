#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
struct lane {
	char direction;
	int num_ships;
	vector<vector<int> > ships;
};
int main()
{
	int num_lanes=0, width=0, u_ships=0, u_ferry=0, t1=0, t2=0;
	cin >> num_lanes >> width >> u_ships >> u_ferry >> t1 >> t2;
	vector<lane> lanes;
	for (int i=0;i<num_lanes;i++)
	{
		lane l1;
		cin >> l1.direction >> l1.num_ships;
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