/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 Convolutional Neural Network     	                                          */
/*								        		 	    Convolutional Layer     	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "ConvolutionalLayer.h"

Neural::ConvolutionalLayer::ConvolutionalLayer(const ConvLayerInitor & _initor)
{
	this->_convNodeNum = _initor.KernelNum;
	this->_kernelSize = _initor.KernelSize;
	this->_stride = _initor.Stride;
	this->_inputSize = _initor.InputSize;
	this->_paddingMethod = _initor.PaddingMethod;
	this->_paddingNum = _initor.PaddingNum;

	this->_outputSize.m = _inputSize.m;
	this->_outputSize.n = _inputSize.n;
	this->_paddingM = floor(_kernelSize.m / 2);
	this->_paddingN = floor(_kernelSize.n / 2);

	SetActivationFunction(_initor.ActivationFunction);

	for (size_t i = 0; i < _convNodeNum; i++)
		this->_convNodes.push_back(ConvNode(_kernelSize, _inputSize));
}

void Neural::ConvolutionalLayer::SetInput(const std::vector<MathLib::Matrix<ElemType>>& _input)
{
	this->_input = _input;
}

void Neural::ConvolutionalLayer::SetDelta(const std::vector<MathLib::Matrix<ElemType>>& _delta)
{
	for (size_t i = 0; i < _convNodeNum; i++)
		_convNodes.at(i).featureDelta = _delta.at(i);
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	for (size_t k = 0; k < _convNodeNum; k++) // Travesing kernel
	{
		_convNodes.at(k).feature.Clear();
		for (size_t i = 0; i < _input.size(); i++) // Travesing input
			_convNodes.at(k).feature += (Convolution(_input.at(i), _convNodes.at(k).kernel) + _convNodes.at(k).bias);
		_convNodes.at(k).feature = _convNodes.at(k).feature * ((double)1 / (double)_input.size());
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{

}

void Neural::ConvolutionalLayer::Update(void)
{

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
