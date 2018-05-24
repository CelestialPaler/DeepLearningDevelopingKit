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

void Neural::ConvolutionalLayer::SetDelta(const std::vector<MathLib::Matrix<ElemType>>& _delta)
{
	this->_delta = _delta;
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	Padding();
	// Travesing every kernel in the layer.
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		_convNodes.at(k).feature.Clear();
		for (size_t i = 0; i < _input.size(); i++)
		{
			//_convNodes.at(k).feature += (Convolution(_paddedInput.at(i), _convNodes.at(k).kernel) + _convNodes.at(k).bias);
			_convNodes.at(k).feature += (Convolution(_paddedInput.at(i), _convNodes.at(k).kernel));
		}
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{
	_deltaDeconved.clear();
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		MathLib::Matrix<ElemType> tempMat(_inputSize.m, _inputSize.n);
		for (size_t i = 0; i < _input.size(); i++)
		{
			for (size_t j = 0; j < _delta.size(); j++)
			{
				tempMat += Rot180(MatrixConvolution(_delta.at(j), Rot180(_convNodes.at(k).kernel)));
			}
		}
		_deltaDeconved.push_back(tempMat);
	}
}

void Neural::ConvolutionalLayer::Update(void)
{
	MathLib::Matrix<double> sumMatrix(_kernelSize.m, _kernelSize.n,MathLib::MatrixType::Ones);
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		MathLib::Matrix<Neural::ElemType> temp(_kernelSize.m, _kernelSize.n);
		size_t kernalOffsetM = 0;
		size_t kernalOffsetN = 0;
		for (size_t i = 0; i < _kernelSize.m; i++)
		{
			for (size_t j = 0; j < _kernelSize.n; j++)
			{
				temp(i, j) = MatrixConvSum(_deltaDeconved.at(k), sumMatrix, kernalOffsetM, kernalOffsetN);
				kernalOffsetN += _stride;
			}
			kernalOffsetM += _stride;
			kernalOffsetN = 0;
		}
		double normalizeIndex = (double)1 / (double)(temp.ColumeSize() * temp.RowSize());
		temp = temp * normalizeIndex;
		// std::cout << "Delta pooled : " << temp << std::endl;
		_convNodes.at(k).kernel -= temp * learnRate;
	}


}

void Neural::ConvolutionalLayer::Padding(void)
{
	_paddedInput.clear();
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

Neural::ElemType Neural::ConvolutionalLayer::MatrixConvSum(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2, const size_t _m, const size_t _n)
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
			temp(i, j) = activationFunction(MatrixConvSum(_input, _kernel, kernalOffsetM, kernalOffsetN));
			kernalOffsetN += _stride;
		}
		kernalOffsetM += _stride;
		kernalOffsetN = 0;
	}
	return temp;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Rot180(const MathLib::Matrix<ElemType>& _mat)
{
	size_t sizeM = _mat.ColumeSize();
	size_t sizeN = _mat.RowSize();
	MathLib::Matrix<ElemType> temp(sizeM, sizeN);
	for (size_t i = 0; i < sizeM; i++)
	{
		for (size_t j = 0; j < sizeN; j++)
		{
			temp(i, j) = _mat(sizeM - 1 - i, sizeN - 1 - j);
		}
	}
	return temp;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::MatrixConvolution(MathLib::Matrix<ElemType> _mat1, MathLib::Matrix<ElemType> _mat2)
{
	size_t mat1M = _inputSize.m + _kernelSize.m - 1 - _stride * _outputSize.m;
	size_t mat1N = _inputSize.n + _kernelSize.n - 1 - _stride * _outputSize.n;
	_mat1 = Pad::Padding(_mat1, PaddingMethod::RightDown, PaddingNum::ZeroPadding, mat1M, mat1N);
	MathLib::Matrix<Neural::ElemType> temp(_inputSize.m, _inputSize.n);
	size_t offsetM = 0;
	size_t offsetN = 0;
	for (size_t i = 0; i < _inputSize.m; i++)
	{
		for (size_t j = 0; j < _inputSize.n; j++)
		{
			temp(i, j) = MatrixConvSum(_mat1, _mat2, offsetM, offsetN);
			offsetN += _stride;
		}
		offsetM += _stride;
		offsetN = 0;
	}
	return temp;
}
