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
	vector<vector<int> > ships;
	vector<double> forbidden_time(int ship_no) 
	{
		vector<int> ship = ships[ship_no];
		double crossing_offset=(double)width/u_ferry;
		double forbidden1=0;
		double forbidden2=0;
		double offset=0;
		if (direction=='E')
		{
			forbidden1=-1.0*ship[1]/u_ships;
			forbidden2=forbidden1+(double)ship[0]/u_ships;
			offset=(double)position*width/u_ferry;
			forbidden1=forbidden1-offset-crossing_offset;
			forbidden2=forbidden2-offset;
		}
		else if (direction=='W')
		{
			forbidden1=(double)ship[1]/u_ships;
			forbidden2=forbidden1+(double)ship[0]/u_ships;
			offset=(double)position*width/u_ferry;
			forbidden1=forbidden1-offset-crossing_offset;
			forbidden2=forbidden2-offset;
		}
		vector<double> result;
		result.push_back(forbidden1);
		result.push_back(forbidden2);
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
			v1.push_back(len);
			v1.push_back(pos);
			l1.ships.push_back(v1);
		}
		lanes.push_back(l1);
	}
	vector<lane>::iterator iter = lanes.begin();
	//map<int, vector<int> > intervals;
	map<double, int> intervals;
	while (iter!=lanes.end())
	{
		int num_ships=(*iter).num_ships;
		for (int i=0;i<num_ships;i++)
		{
			vector<double> forbidden = (*iter).forbidden_time(i);
			if ((forbidden[0]<t1 && forbidden[1]<t1) || (forbidden[0]>t2 && forbidden[1]>t2))
				continue;
			//intervals[forbidden[0]] = forbidden;
			intervals[forbidden[0]]+=1;
			intervals[forbidden[1]]+=-1;
		}
		iter++;
	}
	map<double, int>::iterator i1 = intervals.begin();
	double start=0,end=0;
	double longest=0.000;
	int forbid_ships=0;
	bool isValidRegion=false;
	if (intervals.size()==0)
	{
		cout << t2-t1 << endl;
		return 0;
	}
	if ((i1->first)>t1)
		longest=(i1->first)-t1;
	while (i1!=intervals.end())
	{	
		if (isValidRegion==true)
		{
			end=i1->first;
			isValidRegion=false;
			if (end-start>longest)
				longest=end-start;
		}
		forbid_ships+=i1->second;
		if (forbid_ships==0)
		{
			start=i1->first;
			isValidRegion=true;
		}
		i1++;
	}
	i1--;
	if ((i1->first)<t2 && (t2-i1->first)>longest)
		longest=t2-i1->first;
	cout << longest << endl;
}