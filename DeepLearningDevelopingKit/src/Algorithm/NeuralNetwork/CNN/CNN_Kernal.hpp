/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	               Kernal     	                                                              */
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

	class ConvKernal
	{
	public:
		ConvKernal(const MathLib::Size _size);
		MathLib::Matrix<ElemType> weight;
		MathLib::Size size;
	};

	class PoolingKernal
	{
	public:
		PoolingKernal(const MathLib::Size _size, const PoolingMethod _method);
		MathLib::Matrix<ElemType> weight;
		MathLib::Size size;
	};
}

namespace Neural
{
	Neural::ConvKernal::ConvKernal(const MathLib::Size _size)
	{
		this->size = _size;
		weight.Init(size.m, size.n, MathLib::MatrixType::Random);
	}

	Neural::PoolingKernal::PoolingKernal(const MathLib::Size _size, const PoolingMethod _method)
	{
		switch (_method)
		{
		case Neural::PoolingMethod::MaxPooling:
			break;
		case Neural::PoolingMethod::MinPooling:
			break;
		case Neural::PoolingMethod::MeanPooling:
			break;
		case Neural::PoolingMethod::RandomPooling:
			break;
		default:
			break;
		}
	}

}