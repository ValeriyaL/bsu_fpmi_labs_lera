#include<iostream>
#include "person.h"
using namespace std;

int main()
{
	person A;
	char n[20];
	cout<<"Please input name: "; 
	cin>>n;
	A.getname(n,20);
	cout<<A.putname()<<endl;
	return 0;
}