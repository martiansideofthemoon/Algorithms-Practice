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
	list< list<int> >::iterator zero_pointer;
public:
	data_structure(int number)
	{
		n=number;
		list <int> new_list;
		new_list.push_back(0); // count represented by list
		new_list.push_back(n);
		//list <int>::iterator new_iterator = new_list.begin();
		for (int i=0;i<n;i++)
		{
			new_list.push_back(i);
			//new_iterator++;
			//list_iters.push_back(new_iterator);
		}
		count_values.push_back(new_list);
		for (int i=0;i<n;i++)
			count_list.push_back(count_values.begin());
		list <int>::iterator fill_list_iters = (*count_values.begin()).begin();
		int i=0;
		fill_list_iters++;
		fill_list_iters++;
		//fill_list_iters++;
		while(fill_list_iters!=(*count_values.begin()).end())
		{
			list_iters.push_back(fill_list_iters);
			fill_list_iters++;
			i++;	
		}
		for (int i=0;i<n;i++)
			cout << *list_iters[i] << endl;
		zero_pointer = count_values.begin();
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
			new_list.push_back(1);
			new_list.push_back(i);
			(*count_list[i]).erase(list_iters[i]);
			(*(++((*count_list[i]).begin())))--;
			count_values.push_back(new_list);
			list_iters[i] =++(++(*(--count_values.end())).begin());
			//count_list[i]++;
			if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
				count_values.erase(count_list[i]);
			count_list[i]=--count_values.end();	
		}
		else if (*(*next_value).begin()==current_count+1)
		{
			(*count_list[i]).erase(list_iters[i]);
			(*(++((*count_list[i]).begin())))--;
			if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
				count_values.erase(count_list[i]);
			count_list[i]=next_value;
			(*next_value).push_back(i);
			(*(++(*next_value).begin()))++;
			list_iters[i]=--(*next_value).end();
		}
		else
		{
			list <int> new_list;
			new_list.push_back(current_count+1);
			new_list.push_back(1);
			new_list.push_back(i);
			(*count_list[i]).erase(list_iters[i]);
			(*(++((*count_list[i]).begin())))--;
			list<list<int> >::iterator new_pointer = count_values.insert(next_value,new_list);
			list_iters[i] =++++((*new_pointer).begin());
			//count_list[i]++;
			if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
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
			cout << "block1" << endl;
			list <int> new_list;
			new_list.push_back(current_count-1);
			new_list.push_back(1);
			new_list.push_back(i);
			(*count_list[i]).erase(list_iters[i]);
			(*(++((*count_list[i]).begin())))--;
			count_values.push_front(new_list);
			list_iters[i] =++++(*(count_values.begin())).begin();
			//count_list[i]++;
			if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
				count_values.erase(count_list[i]);
			count_list[i]=count_values.begin();	
		}
		else
		{
			prev_value--;
			if (*(*prev_value).begin()==current_count-1)
			{
				cout << "block2" << endl;
				(*count_list[i]).erase(list_iters[i]);
				(*(++((*count_list[i]).begin())))--;
				if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
					count_values.erase(count_list[i]);
				count_list[i]=prev_value;
				(*prev_value).push_back(i);
				(*(++(*prev_value).begin()))++;
				list_iters[i]=--(*prev_value).end();
			}
			else
			{
				cout << "block3" << endl;
				list <int> new_list;
				new_list.push_back(current_count-1);
				new_list.push_back(1);
				new_list.push_back(i);
				(*count_list[i]).erase(list_iters[i]);
				(*(++((*count_list[i]).begin())))--;
				list<list<int> >::iterator new_pointer = count_values.insert(count_list[i],new_list);
				list_iters[i] =++++((*new_pointer).begin());
				//count_list[i]++;
				if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
					count_values.erase(count_list[i]);
				count_list[i]=new_pointer;
			}
		}
		print();
	}
	void reset(int i)
	{
		int current_count = *((*count_list[i]).begin());
		(*count_list[i]).erase(list_iters[i]);
		(*(++((*count_list[i]).begin())))--;
		if (++(++((*count_list[i]).begin()))==(*count_list[i]).end() && current_count!=0)
			count_values.erase(count_list[i]);
		count_list[i]=zero_pointer;
		//cout << "yolo" << endl;
		(*zero_pointer).push_back(i);
		(*(++(*zero_pointer).begin()))++;
		list_iters[i]=--(*zero_pointer).end();	
		print();
	}
	int count(int i)
	{
		return *((*count_list[i]).begin());
	}
	int findMax()
	{
		list<list <int> >::iterator check_empty = --count_values.end();
		if (++(*check_empty).begin()==(*check_empty).end())	
			check_empty--;
		return *((*check_empty).begin());
	}
	void printMax()
	{
		list<list <int> >::iterator check_empty = --count_values.end();
		if (++(*check_empty).begin()==(*check_empty).end())	
			check_empty--;
		list<int>::iterator max_list= (*check_empty).begin();
		max_list++;
		max_list++;
		while (max_list!=(*check_empty).end())
		{
			cout << *max_list << endl;
			max_list++;
		}
	}
	int numMax()
	{
		list<list <int> >::iterator check_empty = --count_values.end();
		if (++(*check_empty).begin()==(*check_empty).end())	
			check_empty--;
		return *(++(*check_empty).begin());
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
	d1.reset(3);
	d1.reset(1);
	d1.reset(2);
	d1.reset(4);
	d1.reset(0);
	d1.reset(0);
	cout << "Find max is " << d1.numMax() << endl;
	
	d1.printMax();
	//d1.reset(1);
	cout << "max is " << d1.findMax();
}