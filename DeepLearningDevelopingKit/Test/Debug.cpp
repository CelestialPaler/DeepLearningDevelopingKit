/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Debug   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#include "..\MathLib\MathLib.h"
#include "..\Nerual\Node.h"
#include "..\Nerual\Layer.h"

#include <iostream>

using namespace MathLib;
using namespace Nerual;
using namespace std;
// #define MathDebug
// #define NodeDebug
#define LayerDebug

#ifdef MathDebug
int main()
{
	cout << "Math Uint Test" << endl;
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
#endif // Debug

#ifdef NodeDebug
int main()
{
	cout << "Node Uint Test" << endl;
	InputNode InputNode1;
	InputNode InputNode2;

	HiddenNode<2> HiddenNode1;
	HiddenNode<2> HiddenNode2;
	HiddenNode<2> HiddenNode3;
	HiddenNode<2> HiddenNode4;
	HiddenNode<2> HiddenNode5;

	OutputNode<5> OutputNode;

	double data[2] = { 1,0 };
	Vector<double, 2> Input(data);
	Vector<double, 5> temp;

	temp(0) = (Input * HiddenNode1.weight).Sum() - HiddenNode1.bias;
	temp(1) = (Input * HiddenNode2.weight).Sum() - HiddenNode2.bias;
	temp(2) = (Input * HiddenNode3.weight).Sum() - HiddenNode3.bias;
	temp(3) = (Input * HiddenNode4.weight).Sum() - HiddenNode4.bias;
	temp(4) = (Input * HiddenNode5.weight).Sum() - HiddenNode5.bias;

	double ans = (temp * OutputNode.weight).Sum() - OutputNode.bias;

	HiddenNode1.weight.PrintToConsole();
	HiddenNode2.weight.PrintToConsole();
	HiddenNode3.weight.PrintToConsole();
	HiddenNode4.weight.PrintToConsole();
	HiddenNode5.weight.PrintToConsole();

	cout << "Result : " << ans << endl;
	cout << "Node Uint Test Result : OK" << endl;
	system("pause");
	return 0;
}
#endif // NodeDebug

#ifdef LayerDebug
int main()
{
	cout << "Layer Uint Test" << endl;
	InputLayer<2, 2> inputLayer;
	HiddenLayer<2, 5> hiddenLayer;
	OutputLayer<5, 1> outputLayer;

	double data[] = { 0.3, 0.7 };
	Vector<double, 2> input(data);

	inputLayer.SetInput(input);
	inputLayer.Forward();

	hiddenLayer.SetInput(inputLayer.Output());
	hiddenLayer.Forward();

	outputLayer.SetInput(hiddenLayer.Output());
	outputLayer.Forward();

	inputLayer.Output().PrintToConsole();
	hiddenLayer.Output().PrintToConsole();
	outputLayer.Output().PrintToConsole();

	system("pause");
	return 0;
}
#endif // LayerDebug


