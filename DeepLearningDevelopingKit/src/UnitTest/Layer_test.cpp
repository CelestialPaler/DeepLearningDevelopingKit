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

	unsigned iterCount = 0;
	unsigned batchsize = 4;
	double loss = 0;

	if (true)
	{
		do
		{
			for (size_t i = 0; i < 4; i++)
			{
				NumaricSet::Sample sample = TrainSet.GetBatch();

				hidden.SetInput(sample.first);
				hidden.ForwardPropagation();

				out.SetInput(hidden.GetOutput());
				out.ForwardPropagation();

				hidden.BackwardPropagation(out.BackwardPropagation(sample.second));

				cout << sample.first(0) << sample.first(1) << " | " << sample.second(0) << " | ";

				out.BatchDeltaSumUpdate(batchsize);
				hidden.BatchDeltaSumUpdate(batchsize);

				out.LossSumUpdate();
			}

			out.Update();
			hidden.Update();

			out.BatchDeltaSumClear();
			hidden.BatchDeltaSumClear();

			loss = out.GetLoss();
			out.LossSumClear();

			iterCount++;
			cout << "Iter :" << iterCount << "  Loss :" << loss << endl;
		} while (loss > 0.001);
	}

	NumaricSet TestSet;
	TestSet.InitWithXOR();

	if (true)
	{
		for (size_t i = 0; i < 4; i++)
		{
			NumaricSet::Sample sample = TestSet.GetBatch();

			hidden.SetInput(sample.first);
			hidden.ForwardPropagation();

			out.SetInput(hidden.GetOutput());
			out.ForwardPropagation();

			cout << "Input: " << sample.first(0) << sample.first(1) << "  Expectation: " << sample.second(0) << "  Output: " << out.GetOutput()(0) << endl;
		}
	}

	system("pause");
	return 0;
}
#endif // LayerDebug


