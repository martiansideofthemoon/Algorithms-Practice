#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> perm_p;
vector<int> perm_q;
vector<int> perm_r;
vector<int> perm_s;
vector<int> inv_perm_p;
vector<int> inv_perm_q;
//vector<int> inv_perm_r;ra
void print_list(list<int> i,list<int>::iterator i1,list<int>::iterator i2)
{
	//list<int>::iterator a1 = i1;
	while(i1!=i2)
	{
		cout << *i1 << ",";
		i1++;
	}
	cout << endl;
}
void print_list(list<int> i)
{
	list<int>::iterator i1 = i.begin();
	while(i1!=i.end())
	{
		cout << *i1 << ",";
		i1++;
	}
	cout << endl;
}
list<int>::iterator forward(list<int>::iterator i1,int pos)
{
	list<int>::iterator i2 = i1;
	for (int i=1;i<=pos;i++)
		i2++;
	return i2;
}
list<int>::iterator backward(list<int>::iterator i1,int pos)
{
	list<int>::iterator i2 = i1;
	for (int i=1;i<=pos;i++)
		i2--;
	return i2;
}
bool check_lesser(int i,int j)
{
	int tests_passed = 0;
	if (inv_perm_p[i]<inv_perm_p[j])
		tests_passed++;
	if (inv_perm_q[i]<inv_perm_q[j])
		tests_passed++;
	//if (inv_perm_r[i]<inv_perm_r[j])
	//	tests_passed++;
	if (tests_passed>=2)
		return true;
	else
		return false;
}
list<int>::iterator merge_with_count(list<int> &l1,list<int>::iterator l1_begin,list<int>::iterator l1_end,
							list<int>::iterator l2_begin,list<int>::iterator l2_end,
							int size1,int size2,int &count)
{
	list<int>::iterator initial_first = l1_begin;
	cout << "Merging lists of size " << size1 << " and " << size2 << " :- " << endl;
	//print_list(l1,l1_begin,l1_end);
	//print_list(l1,l2_begin,l2_end);
	list<int> l3;
	list<int>::iterator new_iter=l3.begin();
	while (l1_begin!=l1_end && l2_begin!=l2_end)
	{
		if (*l1_begin<*l2_begin)
		{
			l3.push_back(*l1_begin);
			l1_begin++;
			size1--;
		}
		else
		{
			l3.push_back(*l2_begin);
			l2_begin++;
			//print_list(l1,l1.begin(),l1.end());
			size2--;
			count+=size1;
		}
	}
	if (l1_begin==l1_end)
	{
		while (l2_begin!=l2_end)
		{
			l3.push_back(*l2_begin);
			l2_begin++;
			size2--;
			count+=size1;
		}
	}
	else if (l2_begin==l2_end)
	{
		while (l1_begin!=l1_end)
		{
			l3.push_back(*l1_begin);
			l1_begin++;
			size1--;
		}
	}
	list<int>::iterator final_first = l3.begin();
	l1.insert(initial_first,l3.begin(),l3.end());
	l1.erase(initial_first,l2_end);
	//print_list(l3);
	cout << "After merging :- " << endl;
	print_list(l1,l1.begin(),l1.end());
	cout << "New first element is " << *final_first << endl;
	return final_first;
}

list<int>::iterator merge_sort(list<int> &l1,list<int>::iterator l1_begin,list<int>::iterator l1_end,int size,int &count)
{
	cout << "Merge sorting list :- " << endl;
	print_list(l1,l1_begin,l1_end);
	if (forward(l1_begin,1)!=l1_end && l1_begin!=l1_end)
	{
		list<int>::iterator midway=l1_begin;
		for (int i=0;i<size/2;i++)
			midway++;
		//cout << "yolo1" << endl;
		l1_begin = merge_sort(l1,l1_begin,midway,size/2,count);
		cout << *l1_begin << ", " << *midway << " before second merge sort. " << endl;
		
		//cout << "yolo2" << endl;
		midway = merge_sort(l1,midway,l1_end,size-size/2,count);
		//cout << "yolo3" << endl;
		cout << *l1_begin << ", " << *midway << " after second merge sort" << endl;
		
		l1_begin = merge_with_count(l1,l1_begin,midway,midway,l1_end,size/2,size-size/2,count);
		//print_list(l1);
		return l1_begin;
	}
	return l1_begin;
}

int main()
{
	int n = 0;
	cin >> n;
	perm_p.push_back(0);
	perm_q.push_back(0);
	perm_r.push_back(0);
	perm_s.push_back(0);
	for (int i=1;i<=n;i++)
	{
		perm_r.push_back(i);
		perm_s.push_back(i);
		int temp=0;
		cin >> temp;
		perm_p.push_back(temp);
	}
	for (int i=1;i<=n;i++)
	{
		int temp=0;
		cin >> temp;
		perm_q.push_back(temp);
	}
	
	inv_perm_p.push_back(0);
	for (int i=0;i<n;i++)
		inv_perm_p[perm_p[i]]=i;
	
	inv_perm_q.push_back(0);
	for (int i=0;i<n;i++)
		inv_perm_q[perm_q[i]]=i;
		
	for (int i=1;i<=n;i++)
		perm_s[i]=inv_perm_q[perm_q[i]];
	

	list<int> dummy_p;
	dummy_p.push_back(0);
	for (int i=1;i<=n;i++)
		dummy_p.push_back(perm_p[i]);
	int count_p=0;
	merge_sort(dummy_p,forward(dummy_p.begin(),1),dummy_p.end(),n,count_p);
	print_list(dummy_p);
	cout << count_p << endl;
}