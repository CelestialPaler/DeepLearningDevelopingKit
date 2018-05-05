/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          MathLib Error 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "MathLibError.h"
#include <iostream>

void ExceptionHandle(const std::exception & _exp)
{
	std::cout << "Fatal Error Occured!" << std::endl;
	std::cout << _exp.what() << std::endl;
	system("pause");
	exit(0);
}

