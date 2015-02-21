#include <iostream>
#include<string>
using namespace std;
class person
{
protected:
	string name;
public:
	virtual void getinfo();
	virtual void  putinfo();
};

class student: public person
{
private:
	float mark;
public:
	void getinfo();
	void putinfo();
};