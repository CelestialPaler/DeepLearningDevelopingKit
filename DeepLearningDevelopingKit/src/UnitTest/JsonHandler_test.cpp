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
#include "..\Util\Timer.h"

using namespace std;
using namespace MathLib;

int main()
{
	Util::Timer<chrono::seconds> myTimer;
	JsonHandler jsonHandle;

	Vector<double> vec(1000, MathLib::VectorType::Random);
	jsonHandle.AppendVectorToBuffer(vec);
	string savePath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\test2.json";
	jsonHandle.SaveJson(savePath);
	cout << myTimer.GetTime() << endl;
	system("pause");
	return 0;
}
#endif // JsonHandlerDebug


