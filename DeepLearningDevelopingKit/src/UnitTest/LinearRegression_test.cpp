/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	   Linear Regression Test   	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define LinearRegressionDebug

#ifdef LinearRegressionDebug
#include <iostream>
#include "..\Algorithm\RegressionAnalysis\RegressionAnalysis.h"

int main()
{
	Data::NumericSet trainset;
	trainset.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\exmaple\\LR.json");
	trainset.PrintToConsole();

	Regression::LinearRegression debugLR;
	debugLR.SetMethod(Regression::LinearRegressionMethod::OrdinaryLeastSquares);
	debugLR.SetTrainSet(&trainset);

	debugLR.Train();

	std::cout << "\ny = " << debugLR._weight <<"x + "<< debugLR._bias << std::endl;

	system("pause");
	return 0;
}

#endif // !LinearRegressionDebug
