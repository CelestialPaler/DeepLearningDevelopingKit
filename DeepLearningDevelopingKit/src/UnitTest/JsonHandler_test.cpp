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
	string openPath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\test.json";
	jsonHandle.OpenJson(openPath);
	vector<Vector<double>> tempReadVecs = jsonHandle.ParseAllVector();
	for (auto & vec : tempReadVecs)
		cout << vec << endl;

	Vector<double> vec1(5, MathLib::VectorType::Random);
	Vector<double> vec2(3, MathLib::VectorType::Random);
	Vector<double> vec3(10, MathLib::VectorType::Random);
	Vector<double> vec4(2, MathLib::VectorType::Random);
	Vector<double> vec5(7, MathLib::VectorType::Random);
	vector<Vector<double>> tempWriteVecs{ vec1, vec2, vec3, vec4, vec5 };
	jsonHandle.AppendVectorsToBuffer(tempWriteVecs);
	string savePath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\test2.json";
	jsonHandle.SaveJson(savePath);
	cout << myTimer.GetTime() << endl;
	system("pause");
	return 0;
}
#endif // JsonHandlerDebug


