#include <vector>
#include <iostream>
#include <limits>
using namespace std;

void print_vector(vector<int> &i,vector<int>::iterator i1,vector<int>::iterator i2)
{
	while(i1!=i2)
	{
		cout << " " << *i1;
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
	if (i>inv_p.size())
		return false;
	if (j>inv_p.size())
		return true;
	int count = 0;
	if (i<j)
		count++;
	if (inv_p[i]<inv_p[j])
		count++;
	if (inv_q[i]<inv_q[j])
		count++;
	if (count>=2)
		return true;
	else
		return false;
}
void merge(vector<int> &a,vector<int>::iterator start,vector<int>::iterator midway,
		   vector<int>::iterator end, vector<int> &inv_p,vector<int> &inv_q)
{ 
	/*****DEBUGGING*****
	cout << "Merging arrays :- " << endl;
	print_vector(a,start,midway);
	print_vector(a,midway,end);
	/*****DEBUGGING*****/
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
	right.push_back(numeric_limits<int>::max()); // Sentinel 
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
				int size, vector<int> &inv_p, vector<int> &inv_q)
{
	/*****DEBUGGING*****
	cout << "Merge sorting array :- " << endl;
	print_vector(a,start,end);
	/*****DEBUGGING*****/
	if (*start!=*end && *forward(start,1)!=*end)
	{
		vector<int>::iterator midway = forward(start,size/2);
		merge_sort(a,start,midway,size/2,inv_p,inv_q);
		merge_sort(a,midway,end,size-size/2,inv_p,inv_q);
		merge(a,start,midway,end,inv_p,inv_q);
	}
}
void merge_count(vector<int> &a,vector<int>::iterator start,vector<int>::iterator midway,
		   vector<int>::iterator end,int size_left,int size_right,int &count,vector<int> &inv_p,bool &check)
{
	/*****DEBUGGING*****
	cout << "Merging arrays :- " << endl;
	print_vector(a,start,midway);
	print_vector(a,midway,end);
	/*****DEBUGGING*****/
	vector<int>left;
	vector<int>maxpos_left (size_left);
	vector<int>right;
	vector<int>::iterator k = start;
	int maxpos = 0;
	while (k!=midway)
	{
		left.push_back(*k);
		++k;
	}	
	for (int m=size_left-1;m>=0;m--)
	{
		if (inv_p[left[m]]>maxpos)
			maxpos=inv_p[left[m]];
		maxpos_left[m]=maxpos;
	}
	
	left.push_back(numeric_limits<int>::max());
	while (k!=end)
	{
		right.push_back(*k);
		++k;
	}
	right.push_back(numeric_limits<int>::max()); // Sentinel 
	vector<int>::iterator i = left.begin(); 
	vector<int>::iterator j = right.begin();
	vector<int>::iterator max_pos_iter = maxpos_left.begin();
	k = start;
	while (k!=end)
	{
		//if (check_lesser(*i,*j,inv_p,inv_q))
		if (*i<*j)
		{
			*k = *i;
			++i;
			++k;
			++max_pos_iter;
			size_left--;
		}
		else
		{
			if (*i!=numeric_limits<int>::max() && *max_pos_iter>inv_p[*j])
			{

				check=false;		
			}
			*k = *j;
			++j;
			++k;
			count+=size_left;
		}
	}
}
void merge_sort_count(vector<int> &a,vector<int>::iterator start,vector<int>::iterator end,
				int size, int &count, vector<int> &inv_p,bool &check)
{
	/*****DEBUGGING*****
	cout << "Merge sorting array :- " << endl;
	print_vector(a,start,end);
	/*****DEBUGGING*****/
	if (*start!=*end && *forward(start,1)!=*end)
	{
		vector<int>::iterator midway = forward(start,size/2);
		merge_sort_count(a,start,midway,size/2,count,inv_p,check);
		merge_sort_count(a,midway,end,size-size/2,count,inv_p,check);
		merge_count(a,start,midway,end,size/2,size-size/2,count,inv_p,check);
		
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
	perm_r[0]=0;
	perm_s[0]=0;
	inv_p[0]=0;
	inv_q[0]=0;

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
	bool check = true;
	merge_sort(perm_r,forward(perm_r.begin(),1),perm_r.end(),size,inv_p,inv_q);
	cout << "Permutation after sorting :- ";
	print_vector(perm_r);
	vector<int>dummy_r = perm_r;
	
	merge_sort_count(dummy_r,forward(dummy_r.begin(),1),dummy_r.end(),size,count,inv_p,check);
	if (!check)
	{
		cout << "inconsistent as every inversion pair not in p" << endl;
		/*

		For getting i,j,k , we can find the inconsistent inversion pair in r. Perform a linear search between
		the two elements in perm_r for the third element. Any cyclic order will do for i,j,k

		*/
		return 0;
	}
	check = true;
	dummy_r = perm_r;
	int count2=0;
	merge_sort_count(dummy_r,forward(dummy_r.begin(),1),dummy_r.end(),size,count2,inv_q,check);
	if (!check)
	{
		cout << "inconsistent as every inversion pair not in q" << endl;
		/*

		For getting i,j,k , we can find the inconsistent inversion pair in r. Perform a linear search between
		the two elements in perm_r for the third element. Any cyclic order will do for i,j,k

		*/
		return 0;
	}
	int count_p=0;
	merge_sort_count(perm_p,forward(perm_p.begin(),1),perm_p.end(),size,count_p,inv_q,check);
	int count_q=0;
	merge_sort_count(perm_q,forward(perm_q.begin(),1),perm_q.end(),size,count_q,inv_q,check);
	int count_s=0;
	merge_sort_count(perm_s,forward(perm_s.begin(),1),perm_s.end(),size,count_s,inv_q,check);
	if (count==(count_p+count_q-count_s)/2)
		print_vector(perm_r,forward(perm_r.begin(),1),perm_r.end());
	else
	{
		cout << "inconsistent with count=" << count << ", count_p=" << count_p << ",count_q=" << count_q
				<<", count_s=" << count_s << endl;
		/*
		
		We can obtain this without using s. We can see that all inversion pairs of p,q are subsets of r.

		*/
	}
		

}