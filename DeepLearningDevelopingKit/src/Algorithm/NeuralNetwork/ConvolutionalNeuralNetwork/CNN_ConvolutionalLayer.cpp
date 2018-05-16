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
	this->_kernalNum = _initor.KernalNum;
	this->_kernalSize = _initor.KernalSize;
	this->_stride = _initor.Stride;
	this->_paddingMethod = _initor.PaddingMethod;
	this->_paddingNum = _initor.PaddingNum;
	this->_originalInput.Init(_initor.InputSize.m, _initor.InputSize.n);
	for (size_t i = 0; i < _kernalNum; i++)
	{
		ConvKernal newKernal = *new ConvKernal(_kernalSize.m, _kernalSize.n, MathLib::MatrixType::Random);
		this->_kernals.push_back(newKernal);
	}
	switch (_initor.PaddingMethod)
	{
	default:
		for (size_t i = 0; i < _kernalNum; i++)
		{
			ConvFeature newFeature = *new ConvFeature(_originalInput.GetSize().m / _stride, _originalInput.GetSize().n / _stride);
			this->_features.push_back(newFeature);
		}
		break;
	}
	SetActivationFunction(_initor.ActivationFunction);
	SetLossFunction(_initor.LossFunction);
}

void Neural::ConvolutionalLayer::SetInput(const MathLib::Matrix<ElemType>& _input)
{
	this->_originalInput = _input;
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
	// Travesing every kernal in the layer.
	for (size_t k = 0; k < _kernalNum; k++)
	{
		ElemType sum{ 0.f };
		size_t kernalOffsetM{ 0 }, kernalOffsetN{ 0 };
		for (size_t a = 0; a < _features.at(0).GetSize().m; a++)
		{
			for (size_t b = 0; b < _features.at(0).GetSize().n; b++)
			{
				_features.at(k)(a, b) = activationFunction(Convolution(_paddedInput, _kernals.at(k), kernalOffsetM, kernalOffsetN));
				kernalOffsetM += _stride;
			}
			kernalOffsetM = 0;
			kernalOffsetN += _stride;
		}
	}
}

void Neural::ConvolutionalLayer::BackwardPropagation(void)
{

}

void Neural::ConvolutionalLayer::Padding(void)
{
	size_t paddingSize = 2;

	switch (this->_paddingMethod)
	{
	case Neural::PaddingMethod::LeftUp:
		_paddedInput.Init(_originalInput.GetSize().m + paddingSize, _originalInput.GetSize().n + paddingSize);

		for (size_t i = 0; i < _paddedInput.GetSize().m; i++)
			for (size_t j = 0; j < _paddedInput.GetSize().n; j++)
				if (i< paddingSize || j< paddingSize)
					switch (this->_paddingNum)
					{
					case Neural::PaddingNum::ZeroPadding:
						_paddedInput(i, j) = 0;
						break;
					case Neural::PaddingNum::OnePadding:
						_paddedInput(i, j) = 1;
						break;
					case Neural::PaddingNum::RandomPadding:
						break;
					default:
						break;
					}

		for (size_t i = 0; i < _originalInput.GetSize().m; i++)
			for (size_t j = 0; j < _originalInput.GetSize().n; j++)
				_paddedInput(i + paddingSize, j + paddingSize) = _originalInput(i, j);
		break;
	case Neural::PaddingMethod::LeftDown:
		_paddedInput.Init(_originalInput.GetSize().m + paddingSize, _originalInput.GetSize().n + paddingSize);

		for (size_t i = 0; i < _paddedInput.GetSize().m; i++)
			for (size_t j = 0; j < _paddedInput.GetSize().n; j++)
				if (i> _paddedInput.GetSize().m - paddingSize || j< paddingSize)
					switch (this->_paddingNum)
					{
					case Neural::PaddingNum::ZeroPadding:
						_paddedInput(i, j) = 0;
						break;
					case Neural::PaddingNum::OnePadding:
						_paddedInput(i, j) = 1;
						break;
					case Neural::PaddingNum::RandomPadding:
						break;
					default:
						break;
					}

		for (size_t i = 0; i < _originalInput.GetSize().m; i++)
			for (size_t j = 0; j < _originalInput.GetSize().n; j++)
				_paddedInput(i, j + paddingSize) = _originalInput(i, j);
		break;
	case Neural::PaddingMethod::RightUp:
		_paddedInput.Init(_originalInput.GetSize().m + paddingSize, _originalInput.GetSize().n + paddingSize);

		for (size_t i = 0; i < _paddedInput.GetSize().m; i++)
			for (size_t j = 0; j < _paddedInput.GetSize().n; j++)
				if (i< paddingSize || j> _paddedInput.GetSize().n - paddingSize)
					switch (this->_paddingNum)
					{
					case Neural::PaddingNum::ZeroPadding:
						_paddedInput(i, j) = 0;
						break;
					case Neural::PaddingNum::OnePadding:
						_paddedInput(i, j) = 1;
						break;
					case Neural::PaddingNum::RandomPadding:
						break;
					default:
						break;
					}

		for (size_t i = 0; i < _originalInput.GetSize().m; i++)
			for (size_t j = 0; j < _originalInput.GetSize().n; j++)
				_paddedInput(i + paddingSize, j) = _originalInput(i, j);
		break;
	case Neural::PaddingMethod::RightDown:
		_paddedInput.Init(_originalInput.GetSize().m + paddingSize, _originalInput.GetSize().n + paddingSize);

		for (size_t i = 0; i < _paddedInput.GetSize().m; i++)
			for (size_t j = 0; j < _paddedInput.GetSize().n; j++)
				if (i> _paddedInput.GetSize().m - paddingSize|| j> _paddedInput.GetSize().n - paddingSize)
					switch (this->_paddingNum)
					{
					case Neural::PaddingNum::ZeroPadding:
						_paddedInput(i, j) = 0;
						break;
					case Neural::PaddingNum::OnePadding:
						_paddedInput(i, j) = 1;
						break;
					case Neural::PaddingNum::RandomPadding:
						break;
					default:
						break;
					}

		for (size_t i = 0; i < _originalInput.GetSize().m; i++)
			for (size_t j = 0; j < _originalInput.GetSize().n; j++)
				_paddedInput(i, j) = _originalInput(i, j);
		break;
	case Neural::PaddingMethod::Surround:
		_paddedInput.Init(_originalInput.GetSize().m + paddingSize * 2, _originalInput.GetSize().n + paddingSize * 2);

		for (size_t i = 0; i < _paddedInput.GetSize().m; i++)
			for (size_t j = 0; j < _paddedInput.GetSize().n; j++)
				if (i< paddingSize || j< paddingSize|| i> _paddedInput.GetSize().m - paddingSize || j> _paddedInput.GetSize().n - paddingSize)
					switch (this->_paddingNum)
					{
					case Neural::PaddingNum::ZeroPadding:
						_paddedInput(i, j) = 0;
						break;
					case Neural::PaddingNum::OnePadding:
						_paddedInput(i, j) = 1;
						break;
					case Neural::PaddingNum::RandomPadding:
						break;
					default:
						break;
					}

		for (size_t i = 0; i < _originalInput.GetSize().m; i++)
			for (size_t j = 0; j < _originalInput.GetSize().n; j++)
				_paddedInput(i + paddingSize, j + paddingSize) = _originalInput(i, j);
		break;
	default:
		_paddedInput.Init(_originalInput.GetSize().m + paddingSize, _originalInput.GetSize().n + paddingSize);

		for (size_t i = 0; i < _paddedInput.GetSize().m; i++)
			for (size_t j = 0; j < _paddedInput.GetSize().n; j++)
				if (i> _paddedInput.GetSize().m - paddingSize || j> _paddedInput.GetSize().n - paddingSize)
					switch (this->_paddingNum)
					{
					case Neural::PaddingNum::ZeroPadding:
						_paddedInput(i, j) = 0;
						break;
					case Neural::PaddingNum::OnePadding:
						_paddedInput(i, j) = 1;
						break;
					case Neural::PaddingNum::RandomPadding:
						break;
					default:
						break;
					}

		for (size_t i = 0; i < _originalInput.GetSize().m; i++)
			for (size_t j = 0; j < _originalInput.GetSize().n; j++)
				_paddedInput(i + paddingSize, j + paddingSize) = _originalInput(i, j);
		break;
	}

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

Neural::ElemType Neural::ConvolutionalLayer::Convolution(const MathLib::Matrix<ElemType>& _input, const MathLib::Matrix<ElemType>& _kernal, const size_t _m, const size_t _n)
{
	ElemType sum{ 0.f };
	MathLib::Size size = _kernal.GetSize();
	for (size_t i = 0; i < size.m; i++)
		for (size_t j = 0; j < size.n; j++)
			sum += _input(_m + i, _n + j)* _kernal(i, j);
	return sum;
}
