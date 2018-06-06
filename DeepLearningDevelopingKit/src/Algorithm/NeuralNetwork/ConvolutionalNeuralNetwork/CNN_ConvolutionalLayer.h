/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 Convolutional Neural Network     	                                          */
/*								        		 	    Convolutional Layer     	                                                   */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "..\..\..\MathLib\MathLib.h"
#include "..\ActivationFunction.h"
#include "..\LossFunction.h"
#include "CNN_PaddingLayer.h"

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

		ConvNode(const size_t _kernelM, const size_t _kernelN, const size_t _featureM, const size_t _featureN) {
			kernel.Init(_kernelM, _kernelN, MathLib::MatrixType::Random);
			kernelDelta.Init(_kernelM, _kernelN, MathLib::MatrixType::Zero);
			kernelDeltaSum.Init(_kernelM, _kernelN, MathLib::MatrixType::Zero);
			feature.Init(_featureM, _featureN, MathLib::MatrixType::Zero);
			bias = MathLib::Random();
			biasDelta = 0;
			biasDeltaSum = 0;
		}

		ConvNode(const MathLib::Size _kernelSize, const MathLib::Size _featureSize) {
			kernel.Init(_kernelSize.m, _kernelSize.n, MathLib::MatrixType::Random);
			kernelDelta.Init(_kernelSize.m, _kernelSize.n, MathLib::MatrixType::Zero);
			kernelDeltaSum.Init(_kernelSize.m, _kernelSize.n, MathLib::MatrixType::Zero);
			feature.Init(_featureSize.m, _featureSize.n, MathLib::MatrixType::Zero);
			bias = MathLib::Random();
			biasDelta = 0;
			biasDeltaSum = 0;
		}

		ConvKernel kernel;
		ElemType bias;
		ConvFeature feature;

		ConvKernel kernelDelta;
		ElemType biasDelta;

		ConvKernel kernelDeltaSum;
		ElemType biasDeltaSum;
	};

	/***************************************************************************************************/
	// Class : Convolutional Layer
	/// Used for extracting features out of input.
	class ConvolutionalLayer
	{
	public: // Constructors

		// Invoke constructor
		ConvolutionalLayer(const ConvLayerInitor & _initor);

	public: // Getter

		inline const ConvFeature GetFeature(const size_t _index) const { return _convNodes.at(_index).kernel; }
		inline const std::vector<ConvFeature> GetFeatureAll(void) const {
			std::vector<ConvFeature> features;
			for (const ConvNode & node : _convNodes)
				features.push_back(node.feature);
			return features;
		}

		inline const ConvKernel GetKernel(const size_t _index) const { return _convNodes.at(_index).kernel; }
		inline const std::vector<ConvKernel> GetKernelAll(void) const {
			std::vector<ConvKernel> kernels;
			for (const ConvNode & node : _convNodes)
				kernels.push_back(node.kernel);
			return kernels;
		}

		inline const std::vector<MathLib::Matrix<ElemType>> GetDelta(void) const { return _derivative; }


	public: // Setter

		// Set the input of the ConvLayer.
		void SetInput(const std::vector<MathLib::Matrix<ElemType>> &  _input);
		// Set the delta propagate back from next layer.
		void SetDelta(const std::vector<MathLib::Matrix<ElemType>> & _delta);
		// Set the learn rate of the ConvLayer.
		void SetLearnRate(const double _learnRate);

	public: // BackPropagation Algorithm

		// ForwardPropagation function
		void ForwardPropagation(void);
		// BackwardPropagation function
		void BackwardPropagation(void);
		// Update function
		void Update(void);
		// Sum up the delta of a batch.
		void BatchDeltaSumUpdate(const size_t _batchSize);
		// Clear the deltaSum of a batch.
		void BatchDeltaSumClear(void);

	private: //  Inner working function

		// Set the activation function of the layer.
		void SetActivationFunction(const ActivationFunction _function);
		// ConvolutionCal
		MathLib::Matrix<ElemType> ConvolutionCal(const MathLib::Matrix<ElemType> & _mat1, const MathLib::Matrix<ElemType> &  _mat2);

	private: //  Math stuff you know

		// Convolution of two matrix.
		MathLib::Matrix<ElemType> Convolution(const MathLib::Matrix<ElemType> &  _mat1, const MathLib::Matrix<ElemType> &  _mat2);
		ElemType ConvolutionSum(const MathLib::Matrix<ElemType> &  _mat1, const MathLib::Matrix<ElemType> &  _mat2, const size_t _m, const size_t _n);
		// Cross-correlation of two matrix.
		MathLib::Matrix<ElemType> Correlation(const MathLib::Matrix<ElemType> &  _mat1, const MathLib::Matrix<ElemType> &  _mat2);
		// Sum of all elements of the Cross-correlation of two matrix.
		ElemType CorrelationSum(const MathLib::Matrix<ElemType> &  _mat1, const MathLib::Matrix<ElemType> &  _mat2, const size_t _m, const size_t _n);

		// Rotate a Matrix with 180° 
		/// Cross-correlation(A, B) = rot180°(A * rot180°(B))
		MathLib::Matrix<ElemType> Rot180(const MathLib::Matrix<ElemType> & _mat);

		// Hadamard Product of two matrix.
		MathLib::Matrix<Neural::ElemType> Hadamard(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2);

		public:

		// Input of convolutional layer.
		std::vector<MathLib::Matrix<ElemType>> _input;
		std::vector<MathLib::Matrix<ElemType>> _paddedInput;

		// Input size.
		MathLib::Size _inputSize;
		// Output size.
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

		// Padding method
		PaddingMethod _paddingMethod;
		PaddingNum _paddingNum;
		// Padding size
		size_t _paddingM;
		size_t _paddingN;

		std::vector<MathLib::Matrix<ElemType>> _derivative;
		std::vector<MathLib::Matrix<ElemType>> _derivativeLastLayer;

		// Learning rate
		/// Default value is 1
		double learnRate = 1;

		// Activation Function
		ElemType(*activationFunction)(ElemType x);
		ElemType(*activationFunctionDerivative)(ElemType x);
	};
}