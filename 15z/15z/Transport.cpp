#include "Transport.h"
#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<map>
#include<set>
#include<algorithm>


void Transport::addRoute(int numb, int mode, vector<string>::iterator begin, vector<string>::iterator end)
{
	multimap<int, pair<int, vector<string> > >::iterator tr = transport.begin();
	bool is_find = false;
	pair<multimap<int, pair<int, vector<string> > >::iterator,multimap<int, pair<int, vector<string> > >::iterator> pair_it = transport.equal_range(mode);
	if(pair_it.first!=transport.end())
		while (tr!=pair_it.second)
		{
			if(tr->second.first == numb)
			{
				is_find = true;
				break;
			}
			tr++;
		}
	if(!is_find)
	{
		all_stops.insert(begin,end);
		vector<string> stops;
		for(begin; begin!=end; begin++)
			stops.push_back(*begin);
		transport.insert(make_pair(mode, make_pair(numb, stops)));
	}
}

void Transport::deleteRoute(int numb, int mode)
{
	multimap<int, pair<int, vector<string> > >::iterator find = transport.find(mode);
	while(find != transport.end() && find->first == mode)
	{
		if (find->second.first == numb)
		{
			transport.erase(find);
			break;
		}
		else find++;
	}
}

void Transport::addStop(string s)
{
	all_stops.insert(s);
}

void Transport::deleteStop(string name)
{
	set<string>::iterator find1 = all_stops.find(name);
	if(find1!=all_stops.end())
		all_stops.erase(find1);
	multimap<int, pair<int, vector<string> > >::iterator beg = transport.begin();
	for(beg; beg!=transport.end(); beg++)
	{	
		vector<string>::iterator find2 = find(beg->second.second.begin(),beg->second.second.end(),name);
		if(find2!=beg->second.second.end())
		{
			beg->second.second.erase(find2);
			if(beg->second.second.empty())  
			{
				multimap<int, pair<int, vector<string> > >::iterator i1=beg;
				beg++;
				transport.erase(i1);
				beg--;
			}
		}
	}
}

int Transport::number_of_routes()
{
	return transport.size();
}

int Transport::number_of_stops()
{
	return all_stops.size();
}
pair<multimap<int,int>::iterator, multimap<int,int>::iterator> Transport::routes_of_stop(string name)
{
	list_of_transport.clear();
	multimap<int, pair<int, vector<string> > >::iterator beg = transport.begin();
	for(beg; beg!=transport.end(); beg++)
	{	
		vector<string>::iterator find1 = find(beg->second.second.begin(),beg->second.second.end(),name);
		if(find1!=beg->second.second.end())
		{
			list_of_transport.insert(pair<int,int>(beg->first, beg->second.first));
		}
	}
	return make_pair(list_of_transport.begin(),list_of_transport.end());
}

pair<set<int>::iterator,set<int>::iterator> Transport::list_of_routs(int vid, int b, int e)
{
	list_of_numbers.clear();
	pair<multimap<int, pair<int, vector<string> > >::iterator,multimap<int, pair<int, vector<string> > >::iterator> pair1 = transport.equal_range(vid);
	for(multimap<int, pair<int, vector<string> > >::iterator iter = pair1.first; iter!= pair1.second; iter++)
	{
		if(iter->second.first >=b && iter->second.first<=e)
			list_of_numbers.insert(iter->second.first);
	}
	return make_pair(list_of_numbers.begin(),list_of_numbers.end());
}

pair<set<string>::iterator,set<string>::iterator> Transport::empty_st()
{
	empty_stops.clear();
	set<string>::iterator iter = all_stops.begin();
	for(iter; iter!=all_stops.end(); iter++)
	{
		bool empty = true;
		multimap<int, pair<int, vector<string> > >::iterator beg = transport.begin();
		for(beg; beg!=transport.end(); beg++)
		{	
			vector<string>::iterator find1 = find(beg->second.second.begin(),beg->second.second.end(),*iter);
			if(find1!=beg->second.second.end())
			{
				empty = false;
				break;
			}
		}
		if(empty)
			empty_stops.insert(*iter);
	}
	return make_pair(empty_stops.begin(), empty_stops.end());
}

string Transport::max_stop()
{
	set<string>::iterator st = all_stops.begin();
	int max_route=0;
	set<string>::iterator ret = all_stops.begin();
	for(st; st!=all_stops.end(); st++)
	{
		int route=0;
		multimap<int, pair<int, vector<string> > >::iterator beg = transport.begin();
		for(beg; beg!=transport.end(); beg++)
		{	
			vector<string>::iterator find1 = find(beg->second.second.begin(),beg->second.second.end(),*st);
			if(find1!=beg->second.second.end())
			{
				route++;
			}
		}
		if(route>max_route)
		{
			max_route=route;
			ret = st;
		}
	}
	return *ret;
}