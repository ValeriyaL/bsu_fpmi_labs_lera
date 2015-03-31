#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
class Transport
{
private:
	set<string> all_stops;
	set<int> list_of_numbers;
	set<string> empty_stops;
	multimap<int,int> list_of_transport;
	multimap<int, pair<int, vector<string> > > transport;
public:
	void Transport::addRoute(int, int, vector<string>::iterator, vector<string>::iterator);
	void deleteRoute(int, int);
	void addStop(string);
	void deleteStop(string);
	int number_of_routes();
	int number_of_stops();
	pair<multimap<int,int>::iterator, multimap<int,int>::iterator> routes_of_stop(string);
	pair<set<int>::iterator,set<int>::iterator> list_of_routs(int, int, int);
	pair<set<string>::iterator,set<string>::iterator> empty_st();
	string max_stop();
};