/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			 Pooling Layer     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "..\..\..\MathLib\MathLib.h"
#include "..\ActivationFunction.h"
#include "..\LossFunction.h"

/***************************************************************************************************/
// Namespace : Neural
/// Provide Neural Network algorithm library.
namespace Neural
{
	// Define the Element datatype.
	/// Mainly using float and double.
	typedef double ElemType;

	// Define Kernal and Feature.
	typedef MathLib::Matrix<ElemType> PoolKernal;

	// Method of appending paddings to original data
	/// For most situation, Right Down is the most common practice.
	enum class PaddingMethod {
		LeftUp,
		LeftDown,
		RightUp,
		RightDown,
		Surround
	};

	// What data is going to be appended original data as a padding.
	enum class PaddingNum {
		ZeroPadding,
		OnePadding,
		RandomPadding
	};

	// Method of pooling
	/// For most situation, Max Pooling is the most common practice.
	enum class PoolingMethod {
		MaxPooling,
		MinPooling,
		MeanPooling,
		RandomPooling
	};

	// Pooling Layer Initor
	/// Used for initialization of a PoolLayerInitor.
	struct PoolLayerInitor
	{
		// Stride
		size_t Stride;
		// The numner of kernals.
		size_t KernalNum;
		// Size of input matrix. 
		MathLib::Size InputSize;
		PaddingNum PaddingNum;
		PaddingMethod PaddingMethod;
	};

	class PoolingLayer
	{
	public:

		PoolingLayer(const PoolLayerInitor _initor);

	private:

		PoolKernal _poolKernal;

		MathLib::Matrix<ElemType> _input;
		MathLib::Matrix<ElemType> _output;

		PoolingMethod _poolingMethod;
	};
}