/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Process Layer     	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "CNN_ProcessLayer.h"


Neural::ProcessLayer::ProcessLayer(const ProcessLayerInitor _initor)
{
	this->_dataSize= _initor.InputSize;
	this->processFunction = _initor.ProcessFunction;
	this->processFunctionDerivative = _initor.ProcessFunctionDerivative;
}

void Neural::ProcessLayer::SetInput(const std::vector<MathLib::Matrix<ElemType>>& _input)
{
	this->_data = _input;
}

void Neural::ProcessLayer::Process(void)
{
	for (size_t i = 0; i < _data.size(); i++)
	{
		for (size_t a = 0; a < _dataSize.m; a++)
		{
			for (size_t b = 0; b < _dataSize.n; b++)
			{
				_data.at(i)(a, b) = processFunction(_data.at(i)(a, b));
			}
		}
	}
}

void Neural::ProcessLayer::Deprocess(void)
{
	for (size_t i = 0; i < _data.size(); i++)
	{
		for (size_t a = 0; a < _dataSize.m; a++)
		{
			for (size_t b = 0; b < _dataSize.n; b++)
			{
				_data.at(i)(a, b) = processFunctionDerivative(_data.at(i)(a, b)) * _data.at(i)(a, b);
			}
		}
	}
}


