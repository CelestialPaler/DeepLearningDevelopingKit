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

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
Nerual::InputLayer::InputLayer(const size_t _n, const size_t _m)
{
	for (size_t i = 0; i < _m; i++)
	{
		InputNode tempNode = *new InputNode();
		this->_nodes.push_back(tempNode);
	}
	this->n = _n;
	this->m = _m;
}

// "<<" operator
/// Used for streaming in format.
ostream & Nerual::operator<<(ostream & _outstream, InputLayer & _layer)
{
	_outstream << typeid(_layer).name() << endl;
	_outstream << "	Node Num : " << _layer.m << endl;
	return _outstream;
}

// Set the input of the layer.
/// Which means set the nodes` tempInput.
void Nerual::InputLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).tempInput = _vec(i);
	}
}

// Get the output of the layer.
/// Which means get the value pf all nodes in Vector.
Vector<Nerual::ElemType> Nerual::InputLayer::GetOutput(void)
{
	Vector<ElemType> temp(m);
	for (size_t i = 0; i < m; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

// ForwardPropagation Function
/// Calculate the value of each node.
void Nerual::InputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).Calculate();
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
Vector<Nerual::ElemType> Nerual::InputLayer::BackwardPropagation(const Vector<ElemType>& _vec)
{
	Vector<ElemType> temp(n);
	return temp;
}

// Update Function
/// Update the weight and bias of each node.
void Nerual::InputLayer::Update(void)
{
}




/***************************************************************************************************/
// Class : HiddenLayer
/// Used for input data.

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
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

// Set the input of the layer.
/// Which means set the nodes` tempInput.
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

// Get the output of the layer.
/// Which means get the value pf all nodes in Vector.
Vector<Nerual::ElemType> Nerual::HiddenLayer::GetOutput(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

// ForwardPropagation Function
/// Calculate the value of each node.
void Nerual::HiddenLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).Calculate();
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
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

// Update Function
/// Update the weight and bias of each node.
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

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
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

// Set the input of the layer.
/// Which means set the nodes` tempInput.
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

// Set the expectation of the OutputLayer.
void Nerual::OutputLayer::SetExpectation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).expectation = _vec(i);
	}
}

// Get the output of the layer.
/// Which means get the value pf all nodes in Vector.
Vector<Nerual::ElemType> Nerual::OutputLayer::GetOutput(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

// Get the estimated loss between output and expectation.
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

// Get the exact error(Delta) between output and expectation.
Vector<Nerual::ElemType> Nerual::OutputLayer::GetDelta(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < n; i++)
	{
		temp(i) = _nodes.at(i).value - _nodes.at(i).expectation;
	}
	return temp;
}

// ForwardPropagation Function
/// Calculate the value of each node.
void Nerual::OutputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).Calculate();
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
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

// Update Function
/// Update the weight and bias of each node.
void Nerual::OutputLayer::Update(void)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
			_nodes.at(i).weight(j) -= _nodes.at(i).weightDelta(j);
		_nodes.at(i).bias -= _nodes.at(i).biasDelta;
	}
}


