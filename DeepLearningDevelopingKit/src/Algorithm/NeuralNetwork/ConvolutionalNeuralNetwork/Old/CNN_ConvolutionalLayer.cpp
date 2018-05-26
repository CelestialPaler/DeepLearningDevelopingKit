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
	this->_paddingM = floor(_kernelSize.m / 2);
	this->_paddingN = floor(_kernelSize.n / 2);
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
	this->_deltaLastLayer = _delta;
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	// Padding();
	// Travesing every kernel in the layer.
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		_convNodes.at(k).feature.Clear();
		for (size_t i = 0; i < _input.size(); i++)
		{
			_convNodes.at(k).bias = 0;
			_convNodes.at(k).feature += (Convolution(_input.at(i), _convNodes.at(k).kernel) + _convNodes.at(k).bias);
		}
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{
	_delta.clear();
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		MathLib::Matrix<ElemType> tempMat(_inputSize.m, _inputSize.n);
		for (size_t i = 0; i < _input.size(); i++)
		{
			for (size_t j = 0; j < _deltaLastLayer.size(); j++)
			{
				tempMat += Hadamard(Convolution(_deltaLastLayer.at(j), Rot180(_convNodes.at(k).kernel)), _convNodes.at(j).feature);
			}
		}
		_delta.push_back(tempMat);
	}
}

void Neural::ConvolutionalLayer::Update(void)
{
	for (size_t i = 0; i < _delta.size(); i++)
	{
		_convNodes.at(i).bias -= _delta.at(i).Sum();
	}
	for (size_t i = 0; i < _delta.size(); i++)
	{
		for (size_t j = 0; j < _kernelSize.m; j++)
		{
			for (size_t k = 0; k < _kernelSize.n; k++)
			{
				_convNodes.at(i).kernel(j, k) += Hadamard(Rot180(_input.at(i)), _delta.at(i))(j + 1, k + 1);
			}
		}
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

Neural::ElemType Neural::ConvolutionalLayer::CorrelationSum(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2, const size_t _m, const size_t _n)
{
	ElemType sum = 0;
	for (size_t i = 0; i < _mat2.ColumeSize(); i++)
	{
		for (size_t j = 0; j < _mat2.RowSize(); j++)
		{
			sum += _mat1(i + _m, j + _n) * _mat2(i, j);
		}
	}
	return sum;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Hadamard(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2)
{
	MathLib::Matrix<ElemType> temp(_mat2.ColumeSize(), _mat2.RowSize());
	for (size_t i = 0; i < _mat2.ColumeSize(); i++)
	{
		for (size_t j = 0; j < _mat2.RowSize(); j++)
		{
			temp(i, j) = _mat1(i, j) * _mat2(i, j);
		}
	}
	return temp;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Convolution(const MathLib::Matrix<ElemType> _mat1, const MathLib::Matrix<ElemType> _mat2)
{
	MathLib::Matrix<Neural::ElemType> mat1Padded = Pad::Padding(_mat1, PaddingMethod::Surround, PaddingNum::ZeroPadding, _paddingM, _paddingN);
	MathLib::Matrix<Neural::ElemType> temp(_inputSize.m, _inputSize.n);
	size_t offsetM = 0;
	size_t offsetN = 0;
	//MathLib::Matrix<Neural::ElemType> rotKernel = Rot180(_mat2);
	for (size_t i = 0; i < _inputSize.m; i++)
	{
		for (size_t j = 0; j < _inputSize.n; j++)
		{
			temp(i, j) = CorrelationSum(mat1Padded, _mat2, offsetM, offsetN);
			offsetN += _stride;
		}
		offsetM += _stride;
		offsetN = 0;
	}
	return temp;
}
