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
	map<int, map<int, vector<string> > >::iterator find1 = transport.find(mode);
	if(find1==transport.end())
	{
		all_stops.insert(begin,end);
		vector<string> stops;
		for(begin; begin!=end; begin++)
			stops.push_back(*begin);
		map<int, vector<string> > m1;
			m1.insert(make_pair(numb,stops));
		transport.insert(make_pair(mode,m1));
	}
	else
	{
		map<int, vector<string> >::iterator find2 = find1->second.find(numb);
		if(find2==find1->second.end())
		{
			all_stops.insert(begin,end);
			vector<string> stops;
			for(begin; begin!=end; begin++)
				stops.push_back(*begin);
			find1->second.insert(make_pair(numb,stops));
		}
	}
}

void Transport::deleteRoute(int numb, int mode)
{
	map<int, map<int, vector<string> > >::iterator find1 = transport.find(mode);
	if(find1!=transport.end())
	{
		map<int, vector<string> >::iterator find2 = find1->second.find(numb);
		if(find2!=find1->second.end())
			find1->second.erase(find2);
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
	map<int, map<int, vector<string> > >::iterator beg = transport.begin();
	for(beg; beg!=transport.end();)
	{	
		bool b1 = true;
		map<int, vector<string> >::iterator beg2 = beg->second.begin();
		for(beg2; beg2!=beg->second.end();)
		{
			bool b = true;
			vector<string>::iterator find2 = find(beg2->second.begin(),beg2->second.end(),name);
			if(find2!=beg2->second.end())
			{
				beg2->second.erase(find2);
				if(beg2->second.empty())
				{
					map<int, vector<string> >::iterator i1 = beg2++;
					if(i1 == beg->second.begin())
					{
						b = false;
						beg->second.erase(i1);
					}
					else
					{
						beg->second.erase(i1);
						beg2--;
					}
				}
			}
			if(b)
				beg2++;
		}
		if(beg->second.empty())
		{
			map<int, map<int, vector<string> > >::iterator i2 = beg++;
			if(i2 == transport.begin())
			{
				b1 = false;
				transport.erase(i2);
			}
			else
			{
				transport.erase(i2);
				beg--;
			}
		}
		if(b1)
			beg++;
	}
}

int Transport::number_of_routes()
{
	size = 0;
	map<int, map<int, vector<string> > >::iterator size1 = transport.begin();
	for(size1; size1!=transport.end(); size1++)
		size += size1->second.size();
	return size;
}

int Transport::number_of_stops()
{
	return all_stops.size();
}
pair<multimap<int,int>::iterator, multimap<int,int>::iterator> Transport::routes_of_stop(string name)
{
	list_of_transport.clear();
	map<int, map<int, vector<string> > >::iterator beg = transport.begin();
	for(beg; beg!=transport.end(); beg++)
	{	
		map<int, vector<string> >::iterator beg2 = beg->second.begin();
		for(beg2; beg2!=beg->second.end(); beg2++)
		{
			vector<string>::iterator find1 = find(beg2->second.begin(),beg2->second.end(),name);
			if(find1!=beg2->second.end())
				list_of_transport.insert(pair<int,int>(beg->first, beg2->first));
		}
	}
	return make_pair(list_of_transport.begin(),list_of_transport.end());
}

pair<set<int>::iterator,set<int>::iterator> Transport::list_of_routs(int vid, int b, int e)
{
	list_of_numbers.clear();
	map<int, map<int, vector<string> > >::iterator find1 = transport.find(vid);
	if(find1!=transport.end())
	{
		map<int, vector<string> >::iterator beg = find1->second.begin();
		for(beg; beg!=find1->second.end(); beg++)
		{
			if(beg->first >= b && beg->first <= e)
				list_of_numbers.insert(beg->first);
		}
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
		map<int, map<int, vector<string> > >::iterator beg = transport.begin();
		for(beg; beg!=transport.end(); beg++)
		{	
			map<int, vector<string> >::iterator beg2 = beg->second.begin();
			for(beg2; beg2!=beg->second.end(); beg2++)
			{
				vector<string>::iterator find1 = find(beg2->second.begin(), beg2->second.end(), *iter);
				if(find1!=beg2->second.end())
				{
					empty = false;
					break;
				}
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
	if (st == all_stops.end())
		return "";
	set<string>::iterator ret = all_stops.begin();
	for(st; st!=all_stops.end(); st++)
	{
		int route=0;
		map<int, map<int, vector<string> > >::iterator beg = transport.begin();
		for(beg; beg!=transport.end(); beg++)
		{	
			map<int, vector<string> >::iterator beg2 = beg->second.begin();
			for(beg2; beg2!=beg->second.end(); beg2++)
			{
				vector<string>::iterator find1 = find(beg2->second.begin(), beg2->second.end(), *st);
				if(find1!=beg2->second.end())
				{
					route++;
				}
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