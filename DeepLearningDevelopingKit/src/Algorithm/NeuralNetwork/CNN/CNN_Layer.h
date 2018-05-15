/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	    Convolutional Kernal     	                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "..\..\..\MathLib\MathLib.h"
#include "CNN_Kernal.hpp"
#include "CNN_Feature.h"

/***************************************************************************************************/
// Namespace : Neural
namespace Neural
{
	enum class SamplingMethod {
		ZeroPadding,
		OnePadding,
		NoPadding
	};

	// CNN Initor
	/// Used for initialization of a BPNet.
	struct ConvLayerInitor
	{
		MathLib::Size InputSize;
		size_t KernalNum;
		MathLib::Size KernalSize;
		size_t Stride;
		SamplingMethod SamplingMethod;
	};

	class ConvolutionalLayer
	{
	public:

		ConvolutionalLayer(const ConvLayerInitor & _initor);

	public:

		inline const ConvFeature GetFeature(const size_t _index) const { return _features.at(_index); }
		inline const std::vector<ConvFeature> GetFeatureAll(const size_t _index) const { return _features; }
		inline const ConvKernal GetKernal(const size_t _index) const { return _kernals.at(_index); }
		inline const std::vector<ConvKernal> GetKernalAll(const size_t _index) const { return _kernals; }

	public:

		void ForwardPropagation(void);
		void BackwardPropagation(void);

	private:

		MathLib::Matrix<ElemType> _input;

		std::vector<ConvKernal> _kernals;
		std::vector<ConvFeature> _features;

		size_t _kernalNum;
		MathLib::Size _kernalSize;
		size_t _stride;
		SamplingMethod _samplingMethod;
	};

	enum class PoolingMethod {
		MaxPooling,
		MinPooling,
		MeanPooling,
		RandomPooling
	};

	class PoolingLayer
	{
	public:

		PoolingLayer(void);

	private:
	};
}