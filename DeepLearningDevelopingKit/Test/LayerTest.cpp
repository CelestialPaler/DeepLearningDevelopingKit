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
#include <ctime>

// Namespaces
using namespace std;
using namespace MathLib;
using namespace Nerual;

int main()
{
	srand((unsigned)time(NULL));
	PrintLocalTime();
	PrintTitle();

	Vector<double> target(2, VectorType::Random);
	target(0) = 0;
	target(1) = 0;
	Vector<double> output(1);

	InputLayer in(2, 2);
	HiddenLayer hidden(2, 10);
	OutputLayer out(10, 1);

	unsigned count = 0;
	do
	{
		Vector<double> input(2, VectorType::Random);
		in.SetInput(input);
		in.ForwardPropagation();

		// cout << in.GetOutput()(0) << "  " << in.GetOutput()(1) << endl;
		 
		hidden.SetInput(in.GetOutput());
		hidden.ForwardPropagation();
		cout << hidden.GetOutput()(0) << "  " << hidden.GetOutput()(1) << endl;
		out.SetInput(hidden.GetOutput());
		out.ForwardPropagation();

		out.SetExpectation(target);
		/*
		Vector<double> tempDelta(10);
		tempDelta = out.BackwardPropagation(out.GetDelta());
		tempDelta = hidden3.BackwardPropagation(tempDelta);
		tempDelta = hidden2.BackwardPropagation(tempDelta);
		tempDelta = hidden1.BackwardPropagation(tempDelta);

		out.Update();
		hidden1.Update();
		hidden2.Update();
		hidden3.Update();
		*/
		cout << count << "  Loss :" << out.GetOutput()(0) << endl;
		count++;
	} while (out.GetLoss() > 0.00001);

	system("pause");
	return 0;
}
#endif // LayerDebug


