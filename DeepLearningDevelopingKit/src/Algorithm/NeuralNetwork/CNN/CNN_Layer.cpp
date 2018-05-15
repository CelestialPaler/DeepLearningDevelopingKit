/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "CNN_Layer.h"


Neural::ConvolutionalLayer::ConvolutionalLayer(const ConvLayerInitor & _initor)
{
	this->_kernalNum = _initor.KernalNum;
	this->_kernalSize = _initor.KernalSize;
	this->_stride = _initor.Stride;
	this->_samplingMethod = _initor.SamplingMethod;
	for (size_t i = 0; i < _kernalNum; i++)
	{
		ConvKernal newKernal = *new ConvKernal(_kernalSize.m, _kernalSize.n);
		this->_kernals.push_back(newKernal);
	}
	switch (_initor.SamplingMethod)
	{
	default:
		for (size_t i = 0; i < _kernalNum; i++)
		{
			ConvFeature newKernal = *new ConvFeature(_kernalSize.m, _kernalSize.n);
			this->_kernals.push_back(newKernal);
		}
		break;
	}
}

void Neural::ConvolutionalLayer::ForwardPropagation(void)
{
	size_t mBias{ 0 };
	size_t nBias{ 0 };
	size_t m{ 0 };
	size_t n{ 0 };
	for (size_t k = 0; k < _kernalNum; k++)
	{
		ElemType sum{ 0.f };
		for (size_t i = 0; i < _kernalSize.m; i++)
			for (size_t j = 0; j < _kernalSize.n; j++)
				sum += _kernals.at(k).weight(i, j) * _input(i + mBias, j + nBias);
		_features.at(k)._data(m, n) = sum;

		if (mBias + _kernalSize.m < _input.RowSize())
		{
			mBias += _stride;
			m++;
		}
		else 
		{
			mBias = 0; 
			m = 0;
			if (nBias + _kernalSize.n < _input.ColumeSize())
			{
				nBias += _stride;
				n++;
			}
			else
			{
				break;
			}
		}
	}

}
