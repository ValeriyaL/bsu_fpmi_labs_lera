#include "person.h"
#include <iostream>
#include<cstring>
#include<string>

void person::getinfo()
{
	cout<<"Please input name: ";
	cin>>name;
}


void person::putinfo()
{
	cout<<"Name: "<<name<<endl;
}

void student::getinfo()
{
	person::getinfo();
	cout<<"Please input mark: ";
	cin>>mark;
}


void student::putinfo()
{
	person::putinfo();
	cout<<"Mark: "<<mark<<endl;
}