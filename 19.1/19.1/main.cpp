#include<iostream>
#include<Windows.h>
using namespace std;
int main()
{
	float result = 0.0, den = 1.0, mult1 = 1.0, factorial = 1.0, mult2 = 1.0, degree = 1.0, x, mo = -1.0, two = 2.0, counter = 0.0;
	int n;
	cout << "Please input x: ";
	cin >> x;
	cout << "Please input n: ";
	cin >> n;

	__asm
	{
		mov ecx, n
		cmp ecx,0
		je exz
		finit
		cycle :
		//(-1)^m
		FLD mo
		FLD degree
		FMUL ST(0), ST(1)
		FST degree
		finit
		//x^m
		FLD x
		FLD den
		FMUL ST(0), ST(1)
		FST den
		finit
		//2+chisl/zn
		FLD mult1
		FLD two
		FLD den
		FLD degree
		FDIV ST(0), ST(1)
		FADD ST(0), ST(2)
		FMUL ST(0), ST(3)
		FST mult1
		finit
		//factorial
		FLD counter
		FLD1
		FADD ST(0), ST(1)
		FST counter
		finit
		FLD counter
		FLD factorial
		FMUL ST(0), ST(1)
		FST factorial
		finit
		//pr1 / zn2
		FLD factorial
		FLD mult1
		FDIV ST(0), ST(1)
		FLD mult2
		FMUL ST(0), ST(1)
		FST mult2
		finit
		//result
		FLD mult2
		FLD result
		FADD ST(0), ST(1)
		FST result
		finit
		loop cycle
		jmp ex
	exz:
		mov result,0
	ex:
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