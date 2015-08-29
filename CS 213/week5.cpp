#include <vector>
#include <iostream>
#include <limits>
using namespace std;
void print_vector(vector<int> &i,vector<int>::iterator i1,vector<int>::iterator i2)
{
	while(i1!=i2)
	{
		cout << *i1 << ",";
		i1++;
	}
	cout << endl;
}
void print_vector(vector<int> &i)
{
	vector<int>::iterator i1 = i.begin();
	while(i1!=i.end())
	{
		cout << " " << *i1;
		i1++;
	}
	cout << endl;
}
vector<int>::iterator forward(vector<int>::iterator i1,int pos)
{
	vector<int>::iterator i2 = i1;
	for (int i=1;i<=pos;i++)
		i2++;
	return i2;
}
vector<int>::iterator backward(vector<int>::iterator i1,int pos)
{
	vector<int>::iterator i2 = i1;
	for (int i=1;i<=pos;i++)
		i2--;
	return i2;
}
bool check_lesser(int i,int j,vector<int> &inv_p,vector<int> &inv_q)
{
	if (inv_p[i]<inv_p[j] && inv_q[i]<inv_q[j])
		return true;
	else
		return false;
}
void merge(vector<int> &a,vector<int>::iterator start,vector<int>::iterator midway,
		   vector<int>::iterator end,int size_left,int size_right,int &count,
		   vector<int> &inv_p,vector<int> &inv_q)
{
	vector<int>left;
	vector<int>right;
	vector<int>::iterator k = start;
	while (k!=midway)
	{
		left.push_back(*k);
		++k;
	}	
	left.push_back(numeric_limits<int>::max());
	while (k!=end)
	{
		right.push_back(*k);
		++k;
	}
	right.push_back(numeric_limits<int>::max());
	vector<int>::iterator i = left.begin(); 
	vector<int>::iterator j = right.begin();
	k = start;
	while (k!=end)
	{
		if (check_lesser(*i,*j,inv_p,inv_q))
		//if (*i<*j)
		{
			*k = *i;
			++i;
			++k;
		}
		else
		{
			*k = *j;
			++j;
			++k;
		}
	}
}
void merge_sort(vector<int> &a,vector<int>::iterator start,vector<int>::iterator end,
				int size, int &count, vector<int> &inv_p, vector<int> &inv_q)
{
	if (*start!=*end && *forward(start,1)!=*end)
	{
		vector<int>::iterator midway = forward(start,size/2);
		merge_sort(a,start,midway,size/2,count,inv_p,inv_q);
		merge_sort(a,midway,end,size-size/2,count,inv_p,inv_q);
		merge(a,start,midway,end,size,size-size/2,count,inv_p,inv_q);
	}
}
int main()
{
	int size = 0;
	cin >> size;

	vector<int> perm_p;
	vector<int> perm_q;
	vector<int> perm_r (size+1);
	vector<int> perm_s (size+1);
	vector<int> inv_p (size+1);
	vector<int> inv_q (size+1);
	perm_p.push_back(0);
	perm_q.push_back(0);
	perm_r.push_back(0);
	perm_s.push_back(0);
	inv_p.push_back(0);
	inv_q.push_back(0);

	for (int i=1;i<=size;i++)
	{
		int temp;
		cin >> temp;
		perm_p.push_back(temp);
		inv_p[temp] = i;
	}
	for (int i=1;i<=size;i++)
	{
		int temp;
		cin >> temp;
		perm_q.push_back(temp);
		inv_q[temp] = i;
	}
	for (int i=1;i<=size;i++)
	{
		perm_r[i]=i;
		perm_s[i]=inv_p[perm_q[i]];
	}

	int count = 0;
	//Sort sequence r using check_lesser routine
	merge_sort(perm_r,forward(perm_r.begin(),1),perm_r.end(),size,count,inv_p,inv_q);
	//Now we must check whether it is a consistent permutation
	
}