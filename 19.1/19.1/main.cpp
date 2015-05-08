#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	double result = 0.0, den = 1.0, mult1 = 1.0, mult2 = 1.0, x, two = 2.0;
	int degree = 1, mo = -1, counter = 0, factorial = 1;
	int n;
	cout << "Please input x: ";
	cin >> x;
	cout << "Please input n: ";
	cin >> n;
	__asm
	{
		mov ecx, n
		cmp ecx, 0
		je ex
	cycle :
		finit
		//(-1)^m
		mov eax, degree
		xor edx, edx
		imul mo
		mov degree, eax
		//x^m
		FLD x
		FLD den
		FMUL
		FST den
		//2+chisl/zn
		FLD two
		FILD degree
		FLD den
		FDIV
		FADD
		FLD mult1
		FMUL
		FST mult1
		//factorial
		inc counter
		mov eax, counter
		mul factorial
		mov factorial, eax
		//pr1 / zn2
		FLD mult1
		FILD factorial
		FDIV
		FLD mult2
		FMUL
		FST mult2
		//result
		FLD mult2
		FLD result
		FADD
		FST result
		loop cycle
	ex :
	}
	cout << result << endl;
	return 0;
}


/* for (int i = 0; i<n; i++)
{
ch *= -1;
zn *= x;
pr1 *= 2 + ch / zn;
zn2 *= (i + 1);
pr2 *= pr1 / zn2;
rez += pr2;
}
cout << rez << endl;*/