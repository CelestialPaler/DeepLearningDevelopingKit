/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         Serialize Layer     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#include "CNN_SerializeLayer.h"

Neural::SerializeLayer::SerializeLayer(const SerializeLayerInitor _initor)
{
	this->_serializedSize = _initor.SerializeSize;
	this->_deserializedSize = _initor.DeserializeSize;
	_serializedMat.Init(_serializedSize.m, _serializedSize.n);
}

void Neural::SerializeLayer::SetSerializedMat(const MathLib::Matrix<ElemType>& _input)
{
	_serializedMat = _input;
}

void Neural::SerializeLayer::SetDeserializedMat(const std::vector<MathLib::Matrix<ElemType>>& _input)
{
	_deserializedMat = _input;
}

MathLib::Matrix<Neural::ElemType> Neural::SerializeLayer::Serialize(void)
{
	_serializedMat.Clear();
	for (size_t i = 0; i < _deserializedMat.size(); i++)
	{
		for (size_t a = 0; a <_deserializedSize.m; a++)
		{
			for (size_t b = 0; b < _deserializedSize.n; b++)
			{
				_serializedMat(i * _deserializedSize.m*_deserializedSize.n + a * _deserializedSize.m + b, 0) = _deserializedMat.at(i)(a, b);
			}
		}
	}
	return _serializedMat;
}

std::vector<MathLib::Matrix<Neural::ElemType>> Neural::SerializeLayer::Deserialize(void)
{
	_deserializedMat.clear();
	size_t deserializedNum = _serializedSize.m / (_deserializedSize.m * _deserializedSize.n);
	for (size_t i = 0; i < deserializedNum; i++)
	{
		MathLib::Matrix<ElemType> tempMat(_deserializedSize.m, _deserializedSize.n);
		for (size_t a = 0; a <_deserializedSize.m; a++)
		{
			for (size_t b = 0; b < _deserializedSize.n; b++)
			{
				tempMat(a, b) = _serializedMat(i * _deserializedSize.m * _deserializedSize.n + a * _deserializedSize.m + b, 0);
			}
		}
		_deserializedMat.push_back(tempMat);
	}
	return _deserializedMat;
}
