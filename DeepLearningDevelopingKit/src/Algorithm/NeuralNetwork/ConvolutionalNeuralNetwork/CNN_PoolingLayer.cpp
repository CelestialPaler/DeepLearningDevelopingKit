/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			 Pooling Layer     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#include "CNN_PoolingLayer.h"

Neural::PoolingLayer::PoolingLayer(const PoolLayerInitor & _initor)
{
	this->_stride = _initor.Stride;
	this->_poolSize = _initor.PoolSize;
	this->_inputSize = _initor.InputSize;
	this->_poolingMethod = _initor.PoolingMethod;
	this->_paddingMethod = _initor.PaddingMethod;
	this->_paddingNum = _initor.PaddingNum;

	this->_outputSize.m = _inputSize.m /_stride;
	this->_outputSize.n = _inputSize.n / _stride;
	this->PaddingM = _inputSize.m - _stride * _outputSize.m;
	this->PaddingN = _inputSize.n - _stride * _outputSize.n;
}

void Neural::PoolingLayer::SetInput(const std::vector<Feature> & _input)
{
	this->_input = _input;
}

Neural::Feature Neural::PoolingLayer::MaxPool(const Feature & _feature)
{
	Feature tempFeature(_outputSize.m, _outputSize.n,MathLib::MatrixType::Zero);
	size_t kernelOffsetM = 0;
	size_t kernelOffsetN = 0;
	for (size_t a = 0; a < _outputSize.m; a++)
	{
		for (size_t b = 0; b < _outputSize.n; b++)
		{
			tempFeature(a, b) = MaxPoolPart(_feature, kernelOffsetM, kernelOffsetN);
			kernelOffsetN += _stride;
		}
		kernelOffsetM += _stride;
		kernelOffsetN = 0;
	}
	return tempFeature;
}

Neural::ElemType Neural::PoolingLayer::MaxPoolPart(const Feature & _feature, const size_t m, const size_t n)
{
	ElemType max{ 0.f };
	for (size_t i = 0; i < _poolSize.m; i++)
	{
		for (size_t j = 0; j < _poolSize.n; j++)
		{
			if (max < _feature(m + i, n + j))
				max = _feature(m + i, n + j);
		}
	}
	return max;
}

void Neural::PoolingLayer::DownSampling(void)
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		Feature pooledFeature = MaxPool(_paddedInput.at(i));
		_output.push_back(pooledFeature);
	}
}

void Neural::PoolingLayer::Padding(void)
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		MathLib::Matrix<ElemType> newMatrix = Pad::Padding(_input.at(i), _paddingMethod, _paddingNum, PaddingM, PaddingN);
		_paddedInput.push_back(newMatrix);
	}
}
