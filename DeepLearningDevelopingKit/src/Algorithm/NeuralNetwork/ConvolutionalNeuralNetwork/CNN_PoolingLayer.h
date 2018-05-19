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
#include "CNN_Padding.h"

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
		// Method of padding.
		PaddingMethod PaddingMethod;
		// Value uesd in Padding
		PaddingNum PaddingNum;
		// Method of pooling.
		PoolingMethod PoolingMethod;
	};

	/***************************************************************************************************/
	// Class : Pooling Layer
	/// Used for scalling down the features.
	class PoolingLayer
	{
	public: // Constructors

		// Invoke constructor
		PoolingLayer(const PoolLayerInitor & _initor);

	public: // Getter and Setter

		void SetInput(const std::vector<Feature> & _input);

		inline const Feature GetFeature(const size_t _index) const { return _output.at(_index); }
		inline const std::vector<Feature> GetFeatureAll(void) const { return _output; }

	public:

		void DownSampling(void);
		void UpSampling(void);
		void Padding(void);

	private :

		Feature MaxPool(const Feature & _feature);
		ElemType MaxPoolPart(const Feature & _feature, const size_t m, const size_t n);

	public:

		std::vector<Feature> _input;
		std::vector<Feature> _paddedInput;
		std::vector<Feature> _output;

		size_t _stride;
		MathLib::Size _poolSize;
		// Input size.
		MathLib::Size _inputSize;
		MathLib::Size _outputSize;

		// Padding size
		size_t _paddingM;
		size_t _paddingN;
		
		// Delta
		std::vector<Feature> _delta;

		PoolingMethod _poolingMethod;
		PaddingNum _paddingNum;
		PaddingMethod _paddingMethod;
	};
}