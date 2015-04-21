#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	int number, one=1, two=2;
	bool is_simple = 1;
	cout << "Please input your number: ";
	cin >> number;
	__asm
	{
		mov eax, number
		cmp eax,2
		je ex
		mul one
		div two
		mov ecx, eax
		dec ecx
		mov esi,1
	mark1:
		inc esi
		mov eax,number
		mov edx,0
		div esi
		cmp edx,0
		je not_simple
		loop mark1
		jmp ex
	not_simple:
		mov is_simple, 0
	ex:
	}
	cout << is_simple << endl;
	return 0;
}