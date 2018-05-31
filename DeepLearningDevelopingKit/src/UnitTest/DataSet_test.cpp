/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         Data Set Test   	                                                           */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define DataSetDebug

#ifdef DataSetDebug
#include <iostream>
#include <string>
#include "..\DataManager\Dataset\DataSet.h"

using namespace Data;

int main()
{
	ImageSet XOImageSet;
	XOImageSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\Data");
	XOImageSet.PrintToConsole();

	system("pause");
	return 0;
}
#endif // DataSetDebug
