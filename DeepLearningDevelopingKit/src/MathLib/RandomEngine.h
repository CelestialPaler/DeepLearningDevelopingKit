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


