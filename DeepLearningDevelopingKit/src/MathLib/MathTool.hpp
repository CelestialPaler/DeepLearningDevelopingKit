/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	                Matrix   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

/***************************************************************************************************/
// Namespace : MathLib
/// Provide basic mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	/************************************************************************************************************/
	/* Tool functions */
	// Generate a absolute random value within given limit
	/// Defalut value : (-1,1)
	inline double Random(double _lowerLimit = -1, double _upperLimit = 1) {
		if (double width = (_upperLimit - _lowerLimit) > 0)
			return width * ((double)rand() / RAND_MAX + (_upperLimit + _lowerLimit) / 2 - 0.5);
		else
			return 0.f;
	}

	// Generate a random value within (-1/sqrt(m),1/sqrt(m))
	/// Using for advanced weight generartor
	inline double RandomSqrt(unsigned int _num) {
		return 1 / sqrt(_num) * (2 * (double)rand() / RAND_MAX - 1);
	}
}