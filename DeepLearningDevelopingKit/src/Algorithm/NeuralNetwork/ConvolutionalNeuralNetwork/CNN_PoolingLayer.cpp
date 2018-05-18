/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			 Pooling Layer     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#include "CNN_PoolingLayer.h"

Neural::PoolingLayer::PoolingLayer(const PoolLayerInitor & _initor)
{
	this->_poolingMethod = _initor.PoolingMethod;
	this->_stride = _initor.Stride;
	this->_poolSize = _initor.PoolSize;
	this->_inputSize = _initor.InputSize;
	this->_paddingNum = _initor.PaddingNum;
}

void Neural::PoolingLayer::SetInput(const std::vector<Feature> & _input)
{
	this->_input = _input;
}

Neural::ElemType Neural::PoolingLayer::MaxPool(const Feature & _feature, const size_t m, const size_t n)
{
	ElemType max{ 0.f };
	for (size_t i = 0; i < _poolSize.m; i++)
		for (size_t j = 0; j < _poolSize.n; j++)
			if (max < _feature(m + i, n + j))
				max = _feature(m + i, n + j);

	return max;
}

void Neural::PoolingLayer::DownSampling(void)
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		size_t kernelOffsetM{ 0 }, kernelOffsetN{ 0 };
		for (size_t a = 0; a < _input.at(i).GetSize().m / _stride; a++)
		{
			for (size_t b = 0; b < _input.at(i).GetSize().n / _stride; b++)
			{
				_output.at(i)(a, b) = MaxPool(_input.at(i), kernelOffsetM, kernelOffsetN);
				kernelOffsetM += _stride;
			}
			kernelOffsetM = 0;
			kernelOffsetN += _stride;
		}
	}
}

void Neural::PoolingLayer::Padding(void)
{
	for (size_t i = 0; i < _input.size(); i++)
	{
		_input.at(i) = Pad::Padding(_input.at(i), _paddingMethod, _paddingNum);
	}
}
