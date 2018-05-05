/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          MathLib Error 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include <exception>

struct unmatched_size : public std::exception
{
	const char * what() const throw ()
	{
		return "Size of Matrix and Vector Unmatched!";
	}
};

void ExceptionHandle(const std::exception & _exp);
