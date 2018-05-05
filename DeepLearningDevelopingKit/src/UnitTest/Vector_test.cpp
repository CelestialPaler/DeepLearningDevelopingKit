/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	            Vector Test   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
// #define VectorDebug

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

#ifdef VectorDebug

// Header files
#include <iostream>
#include "..\MathLib\MathLib.h"

using namespace std;
using namespace MathLib;

int main()
{
	/*
	Vector<int> debug1(6);
	Vector<int> debug2(3);
	debug1 - debug2;
	*/


	Vector<int> input;
	input.Init(5);
	for (size_t i = 0; i < 5; i++) 
		input(i) = i;

	Vector<int> weight;
	weight.Init(5);
	for (size_t i = 0; i < 5; i++)
		weight(i) = i;

	int bias = 2, ans = 0;

	input = input * 2;

	cout << input << weight << bias << std::endl;

	ans = Vector<int>::DotProduct(input, weight) + bias;
	cout << ans << std::endl;

	Vector<double> test(5, VectorType::Random);
	cout << test<< test.Sum();
	system("pause");
	return 0;
}
#endif // MathDynamicDebug

