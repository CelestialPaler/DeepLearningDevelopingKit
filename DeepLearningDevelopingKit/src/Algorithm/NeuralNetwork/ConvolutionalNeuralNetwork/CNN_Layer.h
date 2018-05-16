/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	    Convolutional Kernal     	                                                  */
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
	typedef double ElemType;

	enum class PaddingMethod {
		LeftUp,
		LeftDown,
		RightUp,
		RightDown,
		Surround
	};

	enum class PaddingNum {
		ZeroPadding,
		OnePadding,
		NoPadding
	};

	enum class PoolingMethod {
		MaxPooling,
		MinPooling,
		MeanPooling,
		RandomPooling
	};

	typedef MathLib::Matrix<ElemType> ConvKernal;
	typedef MathLib::Matrix<ElemType> ConvFeature;

	// ConvLayer Initor
	/// Used for initialization of a ConvLayer.
	struct ConvLayerInitor
	{
		MathLib::Size InputSize;
		size_t KernalNum;
		MathLib::Size KernalSize;
		size_t Stride;
		PaddingMethod PaddingMethod;
		PaddingNum PaddingNum;
		ActivationFunction ActivationFunction;
		LossFunction LossFunction;
	};

	class ConvolutionalLayer
	{
	public:

		ConvolutionalLayer(const ConvLayerInitor & _initor);

	public:

		inline const ConvFeature GetFeature(const size_t _index) const { return _features.at(_index); }
		inline const std::vector<ConvFeature> GetFeatureAll(void) const { return _features; }
		inline const ConvKernal GetKernal(const size_t _index) const { return _kernals.at(_index); }
		inline const std::vector<ConvKernal> GetKernalAll(void) const { return _kernals; }

	public:

		void SetInput(const MathLib::Matrix<ElemType> & _input);
		// Set the activation function of the layer.
		void SetActivationFunction(const ActivationFunction _function);
		// Set the loss function of the layer.
		void SetLossFunction(const LossFunction _function);

	public:

		void ForwardPropagation(void);
		void BackwardPropagation(void);
		void Padding(void);

	private:

		void ZeroPadding(const size_t _paddingSize);
		void OnePadding(const size_t _paddingSize);
		ElemType Convolution(const MathLib::Matrix<ElemType> & _mat1, const MathLib::Matrix<ElemType> & _mat2);
		ElemType Convolution(const MathLib::Matrix<ElemType> & _input, const MathLib::Matrix<ElemType> & _kernal, const size_t _m, const size_t _n);

	public:

		MathLib::Matrix<ElemType> _originalInput;
		MathLib::Matrix<ElemType> _paddedInput;

		std::vector<ConvKernal> _kernals;
		std::vector<ConvFeature> _features;

		size_t _kernalNum;
		MathLib::Size _kernalSize;
		size_t _stride;
		PaddingMethod _paddingMethod;
		PaddingNum _paddingNum;

		ElemType(*activationFunction)(ElemType x);
		ElemType(*activationFunctionDerivative)(ElemType x);
		ElemType(*lossFunction)(ElemType x, ElemType y);
		ElemType(*lossFunctionDerivative)(ElemType x, ElemType y);
	};

	class PoolingLayer
	{
	public:

		PoolingLayer(void);

	private:
	};
}