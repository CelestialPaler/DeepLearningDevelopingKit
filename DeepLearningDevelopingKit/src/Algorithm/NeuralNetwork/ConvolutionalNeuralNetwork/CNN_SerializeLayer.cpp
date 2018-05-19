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
}

void Neural::SerializeLayer::SetSerializedMat(const MathLib::Matrix<ElemType>& _input)
{
	_serializedMat = _input;
}

void Neural::SerializeLayer::SetDeserializedMat(const std::vector<MathLib::Matrix<ElemType>>& _input)
{
	_deserializedMat = _input;
}

void Neural::SerializeLayer::Serialize(void)
{
	_serializedMat.Init(_serializedSize.m, _serializedSize.n);
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
}

void Neural::SerializeLayer::Deserialize(void)
{
}
