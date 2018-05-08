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
#include "..\Util\Timer\Time.hpp"

int main()
{
	Util::Timer debugTimer;
	debugTimer.Start();
	std::cout << "/***********************************************************/" << std::endl;
	std::cout << "Linear Regression Test : \n" << std::endl;
	Data::NumericSet trainset1;
	trainset1.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\exmaple\\LR.json");
	trainset1.PrintToConsole();

	Regression::LinearRegression debugLR;
	debugLR.SetTrainSet(&trainset1);

	debugLR.Train();

	std::cout << "\nTime used:" << debugTimer.GetTime() << " ms" << std::endl;
	std::cout << "y = " << debugLR._weight <<" x + "<< debugLR._bias << std::endl;
	std::cout << "Predict value for 5.3698 is " << debugLR.Predict(5.3698) << "\n\n" << std::endl;

	std::cout << "/***********************************************************/" << std::endl;
	std::cout << "Multivariate Linear Regression Test : \n" << std::endl;
	Data::NumericSet trainset2;
	trainset2.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\exmaple\\MLR.json");
	trainset2.PrintToConsole();

	debugTimer.Reset();
	Regression::MultivariateLinearRegression debugMLR(2);
	debugMLR.SetTrainSet(&trainset2);
	debugMLR.Train();
	std::cout << "\nTime used:" << debugTimer.GetTime() << " ms" << std::endl;
	debugMLR.Test();
	system("pause");
	return 0;
}

#endif // !LinearRegressionDebug
