#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	int number, one=1, two=2, rad;
	bool is_simple = 1;
	cout << "Please input your number: ";
	cin >> number;
	__asm
	{
		mov ecx,1
	start:
		inc ecx
		mov eax,ecx 
		mul eax
		cmp eax,number 
		jg ex
		mov eax,number
		xor edx,edx
		div ecx
		cmp edx,0
		je not_simple
		jmp start
	not_simple:
		mov is_simple, 0
	ex :
	}
	cout << is_simple << endl;
	return 0;
}