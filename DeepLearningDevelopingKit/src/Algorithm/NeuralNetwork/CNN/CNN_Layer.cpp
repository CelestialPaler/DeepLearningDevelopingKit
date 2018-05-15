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
