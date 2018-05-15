/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Module Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define ModuleDebug
#include <ctime>

#ifdef ModuleDebug
#include "..\Algorithm\NeuralNetwork\Module.h"

using namespace Neural;


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

	std::string openPath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\exmaple\\XOR.json";

	NumericSet trainSet;
	trainSet.LoadFromJson(openPath);

	TestBP1.SetTrainSet(&trainSet);
	TestBP1.SetTestSet(&trainSet);

	TestBP1.Train();
	TestBP1.Test();

	system("pause");
	return 0;
}

#endif // ModuleDebug
