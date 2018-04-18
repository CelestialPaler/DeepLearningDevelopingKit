/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	             Math Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header FIle
#include <iostream>

#include "..\MathLib\MathLib.h"

#ifdef USING_STATIC_MATHLIB
using namespace MathLibStatic;
#define MathStaticDebug
#endif // USING_STATIC_MATHLIB

#ifdef USING_DYNAMIC_MATHLIB
using namespace MathLib;
#define MathDynamicDebug
#endif // USING_DYNAMIC_MATHLIB

using namespace std;

#ifdef MathStaticDebug
int main()
{
	Matrix<int, 3, 3> A, B, C, D, E;

	A(1, 1) = 6;
	B(0, 0) = 3;
	B(1, 1) = 3;
	B(2, 2) = 3;

	C = A + B;
	C.PrintToConsole();
	C = C + 1;
	C.PrintToConsole();
	D = A - B;
	D.PrintToConsole();
	E = A * B;
	E.PrintToConsole();
	int data[3][3] = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	Matrix<int, 3, 3> F(data);
	F.PrintToConsole();

	F = F * 3;
	F.PrintToConsole();

	Vector<int, 3> a, b, c;
	a(0) = 3;
	a(1) = 3;
	b(0) = 4;

	a.PrintToConsole();
	b.PrintToConsole();

	a = b;

	(a + b).PrintToConsole();

	system("pause");
	return 0;
}
#endif // MathStaticDebug

#ifdef MathDynamicDebug
int main()
{
	cout << PrintInfo() << "Math Dynamic Test" << endl;
	int data[][] = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	Matrix<int> A(3, 3);
	Matrix<int> B(3, 3);
	Matrix<int> C(3, 3);

	Matrix<int> D(3, 2);
	Matrix<int> E(2, 3);
	Matrix<int> F(3, 3);

	B(0, 0) = 3;
	B(1, 1) = 3;
	B(2, 2) = 3;
	C(0, 0) = 1;

	D(1, 1) = 6;
	E(0, 0) = 3;
	E(1, 1) = 3;
	E(2, 2) = 3;

	cout << A << B;

	A = A + B;
	C += A;
	C -= 2;

	cout << A << B << C;

	F = D * E;
	cout << D << E << F;

	system("pause");
	return 0;
}
#endif // MathDynamicDebug

