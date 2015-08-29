#include <list>
#include <iostream>
using namespace std;
list<int>::iterator a1;
void execute(list<int>::iterator a2,list<int>::iterator a3)
{
	list<int> c;
	while(a2!=a3)
	{
		cout << "Before line :- " << *a1 << endl;
		c.push_back(*a2);
		cout << "After line :- " << *a1 << endl;
		a2++;
	}
}
int main()
{
	list<int> a;
	a.push_back(3);
	a.push_back(4);
	a.push_back(2);
	a.push_back(1);
	a1 = a.begin();
	list<int>::iterator a2=a.begin();
	a2++;
	a2++;
	list<int>::iterator a3=a.end();
	execute(a2,a3);
}
