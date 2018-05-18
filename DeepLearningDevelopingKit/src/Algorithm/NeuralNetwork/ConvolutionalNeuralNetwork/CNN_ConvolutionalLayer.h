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

	// Convolutional Layer Initor
	/// Used for initialization of a ConvLayer.
	struct ConvLayerInitor
	{
		// Stride
		size_t StrideM;
		size_t StrideN;
		// The numner of kernels.
		size_t KernelNum;
		// Size of input matrix. 
		MathLib::Size InputSize;
		// Size of convolutional kernel.
		MathLib::Size KernelSize;
		LossFunction LossFunction;
		ActivationFunction ActivationFunction;
	};
	
	// Define Kernel and Feature.
	typedef MathLib::Matrix<ElemType> ConvKernel;
	typedef MathLib::Matrix<ElemType> ConvFeature;

	/***************************************************************************************************/
	// Struct : ConvNode
	/// Node in convolutional layer.
	struct ConvNode
	{
		ConvNode() = default;

		ConvNode(const size_t _m, const size_t _n){
			kernal.Init(_m,_n,MathLib::MatrixType::Random);
			bias = Random();
		}

		ConvNode(const MathLib::Size _size) {
			kernal.Init(_size.m, _size.n, MathLib::MatrixType::Random);
			bias = Random();
		}

		ConvKernel kernal;
		ElemType bias;
	};

	/***************************************************************************************************/
	// Class : Convolutional Layer
	/// Used for extracting features out of input.
	class ConvolutionalLayer
	{
	public: // Constructors

		// Invoke constructor
		ConvolutionalLayer(const ConvLayerInitor & _initor);
		// Copy constructor
		ConvolutionalLayer(ConvolutionalLayer & _convLayer);

	public: // Getter and Setter

		inline const ConvFeature GetFeature(const size_t _index) const { return _features.at(_index); }
		inline const std::vector<ConvFeature> GetFeatureAll(void) const { return _features; }
		inline const ConvNode GetKernel(const size_t _index) const { return _convNodes.at(_index); }
		inline const std::vector<ConvNode> GetKernelAll(void) const { return _convNodes; }

	public:

		// Set the input of the ConvLayer.
		void SetInput(const std::vector<MathLib::Matrix<ElemType>> &  _input);
		// Set the activation function of the layer.
		void SetActivationFunction(const ActivationFunction _function);
		// Set the loss function of the layer.
		void SetLossFunction(const LossFunction _function);

	public:

		// ForwardPropagation function
		void ForwardPropagation(void);
		// BackwardPropagation function
		void BackwardPropagation(void);

	private:

		ElemType Convolution(const MathLib::Matrix<ElemType> & _mat1, const MathLib::Matrix<ElemType> & _mat2);
		ElemType Convolution(const MathLib::Matrix<ElemType> & _input, const MathLib::Matrix<ElemType> & _kernel, const size_t _m, const size_t _n);

	public:

		// Input of convolutional layer.
		std::vector<MathLib::Matrix<ElemType>> _input;
		// Input size.
		MathLib::Size _inputSize;

		// Convolutional Node in the Layer.
		/// Contains a kernal and a bias.
		std::vector<ConvNode> _convNodes;
		// Features extracted by the node.
		std::vector<ConvFeature> _features;

		// The num of ConvNodes in the layer.
		size_t _convNodeNum;
		// The size of kernal.
		MathLib::Size _kernelSize;
		// The size of stride.
		size_t _strideM;
		size_t _strideN;

		ElemType(*activationFunction)(ElemType x);
		ElemType(*activationFunctionDerivative)(ElemType x);
		ElemType(*lossFunction)(ElemType x, ElemType y);
		ElemType(*lossFunctionDerivative)(ElemType x, ElemType y);
	};
}
