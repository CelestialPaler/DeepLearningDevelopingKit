/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Module Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define ModuleDebug
#include <ctime>

#ifdef ModuleDebug
#include "..\Nerual\NerualLib.h"

using namespace Nerual;


int main()
{
	srand((unsigned)time(NULL));

	BPNetInitor classicBPN;
	classicBPN.InputNodeNum = 2;
	classicBPN.HiddenLayerNum = 1;
	classicBPN.HiddenNodeNum = 10;
	classicBPN.OutputNodeNum = 1;
	classicBPN.InputLayerActivationFunction = ActivationFunction::Sigmoid;
	classicBPN.HiddenLayerActivationFunction = ActivationFunction::ReLU;
	classicBPN.LossFunction = LossFunction::MES;

	BPNet TestBP1(classicBPN);

	NumaricSet TrainSet;
	TrainSet.InitWithXOR();

	NumaricSet TestSet;
	TestSet.InitWithXORTest();

	TestBP1.SetTrainSet(&TrainSet);
	TestBP1.SetTestSet(&TestSet);

	TestBP1.Train();
	TestBP1.Test();

	system("pause");
	return 0;
}

#endif // ModuleDebug
