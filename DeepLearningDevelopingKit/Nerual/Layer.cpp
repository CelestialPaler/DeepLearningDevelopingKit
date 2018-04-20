/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "Layer.h"

/***************************************************************************************************/
// Class : InputLayer
/// Used for input data.
Nerual::InputLayer::InputLayer(void)
{

}

Nerual::InputLayer::InputLayer(const size_t _n)
{
	for (size_t i = 0; i < _n; i++)
	{
		InputNode tempNode = *new InputNode();
		this->_nodes.push_back(tempNode);
	}
	this->n = _n;
}

void Nerual::InputLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).tempInput = _vec(i);
	}
}

Vector<Nerual::ElemType> Nerual::InputLayer::GetOutput(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

Vector<Nerual::ElemType> Nerual::InputLayer::BackwardPropagation(const Vector<ElemType>& _vec)
{
	return Vector<ElemType>();
}

void Nerual::InputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).Calculate();
	}
}

ostream & Nerual::operator<<(ostream & _outstream, InputLayer & _layer)
{
	_outstream << typeid(_layer).name() << endl;
	_outstream << "	Node Num : " << _layer.n << endl;
	return _outstream;
}


/***************************************************************************************************/
// Class : HiddenLayer
/// Used for input data.
Nerual::HiddenLayer::HiddenLayer(void)
{
}

Nerual::HiddenLayer::HiddenLayer(const size_t _n, const size_t _m)
{
	for (size_t i = 0; i < _n; i++)
	{
		HiddenNode tempNode = *new HiddenNode(_m);
		this->_nodes.push_back(tempNode);
	}
	this->n = _n;
	this->m = _m;
}

void Nerual::HiddenLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			_nodes.at(i).tempInput(j) = _vec(j);
		}
	}
}

Vector<Nerual::ElemType> Nerual::HiddenLayer::GetOutput(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

void Nerual::HiddenLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).Calculate();
	}
}

Vector<Nerual::ElemType> Nerual::HiddenLayer::BackwardPropagation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
		_nodes.at(i).valueDelta = _vec(i);

	for (size_t i = 0; i < n; i++) // All the outputNodes
		for (size_t j = 0; j < m; j++)
			_nodes.at(i).weightDelta(j) = 2 * _nodes.at(i).valueDelta * (_nodes.at(i).value * (1 - _nodes.at(i).value)) * _nodes.at(i).tempInput(j);

	for (size_t i = 0; i < n; i++) // All the outputNodes
		_nodes.at(i).biasDelta = 2 * _nodes.at(i).valueDelta * (_nodes.at(i).value * (1 - _nodes.at(i).value));

	Vector<ElemType> tempVec(m);
	for (size_t i = 0; i < m; i++)
	{
		ElemType tempDelta = 0;
		for (size_t j = 0; j < n; j++)
		{
			tempDelta += 2 * _nodes.at(j).valueDelta * (_nodes.at(j).value * (1 - _nodes.at(j).value)) * _nodes.at(j).weight(i);
		}
		tempVec(i) = tempDelta;
	}
	return tempVec;
}

void Nerual::HiddenLayer::Update(void)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
			_nodes.at(i).weight(j) -= _nodes.at(i).weightDelta(j);
		_nodes.at(i).bias -= _nodes.at(i).biasDelta;
	}
}


/***************************************************************************************************/
// Class : OutputLayer
/// Used for output data.
Nerual::OutputLayer::OutputLayer(void)
{
}

Nerual::OutputLayer::OutputLayer(const size_t _n, const size_t _m)
{
	for (size_t i = 0; i < _n; i++)
	{
		OutputNode tempNode = *new OutputNode(_m);
		this->_nodes.push_back(tempNode);
	}
	this->n = _n;
	this->m = _m;
}

void Nerual::OutputLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			_nodes.at(i).tempInput(j) = _vec(j);
		}
	}
}

Vector<Nerual::ElemType> Nerual::OutputLayer::GetOutput(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

Nerual::ElemType Nerual::OutputLayer::GetLoss(void)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).loss = MES(_nodes.at(i).value, _nodes.at(i).expectation);
	}

	ElemType temp = 0;
	for (size_t i = 0; i < n; i++)
	{
		temp += _nodes.at(i).loss;
	}
	temp = temp / n;
	return temp;
}

Vector<Nerual::ElemType> Nerual::OutputLayer::GetDelta(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value - _nodes.at(i).expectation;
	}
	return temp;
}

void Nerual::OutputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).Calculate();
	}
}

Vector<Nerual::ElemType> Nerual::OutputLayer::BackwardPropagation(const Vector<ElemType> & _vec)
{
	for (size_t i = 0; i < n; i++)
		_nodes.at(i).valueDelta = _vec(i);

	for (size_t i = 0; i < n; i++) // All the outputNodes
		for (size_t j = 0; j < n; j++)
			_nodes.at(i).weightDelta(j) = 2 * _nodes.at(i).valueDelta * (_nodes.at(i).value * (1 - _nodes.at(i).value)) * _nodes.at(i).tempInput(j);

	for (size_t i = 0; i < n; i++) // All the outputNodes
		_nodes.at(i).biasDelta = 2 * _nodes.at(i).valueDelta * (_nodes.at(i).value * (1 - _nodes.at(i).value));

	Vector<ElemType> tempVec(m);
	for (size_t i = 0; i < m; i++)
	{
		ElemType tempDelta = 0;
		for (size_t j = 0; j < n; j++)
		{
			tempDelta += 2 * _nodes.at(j).valueDelta * (_nodes.at(j).value * (1 - _nodes.at(j).value)) * _nodes.at(j).weight(i);
		}
		tempVec(i) = tempDelta;
	}
	return tempVec;
}

void Nerual::OutputLayer::Update(void)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
			_nodes.at(i).weight(j) -= _nodes.at(i).weightDelta(j);
		_nodes.at(i).bias -= _nodes.at(i).biasDelta;
	}
}

void Nerual::OutputLayer::SetExpectation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).expectation = _vec(i);
	}
}

