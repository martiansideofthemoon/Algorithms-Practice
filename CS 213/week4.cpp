#include <vector>
#include <list>
#include <iostream>
#include <iterator>
using namespace std;
class data_structure
{
	int n;
	vector < list< list<int> >::iterator> count_list;
	vector < list<int>::iterator> list_iters;
	list < list<int> > count_values; 
public:
	data_structure(int number)
	{
		n=number;
		list <int> new_list;
		new_list.push_back(0); // count represented by list
		list <int>::iterator new_iterator = new_list.begin();
		for (int i=0;i<n;i++)
		{
			new_list.push_back(i);
			new_iterator++;
			list_iters.push_back(new_iterator);
		}
		count_values.push_back(new_list);
		for (int i=0;i<n;i++)
			count_list.push_back(count_values.begin());
		list <int>::iterator fill_list_iters = (*count_values.begin()).begin();
		int i=0;
		fill_list_iters++;
		while(fill_list_iters!=(*count_values.begin()).end())
		{
			list_iters[i]=fill_list_iters;
			fill_list_iters++;
			i++;	
		}
		print();
		//count_list.push_back();
	}
	void increment(int i)
	{
		list< list<int> >::iterator next_value = count_list[i];
		next_value++;
		int current_count = *((*count_list[i]).begin());
		if (next_value==count_values.end())
		{
			list <int> new_list;
			new_list.push_back(current_count+1);
			new_list.push_back(i);
			(*count_list[i]).erase(list_iters[i]);
			count_values.push_back(new_list);
			list_iters[i] =++(*(--count_values.end())).begin();
			//count_list[i]++;
			if (++((*count_list[i]).begin())==(*count_list[i]).end())
				count_values.erase(count_list[i]);
			count_list[i]=--count_values.end();	
		}
		else if (*(*next_value).begin()==current_count+1)
		{
			(*count_list[i]).erase(list_iters[i]);
			if (++((*count_list[i]).begin())==(*count_list[i]).end())
				count_values.erase(count_list[i]);
			count_list[i]=next_value;
			(*next_value).push_back(i);
			list_iters[i]=--(*next_value).end();
		}
		else
		{
			list <int> new_list;
			new_list.push_back(current_count+1);
			new_list.push_back(i);
			(*count_list[i]).erase(list_iters[i]);
			list<list<int> >::iterator new_pointer = count_values.insert(next_value,new_list);
			list_iters[i] =++((*new_pointer).begin());
			//count_list[i]++;
			if (++((*count_list[i]).begin())==(*count_list[i]).end())
				count_values.erase(count_list[i]);
			count_list[i]=new_pointer;
		}
		print();
	}
	void decrement(int i)
	{
		list< list<int> >::iterator prev_value = count_list[i];
		//prev_value--;
		int current_count = *((*count_list[i]).begin());
		if (prev_value==count_values.begin())
		{
			//cout << "block1" << endl;
			list <int> new_list;
			new_list.push_back(current_count-1);
			new_list.push_back(i);
			(*count_list[i]).erase(list_iters[i]);
			count_values.push_front(new_list);
			list_iters[i] =++(*(count_values.begin())).begin();
			//count_list[i]++;
			if (++((*count_list[i]).begin())==(*count_list[i]).end())
				count_values.erase(count_list[i]);
			count_list[i]=count_values.begin();	
		}
		else
		{
			prev_value--;
			if (*(*prev_value).begin()==current_count-1)
			{
				//cout << "block2" << endl;
				(*count_list[i]).erase(list_iters[i]);
				if (++((*count_list[i]).begin())==(*count_list[i]).end())
					count_values.erase(count_list[i]);
				count_list[i]=prev_value;
				(*prev_value).push_back(i);
				list_iters[i]=--(*prev_value).end();
			}
			else
			{
				//cout << "block3" << endl;
				list <int> new_list;
				new_list.push_back(current_count-1);
				new_list.push_back(i);
				(*count_list[i]).erase(list_iters[i]);
				list<list<int> >::iterator new_pointer = count_values.insert(count_list[i],new_list);
				list_iters[i] =++((*new_pointer).begin());
				//count_list[i]++;
				if (++((*count_list[i]).begin())==(*count_list[i]).end())
					count_values.erase(count_list[i]);
				count_list[i]=new_pointer;
			}
		}
		print();
	}
	void print()
	{
		cout << "Printing count of objects :- " << endl;
		for (int i=0;i<n;i++)
			cout << *((*count_list[i]).begin()) << ", ";
		cout << endl;
		cout << "Printing count_values list :- " << endl;
		list <list<int> >::iterator it = count_values.begin();
		while(it!=count_values.end())
		{
			list <int>::iterator it2 = (*it).begin();
			cout << "Elements with count " << *it2 << " :- ";
			it2++;
			while(it2!=(*it).end())
			{
				cout << *it2 << ", ";
				it2++;
			}
			cout << endl;
			it++;
		}
		cout << endl;
	}

};
int main()
{
	data_structure d1(5);
	
	d1.decrement(1);
	d1.decrement(2);
	d1.decrement(3);
	d1.decrement(1);
	d1.decrement(3);
	d1.decrement(2);
	d1.decrement(1);
	d1.decrement(4);
	d1.decrement(1);
	d1.decrement(0);
	d1.decrement(0);
	d1.decrement(0);
	d1.decrement(1);
}