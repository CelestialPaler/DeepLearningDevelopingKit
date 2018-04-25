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
	hidden.SetActivationFunction(ActivationFunction::ReLU);
	hidden.SetLossFunction(LossFunction::MES);
	out.SetActivationFunction(ActivationFunction::Sigmoid);
	out.SetLossFunction(LossFunction::MES);

	NumaricSet TrainSet;
	TrainSet.InitWithXOR();

	unsigned count = 1;
	unsigned iterCount = 0;
	unsigned batchsize = 4;
	do
	{
		NumaricSet::Sample sample = TrainSet.GetBatch();

		hidden.SetInput(sample.first);
		hidden.ForwardPropagation();

		out.SetInput(hidden.GetOutput());
		out.ForwardPropagation();


		hidden.BackwardPropagation(out.BackwardPropagation(sample.second));

		if (count == 3)
		{
			out.Update();
			hidden.Update();

			out.BatchDeltaSumClear();
			hidden.BatchDeltaSumClear();

			count = 0;
			iterCount++;
		}
		else
		{
			out.BatchDeltaSumUpdate(batchsize);
			hidden.BatchDeltaSumUpdate(batchsize);
			count++;
			cout << "Iter :" << iterCount << "  Loss :" << out.GetLoss() << endl;
		}

		Sleep(100);
	} while (out.GetLoss() > 0.00001);
	system("pause");
	return 0;
}
#endif // LayerDebug


