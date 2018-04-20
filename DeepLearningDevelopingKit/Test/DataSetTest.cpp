/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         Data Set Test   	                                                           */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define DataSetDebug

#ifdef DataSetDebug
#include <iostream>
// #include "..\DataSet\DataSet.h"

using namespace Data;

int main()
{
	NumaricSet trainSet;
	NumaricSample sample1 = {
		Vector<double>(2, VectorType::Random), 
		Vector<double>(2, VectorType::Random) 
	};

	trainSet.AddToSet(sample1);

	system("pause");
	return 0;
}
#endif // DataSetDebug
