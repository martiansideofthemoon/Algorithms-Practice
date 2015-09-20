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
			char * name;
			cin >> name;
			accounts[name]=0;
			balances[0].insert(name);
		}
		else if (operation=='D')
		{
			char *name;
			cin >> name;
			int amount;
			cin >> amount;
			int original_amount = accounts[name];
			accounts[name]+=amount;
			balances[original_amount].erase(name);
			balances[original_amount+amount].insert(name);			
		}
		else if (operation=='W')
		{
			char *name;
			cin >> name;
			int amount;
			cin >> amount;
			int original_amount = accounts[name];
			accounts[name]-=amount;
			balances[original_amount].erase(name);
			balances[original_amount-amount].insert(name);
		}
		else if (operation=='C')
		{
			char *name;
			cin >> name;
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
			i1++;
			i2--;
			while (i1!=i2)
			{
				print_set(i1);
				i1++;
			}
			print_set(i1);
		}
		else if (operation=='E')
		{
			stop=true;
		}
	}
	cout << illegal_count << endl;
}