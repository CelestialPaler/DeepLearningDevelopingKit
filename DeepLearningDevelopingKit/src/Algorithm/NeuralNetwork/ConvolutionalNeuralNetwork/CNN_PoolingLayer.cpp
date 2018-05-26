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
	this->_paddingM = _inputSize.m - _stride * _outputSize.m;
	this->_paddingN = _inputSize.n - _stride * _outputSize.n;
}

void Neural::PoolingLayer::SetInput(const std::vector<Feature> & _input)
{
	this->_input = _input;
}

void Neural::PoolingLayer::SetDelta(const std::vector<Feature>& _delta)
{
	this->_delta = _delta;
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

void Neural::PoolingLayer::ForwardPropagation(void)
{
	Padding();
	DownSampling();
}

void Neural::PoolingLayer::BackwardPropagation(void)
{
	UpSampling();
}

void Neural::PoolingLayer::Update(void)
{

}

void Neural::PoolingLayer::DownSampling(void)
{
	_output.clear();
	for (size_t i = 0; i < _input.size(); i++)
	{
		Feature pooledFeature = MaxPool(_paddedInput.at(i));
		_output.push_back(pooledFeature);
	}
}

void Neural::PoolingLayer::UpSampling(void)
{
	_deltaDepooled.clear();
	for (size_t i = 0; i < _delta.size(); i++)
	{
		MathLib::Matrix<ElemType> deltaDepoolMat(_outputSize.m * _poolSize.m, _outputSize.n * _poolSize.n);
		for (size_t a = 0; a < _outputSize.m; a++)
		{
			for (size_t b = 0; b < _outputSize.n; b++)
			{
				for (size_t m = 0; m < _poolSize.m; m++)
				{
					for (size_t n = 0; n < _poolSize.n; n++)
					{
						deltaDepoolMat(a * _poolSize.m + m, b * _poolSize.n + n) = _delta.at(i)(a, b);
					}
				}
			}
		}
		_deltaDepooled.push_back(deltaDepoolMat);
	}
}

void Neural::PoolingLayer::Padding(void)
{
	_paddedInput.clear();
	for (size_t i = 0; i < _input.size(); i++)
	{
		MathLib::Matrix<ElemType> newMatrix = Pad::Padding(_input.at(i), _paddingMethod, _paddingNum, _paddingM, _paddingN);
		_paddedInput.push_back(newMatrix);
	}
}
