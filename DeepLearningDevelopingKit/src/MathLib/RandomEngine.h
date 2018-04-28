/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Random   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include <iostream>
#include <random>
#include <chrono>
#include "..\Nerual\Node.h"

template<class T>
class RandomEngine
{
public:

	RandomEngine()
	{
		this->_engine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	}

public:

private:

	std::default_random_engine _engine;
};

/************************************************************************************************************/
/* Tool functions */
// Generate a absolute random value within given limit
/// Defalut value : (-1,1)
inline double Random(double _lowerLimit = -1, double _upperLimit = 1) {
	if (double width = (_upperLimit - _lowerLimit) > 0)
		return width * ((double)rand() / RAND_MAX + (_upperLimit + _lowerLimit) / 2 - 0.5);
}

// Generate a random value within (-1/sqrt(m),1/sqrt(m))
/// Using for advanced weight generartor
inline double RandomSqrt(unsigned int _num) {
	return 1 / sqrt(_num) * (2 * (double)rand() / RAND_MAX - 1);
}
