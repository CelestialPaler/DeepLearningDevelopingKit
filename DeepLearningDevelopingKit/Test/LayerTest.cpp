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
#include <ctime>
#include "..\MathLib\ActivationFunction.h"

// Namespaces
using namespace std;
using namespace MathLib;
using namespace Nerual;

int main()
{
	srand((unsigned)time(NULL));
	PrintLocalTime();
	PrintTitle();

	InputLayer in(2, 2);
	HiddenLayer hidden(2, 10);
	OutputLayer out(10, 1);

	in.SetActivationFunction(ActivationFunction::Sigmoid);
	hidden.SetActivationFunction(ActivationFunction::ReLU);
	out.SetActivationFunction(ActivationFunction::Sigmoid);

	NumaricSet TrainSet;
	TrainSet.InitWithXOR();

	unsigned count = 0;
	do
	{
		NumaricSet::Sample sample = TrainSet.GetBatch();
		in.SetInput(sample.first);
		in.ForwardPropagation();
		//cout << in.GetOutput()(0) << "  " << in.GetOutput()(1) << " | ";

		hidden.SetInput(in.GetOutput());
		hidden.ForwardPropagation();

		//cout << hidden.GetOutput()(0) << "  " << hidden.GetOutput()(1) << " | ";

		out.SetInput(hidden.GetOutput());
		out.ForwardPropagation();

		//cout << out.GetOutput()(0) << " | ";

		out.SetExpectation(sample.second);
		Vector<double> tempDelta(10);
		//cout << out.GetDelta()(0) << endl;

		tempDelta = out.BackwardPropagation(out.GetDelta());
		hidden.BackwardPropagation(tempDelta);

		if (count == 15)
		{
			out.Update();
			hidden.Update();
			out.BatchDeltaSumClear();
			hidden.BatchDeltaSumClear();
			count = 0;
		}
		else
		{
			out.BatchDeltaSumUpdate(16);
			hidden.BatchDeltaSumUpdate(16);
			count++;
		}

		/*
		tempDelta = hidden3.BackwardPropagation(tempDelta);
		tempDelta = hidden2.BackwardPropagation(tempDelta);
		tempDelta = hidden1.BackwardPropagation(tempDelta);

		out.Update();
		hidden1.Update();
		hidden2.Update();
		hidden3.Update();
		*/

		cout << count << "  Loss :" << out.GetOutput()(0) << endl;
		// Sleep(100);
	} while (out.GetLoss() > 0.00001);
	system("pause");
	return 0;
}
#endif // LayerDebug


