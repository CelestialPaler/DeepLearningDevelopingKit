/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 		 Json Handler Test	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define JsonHandlerDebug

#ifdef JsonHandlerDebug
#include <iostream>
#include <string>
#include "..\MathLib\MathLib.h"
#include "..\Json\JsonHandler.h"

using namespace std;
using namespace MathLib;

int main()
{
	string filePath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\vector.json";
	JsonHandler jsonHandle;
	jsonHandle.OpenJson(filePath);

	Vector<double> data = jsonHandle.ParseVector(0);

	string savePath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\test2.json";
	jsonHandle.SaveJson(savePath);

	system("pause");
	return 0;
}
#endif // JsonHandlerDebug


