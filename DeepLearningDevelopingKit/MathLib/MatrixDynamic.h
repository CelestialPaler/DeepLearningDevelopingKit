/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	         Matrix Dynamic   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "MathDef.h"
#include <iostream>
#include <vector>

using namespace std;

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
/// Specialized for deep learning purpose. Emm might be true ... or not ... XD whatever!
namespace MathLibDynamic
{
	/***************************************************************************************************/
	// Class : Matrix
	template<class T>
	class Matrix
	{
	public:
		Matrix();
	private:
		vector<vector<T>> _data;
	};

	template<class T>
	inline Matrix<T>::Matrix(void)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				this->_data[i][j] = 0;
	}
}

