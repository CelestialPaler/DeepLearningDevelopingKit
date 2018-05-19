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
		size_t Stride;
		// The numner of kernels.
		size_t KernelNum;
		// Size of input matrix. 
		MathLib::Size InputSize;
		// Size of convolutional kernel.
		MathLib::Size KernelSize;
		// Method of padding.
		PaddingMethod PaddingMethod;
		// Value uesd in Padding
		PaddingNum PaddingNum;
		// Activation Function
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

		ConvNode(const size_t _kernelM, const size_t _kernelN, const size_t _featureM, const size_t _featureN){
			kernel.Init(_kernelM, _kernelN,MathLib::MatrixType::Random);
			feature.Init(_featureM, _featureN, MathLib::MatrixType::Zero);
			bias = MathLib::Random();
		}

		ConvNode(const MathLib::Size _kernelSize, const MathLib::Size _featureSize) {
			kernel.Init(_kernelSize.m, _kernelSize.n, MathLib::MatrixType::Random);
			feature.Init(_featureSize.m, _featureSize.n, MathLib::MatrixType::Zero);
			bias = MathLib::Random();
		}

		ConvKernel kernel;
		ElemType bias;
		ConvFeature feature;
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

		inline const ConvFeature GetFeature(const size_t _index) const { return _convNodes.at(_index).kernel; }
		inline const std::vector<ConvFeature> GetFeatureAll(void) const
		{
			std::vector<ConvFeature> features;
			for (const ConvNode & node : _convNodes)
				features.push_back(node.feature);
			return features;
		}

		inline const ConvKernel GetKernel(const size_t _index) const { return _convNodes.at(_index).kernel; }
		inline const std::vector<ConvKernel> GetKernelAll(void) const 
		{ 
			std::vector<ConvKernel> kernels;
			for (const ConvNode & node : _convNodes)
				kernels.push_back(node.kernel);
			return kernels;
		}

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
		// Padding function
		void Padding(void);

	private:

		ElemType MatrixConv(const MathLib::Matrix<ElemType> & _mat1, const MathLib::Matrix<ElemType> & _mat2, const size_t _m, const size_t _n);
		MathLib::Matrix<ElemType> Convolution(const MathLib::Matrix<ElemType> & _input, const MathLib::Matrix<ElemType> & _kernel);

	public:

		// Input of convolutional layer.
		std::vector<MathLib::Matrix<ElemType>> _input;
		std::vector<MathLib::Matrix<ElemType>> _paddedInput;
		// Input size.
		MathLib::Size _inputSize;
		MathLib::Size _outputSize;

		// Convolutional Node in the Layer.
		/// Contains a kernal, a bias and features extracted by the node.
		std::vector<ConvNode> _convNodes;

		// The num of ConvNodes in the layer.
		size_t _convNodeNum;
		// The size of kernal.
		MathLib::Size _kernelSize;
		// The size of stride.
		size_t _stride;

		// Padding size
		size_t PaddingM;
		size_t PaddingN;

		// Padding Method
		PaddingMethod _paddingMethod;
		PaddingNum _paddingNum;

		ElemType(*activationFunction)(ElemType x);
		ElemType(*activationFunctionDerivative)(ElemType x);

	};
}
