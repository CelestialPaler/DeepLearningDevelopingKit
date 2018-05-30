/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 Convolutional Neural Network     	                                          */
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
	this->_derivativeLastLayer = _delta;
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	for (size_t k = 0; k < _convNodeNum; k++) // Travesing kernel
	{
		_convNodes.at(k).feature.Clear();
		for (size_t i = 0; i < _input.size(); i++) // Travesing input
		{
			_convNodes.at(k).feature += (ConvolutionCal(_input.at(i), _convNodes.at(k).kernel) + _convNodes.at(k).bias);
		}
		_convNodes.at(k).feature = _convNodes.at(k).feature * ((double)1 / (double)_input.size());
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{
	_derivative.clear();
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		MathLib::Matrix<ElemType> tempMat(_inputSize.m, _inputSize.n);
		for (size_t i = 0; i < _input.size(); i++)
		{
			for (size_t j = 0; j < _convNodeNum; j++)
			{
				auto a = ConvolutionCal(_derivativeLastLayer.at(j), Rot180(_convNodes.at(k).kernel));
				tempMat += Hadamard(a, _convNodes.at(j).feature);
			}
		}
		_derivative.push_back(tempMat);
	}


	for (size_t k = 0; k < _convNodeNum; k++)
	{
		_convNodes.at(k).kernelDelta.Clear();
		_convNodes.at(k).biasDelta = 0;
		for (size_t a = 0; a < _input.size(); a++)
		{
			for (size_t m = 0; m < _kernelSize.m; m++)
			{
				for (size_t n = 0; n < _kernelSize.n; n++)
				{
					ElemType sum = 0;
					for (size_t i = 0; i < _inputSize.m - _kernelSize.m; i++)
					{
						for (size_t j = 0; j < _inputSize.n - _kernelSize.n; j++)
						{
							sum += _derivative.at(k)(i, j) * _input.at(a)(i + m, j + n);
						}
					}
					_convNodes.at(k).kernelDelta(m, n) = sum;
				}
			}
		}
		
		_convNodes.at(k).biasDelta = _derivative.at(k).Sum();
	}

}

void Neural::ConvolutionalLayer::Update(void)
{
	for (size_t k = 0; k < _convNodeNum; k++)
	{
		_convNodes.at(k).kernel -= _convNodes.at(k).kernelDelta * learnRate;
		_convNodes.at(k).bias -= _convNodes.at(k).biasDelta * learnRate;
	}
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

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::ConvolutionCal(const MathLib::Matrix<ElemType> _mat1, const MathLib::Matrix<ElemType> _mat2)
{
	MathLib::Matrix<Neural::ElemType> temp(_inputSize.m, _inputSize.n);

	MathLib::Matrix<Neural::ElemType> mat1Padded = Pad::Padding(_mat1, PaddingMethod::Surround, PaddingNum::ZeroPadding, _paddingM, _paddingN);
	size_t offsetM{ 0 }, offsetN{ 0 };
	for (size_t i = 0; i < _inputSize.m; i++)
	{
		for (size_t j = 0; j < _inputSize.n; j++)
		{
			temp(i, j) = ConvolutionSum(mat1Padded, _mat2, offsetM, offsetN);
			offsetN += _stride;
		}
		offsetM += _stride;
		offsetN = 0;
	}
	return temp;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Convolution(const MathLib::Matrix<ElemType> _mat1, const MathLib::Matrix<ElemType> _mat2)
{
	return Correlation(_mat1, Rot180(_mat2));
}

Neural::ElemType Neural::ConvolutionalLayer::ConvolutionSum(const MathLib::Matrix<ElemType> _mat1, const MathLib::Matrix<ElemType> _mat2, const size_t _m, const size_t _n)
{
	return CorrelationSum(_mat1, Rot180(_mat2), _m, _n);
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Correlation(const MathLib::Matrix<ElemType> _mat1, const MathLib::Matrix<ElemType> _mat2)
{
	return Hadamard(_mat1, _mat2);
}

Neural::ElemType Neural::ConvolutionalLayer::CorrelationSum(const MathLib::Matrix<ElemType> _mat1, const MathLib::Matrix<ElemType> _mat2, const size_t _m, const size_t _n)
{
	ElemType sum = 0;
	for (size_t i = 0; i < _mat2.ColumeSize(); i++)
		for (size_t j = 0; j < _mat2.RowSize(); j++)
			sum += _mat1(i + _m, j + _n) * _mat2(i, j);
	return sum;
}

MathLib::Matrix<Neural::ElemType> Neural::ConvolutionalLayer::Hadamard(const MathLib::Matrix<ElemType>& _mat1, const MathLib::Matrix<ElemType>& _mat2)
{
	MathLib::Matrix<ElemType> temp(_mat2.ColumeSize(), _mat2.RowSize());
	for (size_t i = 0; i < _mat2.ColumeSize(); i++)
		for (size_t j = 0; j < _mat2.RowSize(); j++)
			temp(i, j) = _mat1(i, j) * _mat2(i, j);
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