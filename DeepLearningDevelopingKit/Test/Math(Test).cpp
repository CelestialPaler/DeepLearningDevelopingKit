﻿/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	             Math Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header FIle
#include <iostream>

#include "..\MathLib\MathLib.h"
#include "..\Util\Log.h"

#ifdef USING_STATIC_MATHLIB
using namespace MathLibStatic;
#define MathStaticDebug
#endif // USING_STATIC_MATHLIB

#ifdef USING_DYNAMIC_MATHLIB
using namespace MathLibDynamic;
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
	Matrix<int> A(3, 3);
	Matrix<int> B(3, 3);
	Matrix<int> C(2, 2);

	A(1, 1) = 6;
	B(0, 0) = 3;
	B(1, 1) = 3;
	B(2, 2) = 3;
	C(0, 0) = 1;

	cout << A << B;

	A = A + B;
	C = C + 1;

	cout << A << B << C;

	Vector<int> a(3);
	Vector<int> b(3);
	Vector<int> c(2);

	a(0) = 1;
	a(2) = 1;
	b(2) = 2;

	a = a + b;

	cout << a << b;

	system("pause");
	return 0;
}
#endif // MathDynamicDebug

