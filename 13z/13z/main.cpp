#include<iostream>
#include<vector>
#include<deque>
#include<iterator>
#include<list>
using namespace std;

template<class T>
bool is_palindrom(T& a)
{
	T::iterator b = a.begin();
	T::iterator e = --a.end();
	for (b, e; b<=e; ++b, --e)
	{
		if (*b != *e)
			return false;
	}
	return true;
}

int main()
{
	cout<<"Vector<int>: "<<endl; 
	vector<int> v;
	v.push_back(28);
	v.push_back(4);
	v.push_back(4);
	v.push_back(28);
	vector<int>::iterator it;
	if(is_palindrom(v))
		cout<<"It is palindrom" <<endl;
	else
		cout<<"It is not palindrom"<<endl;
	for (it = v.begin(); it!=v.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl<<endl<<"Deque<double>: "<<endl;
	
	deque<double> s;
	s.push_back(14);
	s.push_back(15);
	s.push_back(15);
	s.push_back(12);
	if(is_palindrom(s))
		cout<<"It is palindrom" <<endl;
	else
		cout<<"It is not a palindrom"<<endl;
	for(deque<double>::iterator i=s.begin(); i!=s.end(); ++i)
		cout<<*i<<" ";
	cout<<endl;
	return 0;
}