#include <map>
#include <set>
#include <string.h>
#include <iostream>
using namespace std;
struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};
void print_set(map<int, set<const char*, ltstr> >::iterator i1)
{
	cout << i1->first << " ";
	set<const char*, ltstr>::iterator set_iter = (i1->second).begin();
	set<const char*, ltstr>::iterator set_iter_end = (i1->second).end();
	while(set_iter!=set_iter_end)
	{
		cout << *set_iter << " ";
		set_iter++;
	}
	cout << endl;
}
int main()
{
	map<const char*, int, ltstr> accounts;
	map<int, set<const char*, ltstr> > balances;
	bool stop=false;
	int illegal_count=0;
	while (!stop)
	{
		char operation;
		cin >> operation;
		if (operation=='O')
		{
			char * name = new char[80];
			cin >> name;
			if (accounts.find(name)!=accounts.end())
			{
				illegal_count++;
				continue;
			}
			accounts[name]=0;
			balances[0].insert(name);
		}
		else if (operation=='D')
		{
			char * name = new char[80];
			int amount;
			cin >> name >> amount;
			if (accounts.find(name)==accounts.end())
			{
				illegal_count++;
				continue;
			}
			int original_amount = accounts[name];
			accounts[name]+=amount;
			balances[original_amount].erase(name);
			balances[original_amount+amount].insert(name);			
		}
		else if (operation=='W')
		{
			char * name = new char[80];
			cin >> name;
			int amount;
			cin >> amount;
			if (accounts.find(name)==accounts.end() || amount>accounts[name])
			{
				illegal_count++;
				continue;
			}
			int original_amount = accounts[name];
			accounts[name]-=amount;
			balances[original_amount].erase(name);
			balances[original_amount-amount].insert(name);
		}
		else if (operation=='C')
		{
			char *name = new char[80];
			cin >> name;
			if (accounts.find(name)==accounts.end() || accounts[name]!=0)
			{
				illegal_count++;
				continue;
			}
			int original_amount=accounts[name];
			accounts.erase(name);
			balances[original_amount].erase(name);			
		}
		else if (operation=='P')
		{
			int start,end;
			cin >> start >> end;
			map<int, set<const char*, ltstr> >::iterator i1 = balances.lower_bound(start);
			map<int, set<const char*, ltstr> >::iterator i2 = balances.upper_bound(end);
			i2--;
			while (i1!=i2)
			{
				if ((i1->second).size()!=0)
				print_set(i1);
				i1++;
			}
			if ((i1->second).size()!=0)
			print_set(i1);
		}
		else if (operation=='E')
		{
			stop=true;
		}
	}
	cout << illegal_count << endl;
}