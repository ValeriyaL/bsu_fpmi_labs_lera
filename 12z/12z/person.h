#include<iostream>
class person
{
private:
	char* name;
public:
	void getname(char*, int);
	char* putname();
	virtual void getmark(char*,float);
	virtual bool isRetake();
	~person();
};