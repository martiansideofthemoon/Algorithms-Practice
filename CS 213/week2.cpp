#include <vector>
#include <iostream>
using namespace std;
void print_vector(vector<int> a)
{
	cout << "(" << a[0] << "," << a[1] << ")" << ";";
}
bool evaluate_line(vector<int> point1,vector<int> point2,vector<int> point3)
{
	if (point2[0]==point1[0])
	{
		double value = -1*(point3[0]-point1[0]);
		if (value>0)
			return true;
		else
			return false;
	}
	double slope = (point2[1]-point1[1]) / (point2[0]-point1[0]);
	double value = point3[1]-point1[1]-slope*(point3[0]-point1[0]);
	if (value>0)
		return true;
	else
		return false;
}
void solve(vector<int> *red,vector<int> *blue,int n,int *red_indices,int *blue_indices)
{
	/*
	cout << "Printing red :-";
	for (int i=0;i<n;i++)
		print_vector(red[i]);
	cout << "\n Printing blue :-";
	for (int i=0;i<n;i++)
		print_vector(blue[i]);
	cout << "\n";*/
	vector<int> point1 = red[0];
	int candidate=-1;
	int match_amount=0;
	int r_pos=0,r_neg=0,b_pos=0,b_neg=0;
	for (int i=0;i<n;i++)
	{
		vector<int> point2 = blue[i];
		int temp_r_pos=0,temp_r_neg=0,temp_b_pos=0,temp_b_neg=0;
			
		for (int j=1;j<n;j++)
		{
			bool result=evaluate_line(point1,point2,red[j]);
			if (result)
				temp_r_pos++;
			else
				temp_r_neg++;
		}
		for (int j=0;j<n;j++)
		{
			if (j==i)
				continue;
			bool result=evaluate_line(point1,point2,blue[j]);
			if (result)
				temp_b_pos++;
			else
				temp_b_neg++;
		}
		if (temp_r_pos==temp_b_pos && temp_r_pos>0 && temp_r_neg==temp_b_neg && temp_r_neg>0
			 && min(temp_r_pos,temp_r_neg)>match_amount)
		{
			candidate=i;
			match_amount=min(temp_r_pos,temp_r_neg);
			r_pos=temp_r_pos;
			r_neg=temp_r_neg;
			b_pos=temp_b_pos;
			b_neg=temp_b_neg;
		}
	}


	//cout << "Candidate is " << candidate << endl;
	if (candidate==-1)
	{
		if (n==1)
			cout << red_indices[0] << " " << blue_indices[0] << "\n";
		else if (n==2)
		{
			if (evaluate_line(red[0],blue[0],red[1])!=evaluate_line(red[0],blue[0],blue[1]))
			{
				cout << red_indices[0] << " " << blue_indices[1] << "\n";
				cout << red_indices[1] << " " << blue_indices[0] << "\n";
			}
			else
			{
				cout << red_indices[0] << " " << blue_indices[0] << "\n";
				cout << red_indices[1] << " " << blue_indices[1] << "\n";
			}
		}
	}
	else
	{
		vector<int> point2 = blue[candidate];
		cout << red_indices[0] << " " << blue_indices[candidate] << "\n";
		int a=0,b=0,c=0,d=0;
		vector<int> new_red1[r_pos];
		vector<int> new_red2[r_neg];
		vector<int> new_blue1[b_pos];
		vector<int> new_blue2[b_neg];
		int new_red1_indices[r_pos];
		int new_red2_indices[r_neg];
		int new_blue1_indices[b_pos];
		int new_blue2_indices[b_neg];
		int i=1,j=0;
		//cout << "Red pos : " << r_pos << " and neg : " << r_neg << "\n";
		//cout << "Blue pos : " << b_pos << " and neg : " << b_neg << "\n";
		while (i<n)
		{
			if (evaluate_line(point1,point2,red[i]))
			{
				new_red1[a] = red[i];
				new_red1_indices[a] = i;
				a++;
			}
			else
			{
				new_red2[b] = red[i];
				new_red2_indices[b] = i;
				b++;
			}
			i++;
		}
		while (j<n)
		{
			if (j==candidate)
			{
				j++;
				continue;
			}
			if (evaluate_line(point1,point2,blue[j]))
			{
				new_blue1[c] = blue[j];
				new_blue1_indices[c] = j;
				c++;
			}
			else
			{
				new_blue2[d] = blue[j];
				new_blue2_indices[d] = j;
				d++;
			}
			j++;
		}

		solve(new_red1,new_blue1,r_pos,new_red1_indices,new_blue1_indices);
		solve(new_red2,new_blue2,r_neg,new_red2_indices,new_blue2_indices);
	}
}
int main()
{
	int n;
	cin >> n;
	vector<int> red[n/2];
	vector<int> blue[n/2];
	for (int i=0;i<n/2;i++)
	{
		vector<int> v;
		int x,y;
		cin >> x >> y;
		v.push_back(x);
		v.push_back(y);
		red[i]=v;
	}
	for (int i=0;i<n/2;i++)
	{
		vector<int> v;
		int x,y;
		cin >> x >> y;
		v.push_back(x);
		v.push_back(y);
		blue[i]=v;
	}
	int red_indices[n/2];
	int blue_indices[n/2];
	for (int i=0;i<n/2;i++)
	{
		red_indices[i]=i;
		blue_indices[i]=i;
	}
	
	solve(red,blue,n/2,red_indices,blue_indices);
}