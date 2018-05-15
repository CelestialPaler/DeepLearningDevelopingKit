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

	class ConvFeature
	{
	public:
		ConvFeature(const MathLib::Size _size);
		MathLib::Matrix<ElemType> data;
		MathLib::Size size;
	};

	Neural::ConvFeature::ConvFeature(const MathLib::Size _size)
	{
		this->size = _size;
		weight.Init(size.m, size.n, MathLib::MatrixType::Zero);
	}
}