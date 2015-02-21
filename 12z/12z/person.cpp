#include "person.h"
#include <iostream>
#include<cstring>

void person::getname(char* n, int num)
{
	name = new char [num +1 ];
	strcpy(name,n);
}

person::~person()
{
	delete [] name;
}

char* person::putname()
{
	return name;
}

void person::getmark(char* ar,float n)
{}

bool person::isRetake()
{
	return true;
}