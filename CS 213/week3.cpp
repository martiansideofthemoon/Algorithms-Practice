#include <iostream>
#include <vector>
using namespace std;

void compute(vector<int> &a,vector<int> &b,int m,int n)
{
	vector<vector<int>::iterator> possibilities;
	vector<int> indices;
	int number_poss=0;
	int min_length=32000;
	int min_index=0;
	for (int i=0;i<m;i++)
	{
		if (i==m-n+1 && number_poss==0)
		{
			break;
		}
		if (a[i]==b[0])
		{
			if (n==1)
			{
				min_index=i+1;
				min_length=1;
				break;
			}
			indices.push_back(i);
			possibilities.push_back(b.begin());
			number_poss++;
			cout << number_poss << "," << i << endl;
			//Start new possibility.
		}
		for (int j=0;j<number_poss;j++)
		{
			//cout << "a[i] is " << a[i] << " and *possibilities[j] is " << *possibilities[j] << endl; 
			if (possibilities[j]==b.end())
				continue;
			if (a[i]==*possibilities[j])
			{
				possibilities[j]++;
				if (possibilities[j]==b.end() && i-indices[j]<min_length)
				{
					min_length=i-indices[j]+1;
					min_index=indices[j]+1;
				}
			}
		}
	}
	if (min_index==0)
		cout << "infinity" << endl;
	else
		cout << min_length << " " << min_index << endl;
}
int main()
{
	int m,n;
	cin >> m >> n;
	vector<int> a;
	vector<int> b;
	for (int i=0;i<m;i++)
	{
		int temp = 0;
		cin >> temp;
		a.push_back(temp);
	}
	
	for (int i=0;i<n;i++)
	{
		int temp = 0;
		cin >> temp;
		b.push_back(temp);
	}
	//cout << "yolo" << endl;
	compute(a,b,m,n);
}