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
list<int> merge_with_count(list<int> l1,list<int>::iterator l1_begin,list<int>::iterator l1_end,
							list<int>::iterator l2_begin,list<int>::iterator l2_end,
							int size1,int size2,int &count)
{
	while (l1_begin!=l1_end && l2_begin!=l2_end)
	{
		if (*l1_begin<*l2_begin)
		{
			l1_begin++;
			size1--;
		}
		else
		{
			l1.insert(l1_begin,*l2_begin);
			l2_begin = l1.erase(l2_begin);
			size2--;
			count+=size1;
		}
	}
	if (l1_begin==l1_end)
	{
		while (l2_begin!=l2_end)
		{
			l1.insert(l1_begin,*l2_begin);
			l2_begin = l1.erase(l2_begin);
			size2--;
			count+=size1;
		}
	}
}
void merge_sort(list<int> &l1,list<int>::iterator l1_begin,list<int>::iterator l1_end,int size,int &count)
{
	if (l1_begin!=l1_end)
	{
		list<int>::iterator midway=l1_begin;
		for (int i=0;i<size/2;i++)
			midway++;
		merge_sort(l1,l1_begin,midway,size/2,count);
		merge_sort(l1,midway,l1_end,size-size/2,count);
		merge_with_count(l1,l1_begin,midway,midway,l1_end,size/2,size-size/2,count);
	}
}
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

	//sort(p4.begin(),p4.end(),check_lesser);


}