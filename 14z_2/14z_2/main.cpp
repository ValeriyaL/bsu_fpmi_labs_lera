#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;

template<class P, class T>
bool compare(pair<P, T> p, pair<P, T> q )
{
	return p.first < q.first;
}

template<class P, class T, class Compare = less<P>, class C = map<P, T, Compare> >
class PriorityQueue
{
protected:
	C c;
public:
	typedef typename C::key_type key_type;
	typedef typename C::mapped_type mapped_type;
	typedef typename C::size_type size_type;
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	void enqueue(key_type prior, const mapped_type& val){c.insert(pair<P,T>(prior,val));} 
	void dequeue()
	{
		typename C::iterator it = c.begin();
		typename C::iterator i = c.end();
		C::iterator max = max_element(c.begin(), c.end(), compare<P, T>);
		c.erase(max);
	}
	mapped_type top ()
	{
		typename C::iterator it = c.begin();
		typename C::iterator i = c.end();
		C::iterator max = max_element(c.begin(), c.end(), compare<P, T>);
		return (*max).second; 
	}
};

int main()
{
	PriorityQueue<int, string> q1;	
	q1.enqueue(2,"aaa");
	q1.enqueue(1,"bbb");
	q1.enqueue(3,"ccc");
	q1.enqueue(4,"ddd");
	q1.dequeue(); //delete "ddd"
	cout<<"Size of q1: "<<q1.size()<<endl<<"The element with the biggest key: "<<q1.top()<<endl;
	return 0;
}
