#include<iostream>
#include "person.h"
using namespace std;
int main()
{
	person* A[3];
	A[0] = new student;
	A[1] = new student;
	A[2] = new person;
	for (int i=0; i<3; i++)
	{
		A[i]->getinfo();
	}
	for (int i=0; i<3; i++)
	{
		A[i]->putinfo();
	}
	return 0;
}