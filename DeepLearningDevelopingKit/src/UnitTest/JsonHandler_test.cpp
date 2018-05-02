/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 		 Json Handler Test	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define JsonHandlerDebug

#ifdef JsonHandlerDebug
#include <iostream>
#include <string>
#include "..\MathLib\MathLib.h"
#include "..\Util\Json\JsonHandler.h"
#include "..\Util\Json\JsonParser.h"
#include "..\Util\Timer\Timer.h"

using namespace std;
using namespace MathLib;

int main()
{
	Util::Timer<chrono::seconds> myTimer;
	VectorParser debugParser;
	string openPath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\test.json";
	vector<Vector<double>> tempReadVecs = debugParser.Deserialize(openPath);

	for (auto & vec : tempReadVecs)
		cout << vec << std::endl;

	Vector<double> vec1(5, MathLib::VectorType::Random);
	Vector<double> vec2(3, MathLib::VectorType::Random);
	Vector<double> vec3(10, MathLib::VectorType::Random);
	Vector<double> vec4(2, MathLib::VectorType::Random);
	Vector<double> vec5(7, MathLib::VectorType::Random);
	vector<Vector<double>> tempWriteVecs{ vec1, vec2, vec3, vec4, vec5 };

	string savePath = "F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\test\\test2.json";
	debugParser.Serialize(savePath, tempWriteVecs);
	cout << "Time consume : " << myTimer.GetTime() << " ms " << std::endl;
	system("pause");
	return 0;
}
#endif // JsonHandlerDebug


