/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 		           Padding     	                                                           */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include "..\..\..\MathLib\MathLib.h"

extern enum class PoolingMethod;
extern enum class PaddingNum;

/***************************************************************************************************/
// Namespace : Neural
/// Provide Neural Network algorithm library.
namespace Neural
{
	class Pad
	{
		// Define the Element datatype.
		/// Mainly using float and double.
		typedef double ElemType;


	public:
		
		static MathLib::Matrix<ElemType> Padding(const PoolingMethod _method, PaddingNum _num)
		{
		
		}

	private:

	};
}