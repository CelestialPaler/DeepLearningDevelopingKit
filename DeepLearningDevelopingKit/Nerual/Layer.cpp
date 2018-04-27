/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "Layer.h"

const double learnRate = 0.5;

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

void Nerual::InputLayer::SetActivationFunction(const ActivationFunction _function)
{
	switch (_function)
	{
	case ActivationFunction::Sigmoid:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	case ActivationFunction::ReLU:
		this->activationFunction = ReLU;
		this->activationFunctionDerivative = ReLUDerivative;
		break;
	default:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	}
}

void Nerual::InputLayer::SetLossFunction(const LossFunction _function)
{
	switch (_function)
	{
	case LossFunction::MES:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	default:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
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
		_nodes.at(i).value = _nodes.at(i).tempInput;
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

void Nerual::InputLayer::BatchDeltaSumUpdate(const size_t _batchSize)
{
}

void Nerual::InputLayer::BatchDeltaSumClear(void)
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
	for (size_t i = 0; i < _m; i++)
	{
		HiddenNode tempNode = *new HiddenNode(_n);
		this->_nodes.push_back(tempNode);
	}
	this->n = _n;
	this->m = _m;
}

// Set the input of the layer.
/// Which means set the nodes` tempInput.
void Nerual::HiddenLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			_nodes.at(i).tempInput(j) = _vec(j);
		}
	}
}

void Nerual::HiddenLayer::SetExpectation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).expectation = _vec(i);
	}
}

void Nerual::HiddenLayer::SetActivationFunction(const ActivationFunction _function)
{
	switch (_function)
	{
	case ActivationFunction::Sigmoid:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	case ActivationFunction::ReLU:
		this->activationFunction = ReLU;
		this->activationFunctionDerivative = ReLUDerivative;
		break;
	default:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	}
}

void Nerual::HiddenLayer::SetLossFunction(const LossFunction _function)
{
	switch (_function)
	{
	case LossFunction::MES:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	default:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	}
}

// Get the output of the layer.
/// Which means get the value pf all nodes in Vector.
Vector<Nerual::ElemType> Nerual::HiddenLayer::GetOutput(void)
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
void Nerual::HiddenLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).value = activationFunction((_nodes.at(i).tempInput * _nodes.at(i).weight).Sum() - _nodes.at(i).bias);
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
Vector<Nerual::ElemType> Nerual::HiddenLayer::BackwardPropagation(const Vector<ElemType>& _vec)
{
	SetExpectation(_vec);
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).valueDelta = _nodes.at(i).value - _nodes.at(i).expectation;
		_nodes.at(i).weightDelta = _nodes.at(i).tempInput * lossFunctionDerivative(_nodes.at(i).value, _nodes.at(i).expectation) * activationFunctionDerivative(_nodes.at(i).value);
		_nodes.at(i).biasDelta = lossFunctionDerivative(_nodes.at(i).value, _nodes.at(i).expectation) * activationFunctionDerivative(_nodes.at(i).value);
	}

	/// Calculate the partial derivative of loss to last layer value and return the expectation of last layer.
	Vector<ElemType> tempVec(n);
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			tempVec(i) += lossFunctionDerivative(_nodes.at(j).value, _nodes.at(j).expectation) * activationFunctionDerivative(_nodes.at(j).value) * _nodes.at(j).weight(i);
	tempVec += _nodes.at(0).tempInput;
	return tempVec;
}

// Update Function
/// Update the weight and bias of each node.
void Nerual::HiddenLayer::Update(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weight += _nodes.at(i).weightDeltaSum * learnRate;
		_nodes.at(i).bias += _nodes.at(i).biasDeltaSum * learnRate;
	}
}

void Nerual::HiddenLayer::BatchDeltaSumUpdate(const size_t _batchSize)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weightDeltaSum += (_nodes.at(i).weightDelta * (1 / (double)_batchSize));
		_nodes.at(i).biasDeltaSum += (_nodes.at(i).biasDelta * (1 / (double)_batchSize));
	}
}

void Nerual::HiddenLayer::BatchDeltaSumClear(void)
{
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			_nodes.at(i).weightDeltaSum(j) = 0;

	for (size_t i = 0; i < m; i++)
		_nodes.at(i).biasDeltaSum = 0;
}


/***************************************************************************************************/
// Class : OutputLayer
/// Used for output data.

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
Nerual::OutputLayer::OutputLayer(const size_t _n, const size_t _m)
{
	for (size_t i = 0; i < _m; i++)
	{
		OutputNode tempNode = *new OutputNode(_n);
		this->_nodes.push_back(tempNode);
	}
	this->n = _n;
	this->m = _m;
}

// Set the input of the layer.
/// Which means set the nodes` tempInput.
void Nerual::OutputLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).tempInput = _vec;
	}
}

// Set the expectation of the OutputLayer.
void Nerual::OutputLayer::SetExpectation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).expectation = _vec(i);
	}
}

void Nerual::OutputLayer::SetActivationFunction(const ActivationFunction _function)
{
	switch (_function)
	{
	case ActivationFunction::Sigmoid:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	case ActivationFunction::ReLU:
		this->activationFunction = ReLU;
		this->activationFunctionDerivative = ReLUDerivative;
		break;
	default:
		this->activationFunction = Sigmoid;
		this->activationFunctionDerivative = SigmoidDerivative;
		break;
	}
}

void Nerual::OutputLayer::SetLossFunction(const LossFunction _function)
{
	switch (_function)
	{
	case LossFunction::MES:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	default:
		this->lossFunction = MES;
		this->lossFunctionDerivative = MESDerivative;
		break;
	}
}

// Get the output of the layer.
/// Which means get the value pf all nodes in Vector.
Vector<Nerual::ElemType> Nerual::OutputLayer::GetOutput(void)
{
	Vector<ElemType> temp(n);
	for (size_t i = 0; i < m; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

// Get the estimated loss between output and expectation.
Nerual::ElemType Nerual::OutputLayer::GetLoss(void)
{
	ElemType temp = 0;
	for (size_t i = 0; i < m; i++)
	{
		temp += _nodes.at(i).lossSum;
	}
	temp = temp / n;
	return temp;
}

// Get the exact error(Delta) between output and expectation.
Vector<Nerual::ElemType> Nerual::OutputLayer::GetDelta(void)
{
	Vector<ElemType> temp(m);
	for (size_t i = 0; i < m; i++)
	{
		temp(i) = _nodes.at(i).value - _nodes.at(i).expectation;
	}
	return temp;
}

// ForwardPropagation Function
/// Calculate the value of each node.
void Nerual::OutputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < m; i++)
	{
		/// θ(∑ X * W - B)
		_nodes.at(i).value = activationFunction((_nodes.at(i).tempInput * _nodes.at(i).weight).Sum() - _nodes.at(i).bias);
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
/// _vec is the expactation of the layer.
Vector<Nerual::ElemType> Nerual::OutputLayer::BackwardPropagation(const Vector<ElemType> & _vec)
{
	SetExpectation(_vec);
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).valueDelta = _nodes.at(i).value - _nodes.at(i).expectation;
		_nodes.at(i).weightDelta = _nodes.at(i).tempInput * lossFunctionDerivative(_nodes.at(i).value, _nodes.at(i).expectation) * activationFunctionDerivative(_nodes.at(i).value);
		_nodes.at(i).biasDelta = lossFunctionDerivative(_nodes.at(i).value, _nodes.at(i).expectation) * activationFunctionDerivative(_nodes.at(i).value);
	}

	/// Calculate the partial derivative of loss to last layer value and return the expectation of last layer.
	Vector<ElemType> tempVec(n);
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			tempVec(i) += lossFunctionDerivative(_nodes.at(j).value, _nodes.at(j).expectation) * activationFunctionDerivative(_nodes.at(j).value) * _nodes.at(j).weight(i);
	tempVec += _nodes.at(0).tempInput;
	return tempVec;
}

// Update Function
/// Update the weight and bias of each node.
void Nerual::OutputLayer::Update(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weight += _nodes.at(i).weightDeltaSum * learnRate;
		_nodes.at(i).bias += _nodes.at(i).biasDeltaSum * learnRate;
	}
}

void Nerual::OutputLayer::BatchDeltaSumUpdate(const size_t _batchSize)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weightDeltaSum += (_nodes.at(i).weightDelta * (1 / (double)_batchSize));
		cout << _nodes.at(i).weightDelta << endl;
		_nodes.at(i).biasDeltaSum += (_nodes.at(i).biasDelta * (1 / (double)_batchSize));
	}
}

void Nerual::OutputLayer::BatchDeltaSumClear(void)
{
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			_nodes.at(i).weightDeltaSum(j) = 0;

	for (size_t i = 0; i < m; i++)
		_nodes.at(i).biasDeltaSum = 0;
}

void Nerual::OutputLayer::LossSumUpdate(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).loss = lossFunction(_nodes.at(i).value, _nodes.at(i).expectation);
		_nodes.at(i).lossSum += _nodes.at(i).loss;
	}
}

void Nerual::OutputLayer::LossSumClear(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).lossSum = 0;
	}
}

// Get the node number of the layers.
size_t Nerual::Layer::GetNodeNum(void)
{
	return m;
}
