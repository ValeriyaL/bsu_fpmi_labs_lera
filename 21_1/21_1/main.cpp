#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	char* s1 = "abgr fghggjtdjg";
	char symb = 'r';
	int res = 0;
	__asm
	{
		cld
			mov edi, s1
			mov esi, edi
			mov ecx, 0ffffffffh
			xor al, al
			repne scasb
			sub edi, esi
			dec edi
			mov edx, edi

			std
			mov esi, s1
			mov edi, s1
			dec edx
			add edi, edx
			mov ecx, edx
			mov al, symb
			repne scasb
			sub edi, esi
			cmp ecx, 0
			je nu
			inc edi
			inc edi
			mov res, edi
			jmp ex
		nu :
		mov esi, s1
			mov al, symb
			mov bl, [esi]
			cmp bl, al
			jne no_symb
			inc edi
			mov res, edi
			jmp ex
		no_symb :
		mov res, 0
		ex :
	}
	cout << res << endl;
	return 0;
}