#include <iostream>
using namespace std;
int num=0;
int total=0;
int calc(int arr[][8],int queens2[][2],int numqueen2)
{
	//cout << numqueen2 << endl;
	if (numqueen2==total) 
	{
		for (int i=0;i<8;i++)
		{
			cout << queens2[i][0] << "," << queens2[i][1] << ";";
		}
		num++;
		cout << endl;
		return 1;
	}
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			int queens[8][2];
			for (int a=0;a<numqueen2;a++)
			{
				queens[a][0]=queens2[a][0];
				queens[a][1]=queens2[a][1];
			}
			int numqueen=numqueen2;
			int arr2[8][8];
			for (int a=0;a<8;a++)
			{
				for (int b=0;b<8;b++) arr2[a][b]=arr[a][b];
			}
			if (arr2[i][j]==0)
			{
			arr2[i][j]=2;
			queens[numqueen][0]=i;
			queens[numqueen][1]=j;
			numqueen++;
			int k[][4]={{1,1},{1,-1},{-1,1},{-1,-1}};
			for (int m=0;m<numqueen;m++)
			{
				for (int a=0;a<8;a++)
				{
					if (arr2[a][queens[m][1]]==0)
					arr2[a][queens[m][1]]=1;
				if (arr2[queens[m][0]][a]==0)
					arr2[queens[m][0]][a]=1;
				}
				for (int a=0;a<4;a++)
				{
					int c=1;
					while (k[a][0]*c+queens[m][0]<8 && k[a][0]*c+queens[m][0]>=0 && k[a][1]*c+queens[m][1]>=0 && k[a][1]*c+queens[m][1]<8)
					{
						if (arr2[k[a][0]*c+queens[m][0]][k[a][1]*c+queens[m][1]]!=2)
						arr2[k[a][0]*c+queens[m][0]][k[a][1]*c+queens[m][1]]=1;
						c++;
					}				
				}
			}
			/*for (int q=0;q<8;q++)
			{
				for (int w=0;w<8;w++)
				{
					cout << arr2[q][w];
				}
				cout << endl;
			}
			cout << endl;*/
			int u=calc(arr2,queens,numqueen);
			arr[i][j]=1;
			}
			
		}
	}
	return num;
}
int main()
{
	int array[8][8];
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++) array[i][j]=0;
	}	
	int queens[8][2];
	for (int i=1;i<10;i++)
	{
		total=i;
		int k=calc(array,queens,0);
		cout << num << endl;
		num=0;
		for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++) array[i][j]=0;
	}	
	}
	
}