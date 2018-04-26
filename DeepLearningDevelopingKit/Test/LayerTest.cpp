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
	in.SetLossFunction(LossFunction::MES);
	hidden.SetActivationFunction(ActivationFunction::Sigmoid);
	hidden.SetLossFunction(LossFunction::MES);
	out.SetActivationFunction(ActivationFunction::Sigmoid);
	out.SetLossFunction(LossFunction::MES);

	NumaricSet TrainSet;
	TrainSet.InitWithXOR();

	unsigned count = 0;
	unsigned iterCount = 0;
	unsigned batchsize = 4;
	do
	{
		NumaricSet::Sample sample = TrainSet.GetBatch();

		cout << sample.first(0)<< sample.first(1)<< " | ";

		hidden.SetInput(sample.first);
		hidden.ForwardPropagation();

		for (size_t i = 0; i < 10; i++)
		{
			cout << hidden.GetOutput()(i) << endl;
		}

		out.SetInput(hidden.GetOutput());
		out.ForwardPropagation();
		
		cout << out.GetOutput()(0) << endl;

		hidden.BackwardPropagation(out.BackwardPropagation(sample.second));

		if (count == 3)
		{
			out.Update();
			hidden.Update();

			out.BatchDeltaSumClear();
			hidden.BatchDeltaSumClear();

			count = 0;
			iterCount++;
			cout << "Iter :" << iterCount << "  Loss :" << out.GetLoss() << endl;
		}
		else
		{
			out.BatchDeltaSumUpdate(batchsize);
			hidden.BatchDeltaSumUpdate(batchsize);
			count++;
		}

		Sleep(125);
	} while (out.GetLoss() > 0.00001);
	system("pause");
	return 0;
}
#endif // LayerDebug


