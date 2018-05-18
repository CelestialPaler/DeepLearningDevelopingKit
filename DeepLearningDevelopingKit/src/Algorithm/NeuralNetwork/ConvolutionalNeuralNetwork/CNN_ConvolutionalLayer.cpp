/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	    Convolutional Layer     	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "CNN_ConvolutionalLayer.h"


Neural::ConvolutionalLayer::ConvolutionalLayer(const ConvLayerInitor & _initor)
{
	this->_convNodeNum = _initor.KernelNum;
	this->_kernelSize = _initor.KernelSize;
	this->_strideM = _initor.StrideM;
	this->_strideN = _initor.StrideN;
	this->_inputSize = _initor.InputSize;

	for (size_t i = 0; i < _convNodeNum; i++)
	{
		ConvNode newConvNode = *new ConvNode(_kernelSize);
		this->_convNodes.push_back(newConvNode);
	}

	SetActivationFunction(_initor.ActivationFunction);
	SetLossFunction(_initor.LossFunction);
}

void Neural::ConvolutionalLayer::SetInput(const std::vector<MathLib::Matrix<ElemType>>& _input)
{
	this->_input = _input;
}

void Neural::ConvolutionalLayer::SetActivationFunction(const ActivationFunction _function)
{
	switch (_function)
	{
	case ActivationFunction::Sigmoid:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	case ActivationFunction::ReLU:
		this->activationFunction = ReLU;
		this->activationFunctionDerivative = ReLUDerivative;
		break;
	default:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	}
}

void Neural::ConvolutionalLayer::SetLossFunction(const LossFunction _function)
{
	switch (_function)
	{
	case LossFunction::MES:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	default:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	}
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	// Travesing every input feature in the layer.
	for (size_t i = 0; i < _input.size(); i++)
	{
		size_t kernelOffsetM = 0;
		size_t kernelOffsetN = 0;
		// Travesing every kernel in the layer.
		for (size_t k = 0; k < _convNodeNum; k++)
		{
			for (size_t a = 0; a < _inputSize.m; a++)
			{
				for (size_t b = 0; b < _inputSize.n; b++)
					_features.at(i * _convNodeNum + k)(a, b) = activationFunction(Convolution(_input.at(i), _convNodes.at(k).kernal, kernelOffsetM, kernelOffsetN));
				kernelOffsetM += _strideM;
			}
			kernelOffsetN += _strideN;
			kernelOffsetM = 0;
		}
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{

}

Neural::ElemType Neural::ConvolutionalLayer::Convolution(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2)
{
	ElemType sum{ 0.f };
	MathLib::Size size = _mat1.GetSize();
	for (size_t i = 0; i < size.m; i++)
		for (size_t j = 0; j < size.n; j++)
			sum += _mat1(i, j)* _mat2(i, j);
	return sum;
}

Neural::ElemType Neural::ConvolutionalLayer::Convolution(const MathLib::Matrix<ElemType>& _input, const MathLib::Matrix<ElemType>& _kernel, const size_t _m, const size_t _n)
{
	ElemType sum{ 0.f };
	MathLib::Size size = _kernel.GetSize();
	for (size_t i = 0; i < size.m; i++)
		for (size_t j = 0; j < size.n; j++)
			sum += _input(_m + i, _n + j)* _kernel(i, j);
	return sum;
}
