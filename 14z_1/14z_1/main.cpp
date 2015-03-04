#include<iostream>
#include<list>
#include<algorithm>
#include<iterator>
#include<vector>
#include<deque>
using namespace std;

template<class T>
T& mergeSort(T& cont)
{
	if (cont.size()<=1)
		return cont;	
	T left,right,first,second;
	T::iterator cur = cont.begin();
	for (int i =0; i!=(cont.size()/2); i++)
	{
		cur++;
	}
	left.assign(cont.begin(), cur);
	right.assign(cur, cont.end());
	first = mergeSort(left);
	second = mergeSort(right);
	merge(first.begin(), first.end(), second.begin(),second.end(),cont.begin());
	return cont;
}

int main()
{
	list<double> l;
	l.push_back(5.22);
	l.push_back(28.3);
	l.push_back(28.5);
	l.push_back(14);
	l.push_back(12);
	list<double>::iterator it;
	cout<<"List before sorting: "<<endl;
	for (it = l.begin(); it!=l.end(); ++it)
	{
		cout<<*it<<"  ";
	}
	cout<<endl;
	mergeSort(l);
	cout<<"List after sorting: "<<endl;
	for (it = l.begin(); it!=l.end(); ++it)
	{
		cout<<*it<<"  ";
	}
	cout<<endl;
	return 0;
}