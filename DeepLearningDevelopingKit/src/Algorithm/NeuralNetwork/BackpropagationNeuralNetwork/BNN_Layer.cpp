/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "BNN_Layer.h"

/***************************************************************************************************/
// Class : Layer 
/// Base class of the layer class.
// Get the node number of the layers.

void Neural::Layer::SetLearnRate(const double _learnRate)
{
	this->learnRate = _learnRate;
}

size_t Neural::Layer::GetNodeNum(void)
{
	return m;
}


/***************************************************************************************************/
// Class : InputLayer

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
Neural::InputLayer::InputLayer(const size_t _n, const size_t _m)
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
std::ostream & Neural::operator<<(std::ostream & _outstream, InputLayer & _layer)
{
	_outstream << typeid(_layer).name() << std::endl;
	_outstream << "	Node Num : " << _layer.m << std::endl;
	return _outstream;
}

// Set the input of the layer.
/// Which means set the nodes` tempInput.
void Neural::InputLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < n; i++)
	{
		_nodes.at(i).tempInput = _vec(i);
	}
}

// Set the activation function of the layer.
void Neural::InputLayer::SetActivationFunction(const ActivationFunction _function)
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

// Set the loss function of the layer.
void Neural::InputLayer::SetLossFunction(const LossFunction _function)
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
/// Which means get the value of all nodes in Vector.
Vector<Neural::ElemType> Neural::InputLayer::GetOutput(void)
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
void Neural::InputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).value = _nodes.at(i).tempInput;
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
Vector<Neural::ElemType> Neural::InputLayer::BackwardPropagation(const Vector<ElemType>& _vec)
{
	/// Calculate the partial derivative of loss to last layer value and return the expectation of last layer.
	return _vec;
}

// Update Function
/// Update the weight and bias of each node.
void Neural::InputLayer::Update(void)
{

}

// Sum up the delta of a batch.
void Neural::InputLayer::BatchDeltaSumUpdate(const size_t _batchSize)
{
}

// Clear the sumdelta of a batch.
void Neural::InputLayer::BatchDeltaSumClear(void)
{
}


/***************************************************************************************************/
// Class : HiddenLayer
/// Used for input data.

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
Neural::HiddenLayer::HiddenLayer(const size_t _n, const size_t _m)
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
void Neural::HiddenLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			_nodes.at(i).tempInput(j) = _vec(j);
		}
	}
}

// Set the expectation of the HiddenLayer.
void Neural::HiddenLayer::SetExpectation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).expectation = _vec(i);
	}
}

// Set the activation function of the layer.
void Neural::HiddenLayer::SetActivationFunction(const ActivationFunction _function)
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

// Set the loss function of the layer.
void Neural::HiddenLayer::SetLossFunction(const LossFunction _function)
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
/// Which means get the value of all nodes in Vector.
Vector<Neural::ElemType> Neural::HiddenLayer::GetOutput(void)
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
void Neural::HiddenLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).value = activationFunction(Vector<double>::DotProduct(_nodes.at(i).tempInput, _nodes.at(i).weight) + _nodes.at(i).bias);
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
Vector<Neural::ElemType> Neural::HiddenLayer::BackwardPropagation(const Vector<ElemType>& _vec)
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
void Neural::HiddenLayer::Update(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weight += _nodes.at(i).weightDeltaSum * learnRate;
		_nodes.at(i).bias += _nodes.at(i).biasDeltaSum * learnRate;
	}
}

// Sum up the delta of a batch.
void Neural::HiddenLayer::BatchDeltaSumUpdate(const size_t _batchSize)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weightDeltaSum += (_nodes.at(i).weightDelta * (1 / (double)_batchSize));
		_nodes.at(i).biasDeltaSum += (_nodes.at(i).biasDelta * (1 / (double)_batchSize));
	}
}

// Clear the sum of sum of delta.
void Neural::HiddenLayer::BatchDeltaSumClear(void)
{
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			_nodes.at(i).weightDeltaSum(j) = 0;

	for (size_t i = 0; i < m; i++)
		_nodes.at(i).biasDeltaSum = 0;
}


/***************************************************************************************************/
// Class : OutputLayer
/// Used for output data, quantify the loss of the output.

// Constructor
/// n is the input num of the layer.
/// m is the output num of the layer, which of course is the node num in this layer.
Neural::OutputLayer::OutputLayer(const size_t _n, const size_t _m)
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
void Neural::OutputLayer::SetInput(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).tempInput = _vec;
	}
}

// Set the expectation of the OutputLayer.
void Neural::OutputLayer::SetExpectation(const Vector<ElemType>& _vec)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).expectation = _vec(i);
	}
}

// Set the activation function of the layer.
void Neural::OutputLayer::SetActivationFunction(const ActivationFunction _function)
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

// Set the loss function of the layer.
void Neural::OutputLayer::SetLossFunction(const LossFunction _function)
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
Vector<Neural::ElemType> Neural::OutputLayer::GetOutput(void)
{
	Vector<ElemType> temp(m);
	for (size_t i = 0; i < m; i++)
	{
		temp(i) = _nodes.at(i).value;
	}
	return temp;
}

// Get the estimated loss between output and expectation.
Neural::ElemType Neural::OutputLayer::GetLoss(void)
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
Vector<Neural::ElemType> Neural::OutputLayer::GetDelta(void)
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
void Neural::OutputLayer::ForwardPropagation(void)
{
	for (size_t i = 0; i < m; i++)
	{
		/// θ(∑ X * W - B)
		_nodes.at(i).value = activationFunction(Vector<double>::DotProduct(_nodes.at(i).tempInput, _nodes.at(i).weight) + _nodes.at(i).bias);
	}
}

// BackwardPropagation Function
/// Calculate the gradient(delta) of each node.
Vector<Neural::ElemType> Neural::OutputLayer::BackwardPropagation(const Vector<ElemType> & _vec)
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
void Neural::OutputLayer::Update(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weight += _nodes.at(i).weightDeltaSum * learnRate;
		_nodes.at(i).bias += _nodes.at(i).biasDeltaSum * learnRate;
	}
}

// Sum up the delta of a batch.
void Neural::OutputLayer::BatchDeltaSumUpdate(const size_t _batchSize)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).weightDeltaSum += (_nodes.at(i).weightDelta * (1 / (double)_batchSize));
		_nodes.at(i).biasDeltaSum += (_nodes.at(i).biasDelta * (1 / (double)_batchSize));
	}
}

// Clear the sum of sum of delta.
void Neural::OutputLayer::BatchDeltaSumClear(void)
{
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < n; j++)
			_nodes.at(i).weightDeltaSum(j) = 0;

	for (size_t i = 0; i < m; i++)
		_nodes.at(i).biasDeltaSum = 0;
}

// Sum up the loss of a batch.
void Neural::OutputLayer::LossSumUpdate(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).loss = lossFunction(_nodes.at(i).value, _nodes.at(i).expectation);
		_nodes.at(i).lossSum += _nodes.at(i).loss;
	}
}

// Clear the sum of loss od a batch.
void Neural::OutputLayer::LossSumClear(void)
{
	for (size_t i = 0; i < m; i++)
	{
		_nodes.at(i).lossSum = 0;
	}
}
