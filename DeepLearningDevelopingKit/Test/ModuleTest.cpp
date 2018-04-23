/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Module Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define ModuleDebug
#include <ctime>

#ifdef ModuleDebug
#include "..\Nerual\NerualLib.h"

using namespace Nerual;

int main()
{
	srand((unsigned)time(NULL));

	NumaricSet TrainSet;
	TrainSet.InitWithXOR();

	BPNetInitor classicBPN;
	classicBPN.InputNodeNum = 2;
	classicBPN.HiddenLayerNum = 2;
	classicBPN.HiddenNodeNum = 10;
	classicBPN.OutputNodeNum = 1;

	BPNet TestBP1(classicBPN);

	TestBP1.SetTrainSet(&TrainSet);
	TestBP1.Train();

	system("pause");
	return 0;
}

#endif // ModuleDebug
