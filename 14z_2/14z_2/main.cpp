#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;



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
	void enqueue(P prior, const T& val){c.insert(pair<P,T>(prior,val));} 
	void dequeue()
	{
		typename C::iterator i = --c.end();
		c.erase(i);
	}
	mapped_type top ()
	{
		typename C::iterator i = --c.end();
		return (*i).second; 
	}
};

int main()
{
	PriorityQueue<int, string> q1;	
	q1.enqueue(2,"aaa");
	q1.enqueue(1,"bbb");
	q1.enqueue(3,"ccc");
	q1.enqueue(4,"ddd");
	/*q1.dequeue(); *///delete "ddd"
	cout<<"Size of q1: "<<q1.size()<<endl<<"The element with the biggest key: "<<q1.top()<<endl;
	return 0;
}
