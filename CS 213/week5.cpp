#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> p1;
vector<int> p2;
vector<int> p3;
vector<int> inv_p1;
vector<int> inv_p2;
vector<int> inv_p3;
bool check_lesser(int i,int j)
{
	int tests_passed = 0;
	if (inv_p1[i]<inv_p1[j])
		tests_passed++;
	if (inv_p2[i]<inv_p2[j])
		tests_passed++;
	if (inv_p3[i]<inv_p3[j])
		tests_passed++;
	if (tests_passed>=2)
		return true;
	else
		return false;
}
int main()
{
	int n = 0;
	cin >> n;
	vector<int> p4;
	p1.push_back(0);
	p2.push_back(0);
	p3.push_back(0);
	p4.push_back(0);
	for (int i=1;i<=n;i++)
	{
		p3.push_back(i);
		p4.push_back(i);
		int temp=0;
		cin >> temp;
		p1.push_back(temp);
	}
	for (int i=1;i<=n;i++)
	{
		int temp=0;
		cin >> temp;
		p2.push_back(temp);
	}
	
	inv_p1.push_back(0);
	for (int i=0;i<n;i++)
		inv_p1[p1[i]]=i;
	
	inv_p2.push_back(0);
	for (int i=0;i<n;i++)
		inv_p2[p2[i]]=i;
	
	inv_p3.push_back(0);
	for (int i=0;i<n;i++)
		inv_p3[p3[i]]=i;

	sort(p4.begin(),p4.end(),check_lesser);

	
}