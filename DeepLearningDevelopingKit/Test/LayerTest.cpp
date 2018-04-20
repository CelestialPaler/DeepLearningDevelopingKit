/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Layer Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define LayerDebug

#ifdef LayerDebug

// Header files
#include <iostream>
#include "..\MathLib\MathLib.h"
#include "..\Nerual\NerualLib.h"
#include "..\Util\Log.h"

// Namespaces
using namespace std;
using namespace MathLib;

int main()
{
	PrintLocalTime();
	PrintTitle();
	Vector<double> input(2, VectorType::Random);

	InputLayer in1(2);
	HiddenLayer hidden1(10, 2);

	in1.SetInput(input);
	in1.ForwardPropagation();

	hidden1.SetInput(in1.GetOutput());
	hidden1.ForwardPropagation();

	Vector<double> output(10);
	output = hidden1.GetOutput();

	cout << output;



	system("pause");
	return 0;
}
#endif // LayerDebug


