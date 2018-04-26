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
	HiddenLayer hidden1(2, 5);
	HiddenLayer hidden2(5, 5);
	HiddenLayer hidden3(5, 5);
	OutputLayer out(5, 1);

	in.SetActivationFunction(ActivationFunction::Sigmoid);
	in.SetLossFunction(LossFunction::MES);
	hidden1.SetActivationFunction(ActivationFunction::Sigmoid);
	hidden1.SetLossFunction(LossFunction::MES);
	hidden2.SetActivationFunction(ActivationFunction::Sigmoid);
	hidden2.SetLossFunction(LossFunction::MES);
	hidden3.SetActivationFunction(ActivationFunction::Sigmoid);
	hidden3.SetLossFunction(LossFunction::MES);
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

		// cout << sample.first(0) << sample.first(1) << " | " << sample.second(0) << " | ";

		hidden1.SetInput(sample.first);
		hidden1.ForwardPropagation();
		hidden2.SetInput(hidden1.GetOutput());
		hidden2.ForwardPropagation();
		hidden3.SetInput(hidden2.GetOutput());
		hidden3.ForwardPropagation();


		out.SetInput(hidden3.GetOutput());
		out.ForwardPropagation();

		// cout << "  Output : " << out.GetOutput()(0) << endl;

		if (count == 3)
		{
			if (true)
			{
				hidden1.BackwardPropagation(out.BackwardPropagation(sample.second));
				out.Update();
				hidden3.Update();
				hidden2.Update();
				hidden1.Update();

				out.BatchDeltaSumClear();
				hidden3.BatchDeltaSumClear();
				hidden2.BatchDeltaSumClear();
				hidden1.BatchDeltaSumClear();
			}
			count = 0;
			iterCount++;
			cout << "Iter :" << iterCount << "  Loss :" << out.GetLoss() << endl;
		}
		else
		{
			out.BatchDeltaSumUpdate(batchsize);
			hidden3.BatchDeltaSumUpdate(batchsize);
			hidden2.BatchDeltaSumUpdate(batchsize);
			hidden1.BatchDeltaSumUpdate(batchsize);
			count++;
		}

		Sleep(0 / batchsize);
	} while (out.GetLoss() > 0.001);




	system("pause");
	return 0;
}
#endif // LayerDebug


