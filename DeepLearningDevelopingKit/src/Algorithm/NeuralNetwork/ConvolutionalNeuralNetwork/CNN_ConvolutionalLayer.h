/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	    Convolutional Layer     	                                                      */
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
	typedef MathLib::Matrix<ElemType> ConvKernel;
	typedef MathLib::Matrix<ElemType> ConvFeature;

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

	// Convolutional Layer Initor
	/// Used for initialization of a ConvLayer.
	struct ConvLayerInitor
	{
		// Stride
		size_t Stride;
		// The numner of kernels.
		size_t KernelNum;
		// Size of input matrix. 
		MathLib::Size InputSize;
		// Size of convolutional kernel.
		MathLib::Size KernelSize;
		PaddingNum PaddingNum;
		PaddingMethod PaddingMethod;
		LossFunction LossFunction;
		ActivationFunction ActivationFunction;
	};

	class ConvolutionalLayer
	{
	public:

		ConvolutionalLayer(const ConvLayerInitor & _initor);

	public:

		inline const ConvFeature GetFeature(const size_t _index) const { return _features.at(_index); }
		inline const std::vector<ConvFeature> GetFeatureAll(void) const { return _features; }
		inline const ConvKernel GetKernel(const size_t _index) const { return _kernels.at(_index); }
		inline const std::vector<ConvKernel> GetKernelAll(void) const { return _kernels; }

	public:

		void SetInput(const MathLib::Matrix<ElemType> & _input);
		// Set the activation function of the layer.
		void SetActivationFunction(const ActivationFunction _function);
		// Set the loss function of the layer.
		void SetLossFunction(const LossFunction _function);

	public:

		// ForwardPropagation function
		void ForwardPropagation(void);
		// BackwardPropagation function
		void BackwardPropagation(void);
		// Padding function
		void Padding(void);

	private:

		ElemType Convolution(const MathLib::Matrix<ElemType> & _mat1, const MathLib::Matrix<ElemType> & _mat2);
		ElemType Convolution(const MathLib::Matrix<ElemType> & _input, const MathLib::Matrix<ElemType> & _kernel, const size_t _m, const size_t _n);

	public:

		MathLib::Matrix<ElemType> _originalInput;
		MathLib::Matrix<ElemType> _paddedInput;

		std::vector<ConvKernel> _kernels;
		std::vector<ConvFeature> _features;

		size_t _kernelNum;
		MathLib::Size _kernelSize;
		size_t _stride;
		PaddingMethod _paddingMethod;
		PaddingNum _paddingNum;

		ElemType(*activationFunction)(ElemType x);
		ElemType(*activationFunctionDerivative)(ElemType x);
		ElemType(*lossFunction)(ElemType x, ElemType y);
		ElemType(*lossFunctionDerivative)(ElemType x, ElemType y);
	};
}
