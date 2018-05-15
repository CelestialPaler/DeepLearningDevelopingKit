/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Feature Map     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "..\..\..\MathLib\MathLib.h"

/***************************************************************************************************/
// Namespace : Neural
/// Provide Node for nerual network algorithms.
namespace Neural
{
	// Define the Element datatype.
	/// Mainly using float and double.
	typedef double ElemType;

	struct ConvFeature
	{
		MathLib::Matrix<ElemType> _data;
	};
}