#include<iostream>
using namespace std;
int main()
{
	int size1, size2, mult_size = 1, summ_size;
	/*cout << "Please input number of coefficients of your first polynom: ";
	cin >> size1;
	cout << "Please input coefficient of your first polynom: ";
	int polyn1[10000];
	for (int i = 0; i < size1; i++)
	cin >> polyn1[i];
	cout << "Please input number of coefficients of your second polynom: ";
	cin >> size2;
	cout << "Please input coefficient of your second polynom: ";
	int polyn2[10000];
	for (int i = 0; i < size2; i++)
	cin >> polyn2[i];*/
	int polyn1[100] = { 1, -10, 3, -1 };
	int polyn2[100] = { 1, 8, -1, 4, 5 };
	size1 = 4;
	size2 = 5;
	int summ[10000] = { 0, };
	int mult[10000] = { 0, };
	__asm
	{
		//summ
		mov eax, size1
		mov ecx, size2
		cmp eax, ecx
		jg first
		mov summ_size, ecx
		jmp sum
	first :
		mov summ_size, eax
	sum :
		cmp size1, 0
		je second
		mov ecx, size1
		xor ebx, ebx
	pol1 :
		mov eax, polyn1[ebx * 4]
		mov summ[ebx * 4], eax
		inc ebx
		loop pol1
	second :
		cmp size2, 0
		je end1
		mov ecx, size2
		xor ebx, ebx
	pol2 :
		mov eax, polyn2[ebx * 4]
		add summ[ebx * 4], eax
		inc ebx
		loop pol2
	end1 :
		cmp summ_size, 0
		jne sec_z
		mov summ_size, 1
		//mult
	sec_z :
		cmp size1, 0
		je exit1
		cmp size2, 0
		je exit1
		mov eax, size1
		dec eax
		add eax, size2
		mov mult_size, eax
		mov ebx, size1
	zer1 :
		cmp ebx, mult_size
		je zer2
		mov polyn1[ebx * 4], 0;
		inc ebx
		jmp zer1
	zer2 :
		mov ebx, size2
	zerr :
		cmp ebx, mult_size
		je multip
		mov polyn2[ebx * 4], 0;
		inc ebx
		jmp zerr
	multip :
		//mult[k]=mult[k]+first[i]*second[k-i];
		xor edi, edi
	mult1 :
		xor esi, esi
	mult2 :
		mov eax, polyn1[esi * 4]
		mov ebx, edi
		sub ebx, esi
		xor edx, edx
		mov ecx, polyn2[ebx * 4]
		imul ecx
		add mult[edi * 4], eax
		inc esi
		cmp esi, edi
		jg vneshn
		jmp mult2
	vneshn :
		inc edi
		cmp edi, mult_size
		jg exit1
		jmp mult1
		jmp exit1
	exit1 :
	}
	for (int i = 0; i < summ_size; i++)
		cout << summ[i] << " ";
	cout << endl;
	for (int i = 0; i < mult_size; i++)
		cout << mult[i] << " ";
	cout << endl;
	return 0;
}