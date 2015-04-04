#include<iostream>
#include<vector>
#include"Transport.h"
#include<iterator>
#include<string>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

int main()
{
	Transport X;
	char answ = 'y';
	cout<<"Please input number of modes: ";
	int numb_of_modes;
	cin>>numb_of_modes;
	string* str = new string[numb_of_modes];
	for(int i = 0; i<numb_of_modes; i++)
	{
		cout<<"Please input "<<i+1<<" mode: ";
		cin>>str[i];
	}
	do {
		cout<<"Please input mode:" <<endl;
		for(int i = 0; i<numb_of_modes; i++)
		{
			cout<<i+1<<" - "<<str[i]<<endl;
		}
		int mode; cin>>mode;
		int number;
		cout<<"Please input number: "; cin>>number;
		int stops;
		cout<<"Please input number of stops: "; cin>>stops;
		cout<<"Please input stops: ";
		vector<string> stop;
		for(int i=0; i<stops; i++)
		{
			string s;
			cin>>s;
			stop.push_back(s);
		}
		X.addRoute(number,mode,stop.begin(), stop.end());
		cout<<"Do you want to add one more route?(y/n):  ";
		cin>>answ;
	} while(answ != 'n');
	cout<<"Do you want to delete route?(y/n): ";
	cin>>answ;
	while(answ == 'y')
	{
		cout<<"Please input mode and number of transport you would like to delete: ";
		int mode, number;
		cin>>mode>>number;
		X.deleteRoute(number,mode);
		cout<<"Do you want to delete one more route?(y/n): ";
		cin>>answ;
	}
	cout<<"Do you want to add stops?(y/n): ";
	cin>>answ;
	while(answ == 'y')
	{
		string stop;
		cout<<"Please input the stop you want to add: ";
		cin>>stop;
		X.addStop(stop);
		cout<<"Do you want to add one more stop?(y/n): ";
		cin>>answ;
	}
	cout<<"Do you want to delete stop?(y/n): ";
	cin>>answ;
	while(answ=='y')
	{
		string stop;
		cout<<"Please input the stop you want to delete: ";
		cin>>stop;
		X.deleteStop(stop);
		cout<<"Do you want to delete one more stop?(y/n): ";
		cin>>answ;
	}
	int n = X.number_of_routes();
	cout<<"Number of routes: "<<n<<endl;
	n = X.number_of_stops();
	cout<<"Number of stops: "<<n<<endl;
	answ = 'y';
	while(answ == 'y')
	{
		cout<<"Please input stop for what you want to have list of routes: ";
		string stop; cin>>stop;
		multimap<int,int> m;
		pair<multimap<int,int>::iterator,multimap<int,int>::iterator> pair1 = X.routes_of_stop(stop);
		m.insert(pair1.first, pair1.second);
		for(multimap<int,int>::iterator it = m.begin(); it!=m.end(); it++)
		{
			for(int i = 0; i<numb_of_modes; i++)
			{
				if(it->first == i+1)
					cout<<str[i]<<" ";
			}
			cout<<it->second<<endl;
		}
		cout<<"Do you want to have list of routes for another stop?(y/n): ";
		cin>>answ;
	}
	answ = 'y';
	while(answ == 'y')
	{
		int mode, n1, n2;
		cout<<"Please input mode and 2 numbers of transport: ";
		cin>>mode>>n1>>n2;
		set<int> s1;
		pair<set<int>::iterator,set<int>::iterator> p2 = X.list_of_routs(mode,n1,n2);
		s1.insert(p2.first,p2.second);
		for(set<int>::iterator ii = s1.begin(); ii!=s1.end(); ii++)
			cout<<*ii<<" ";
		cout<<endl<<"Do you want to have list for another mode?(y/n): ";
		cin>>answ;
	}
	cout<<"List of empty stops: ";
	set<string> set2;
	pair<set<string>::iterator,set<string>::iterator> pair3 = X.empty_st();
	set2.insert(pair3.first,pair3.second);
	for(set<string>::iterator i2 = set2.begin(); i2!=set2.end(); i2++)
		cout<<*i2<<" ";
	cout<<endl<<"Stop with the largest number of transport: "; 
	string ss = X.max_stop();
	cout<<ss<<endl;
	return 0;
}