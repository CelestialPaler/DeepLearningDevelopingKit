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

	// Define Kernel and Feature.
	typedef MathLib::Matrix<ElemType> Feature;

	extern enum class PaddingMethod;
	extern enum class PaddingNum;

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
		// Size of input matrix. 
		MathLib::Size InputSize;
		// Size of pool
		MathLib::Size PoolSize;
		PaddingNum PaddingNum;
		PaddingMethod PaddingMethod;
		PoolingMethod  PoolingMethod;
	};

	class PoolingLayer
	{
	public:

		PoolingLayer(const PoolLayerInitor & _initor);

	public:

		void SetInput(const std::vector<Feature> & _input);

		inline const Feature GetFeature(const size_t _index) const { return _output.at(_index); }
		inline const std::vector<Feature> GetFeatureAll(void) const { return _output; }

	public:

		void DownSampling(void);

	private :

		ElemType MaxPool(const Feature & _feature, const size_t m, const size_t n);

	public:

		std::vector<Feature> _input;
		std::vector<Feature> _output;

		size_t _stride;
		MathLib::Size _poolSize;
		MathLib::Size _inputSize;
		PoolingMethod _poolingMethod;
	};
}