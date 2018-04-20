/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Module Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define ModuleDebug

#ifdef ModuleDebug
#include "..\Nerual\NerualLib.h"

using namespace Nerual;

int main()
{
	NumaricSet TrainSet;

	Vector<double> input1(2, VectorType::Zero);
	input1(0) = 0;
	input1(1) = 0;
	Vector<double> target1(1, VectorType::Zero);
	target1(0) = 0;
	NumaricSet::Sample tempSample1;
	tempSample1.first = input1;
	tempSample1.second = target1;
	TrainSet.AddToSet(tempSample1);

	BPNetInitor classicBPN;
	classicBPN.InputNodeNum = 2;
	classicBPN.HiddenLayerNum = 3;
	classicBPN.HiddenNodeNum = 10;
	classicBPN.OutputNodeNum = 1;

	BPNet TestBP1(classicBPN);

	TestBP1.SetTrainSet(&TrainSet);
	TestBP1.Train();

	system("pause");
	return 0;
}

#endif // ModuleDebug
