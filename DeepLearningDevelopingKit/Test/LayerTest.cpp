/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Layer Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define LayerDebug

#ifdef LayerDebug

// Header files
#include <iostream>
#include "..\MathLib\MathLib.h"
#include "..\Nerual\NerualLib.h"
#include "..\Util\Log.h"

// Namespaces
using namespace std;
using namespace MathLib;
using namespace Nerual;

int main()
{
	PrintLocalTime();
	PrintTitle();

	Vector<double> input(2);
	input(0) = 0;
	input(1) = 0;
	Vector<double> target(2, VectorType::Random);
	target(0) = 0;
	target(1) = 0;
	Vector<double> output(1);

	InputLayer in(2, 2);
	HiddenLayer hidden1(2, 10);
	HiddenLayer hidden2(10, 15);
	HiddenLayer hidden3(15, 10);
	OutputLayer out(10, 1);

	unsigned count = 0;
	do
	{
		in.SetInput(input);
		in.ForwardPropagation();

		hidden1.SetInput(in.GetOutput());
		hidden1.ForwardPropagation();
		hidden2.SetInput(hidden1.GetOutput());
		hidden2.ForwardPropagation();
		hidden3.SetInput(hidden2.GetOutput());
		hidden3.ForwardPropagation();

		out.SetInput(hidden3.GetOutput());
		out.ForwardPropagation();

		out.SetExpectation(target);

		cout << count << "  Loss :" << out.GetLoss() << endl;

		Vector<double> tempDelta(10);
		tempDelta = out.BackwardPropagation(out.GetDelta());
		tempDelta = hidden3.BackwardPropagation(tempDelta);
		tempDelta = hidden2.BackwardPropagation(tempDelta);
		tempDelta = hidden1.BackwardPropagation(tempDelta);

		out.Update();
		hidden1.Update();
		hidden2.Update();
		hidden3.Update();

		count++;
	} while (out.GetLoss() > 0.00001);

	system("pause");
	return 0;
}
#endif // LayerDebug


