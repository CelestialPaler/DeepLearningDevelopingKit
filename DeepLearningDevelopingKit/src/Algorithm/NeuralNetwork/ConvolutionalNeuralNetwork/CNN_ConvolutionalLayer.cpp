﻿/***************************************************************************************************/
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
	this->_stride = _initor.Stride;
	this->_inputSize = _initor.InputSize;
	this->_paddingMethod = _initor.PaddingMethod;
	this->_paddingNum = _initor.PaddingNum;

	for (size_t i = 0; i < _convNodeNum; i++)
	{
		ConvNode newConvNode = *new ConvNode(_kernelSize, _inputSize);
		this->_convNodes.push_back(newConvNode);
	}

	SetActivationFunction(_initor.ActivationFunction);

	this->_outputSize.m = _inputSize.m;
	this->_outputSize.n = _inputSize.n;
	this->_paddingM = _inputSize.m + _kernelSize.m - 1 - _stride * _outputSize.m;
	this->_paddingN = _inputSize.n + _kernelSize.n - 1 - _stride * _outputSize.n;
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
	case ActivationFunction::Linear:
		this->activationFunction = Linear;
		this->activationFunctionDerivative = LinearDerivative;
		break;
	default:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	}
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	// Travesing every kernel in the layer.
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		for (size_t i = 0; i < _input.size(); i++)
		{
			_convNodes.at(k).feature += Convolution(_paddedInput.at(i), _convNodes.at(k).kernel);
		}
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{

}

void Neural::ConvolutionalLayer::Padding(void)
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		MathLib::Matrix<ElemType> newMatrix = *new MathLib::Matrix<ElemType>;
		_paddedInput.push_back(newMatrix);
	}
	for (size_t i = 0; i < _input.size(); i++)
	{
		_paddedInput.at(i) = Pad::Padding(_input.at(i), _paddingMethod, _paddingNum, _paddingM, _paddingN);
	}
}

Neural::ElemType Neural::ConvolutionalLayer::MatrixConv(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2, const size_t _m, const size_t _n)
{
	ElemType sum{ 0.f };
	MathLib::Size size = _mat2.GetSize();
	for (size_t i = 0; i < size.m; i++)
		for (size_t j = 0; j < size.n; j++)
			sum += _mat1(_m + i, _n + j)* _mat2(i, j);
	return sum;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Convolution(const MathLib::Matrix<ElemType>& _input, const MathLib::Matrix<ElemType>& _kernel)
{
	MathLib::Matrix<Neural::ElemType> temp(_inputSize.m, _inputSize.n);
	size_t kernalOffsetM = 0;
	size_t kernalOffsetN = 0;
	for (size_t i = 0; i < _inputSize.m; i++)
	{
		for (size_t j = 0; j < _inputSize.n; j++)
		{
			temp(i, j) = activationFunction(MatrixConv(_input, _kernel, kernalOffsetM, kernalOffsetN));
			kernalOffsetN += _stride;
		}
		kernalOffsetM += _stride;
		kernalOffsetN = 0;
	}
	return temp;
}