/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Node 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "Node.h"

/**********************************************************************************************************/
// Class : InputNode
Nerual::InputNode::InputNode(void)
{
	this->value = 0.f;
}

ostream & Nerual::operator<<(ostream & _outstream, InputNode & _node)
{
	_outstream << typeid(_node).name() << endl;
	_outstream << "	Value: " << _node.value << endl;
	return _outstream;
}

/**********************************************************************************************************/
// Class : HiddenNode
Nerual::HiddenNode::HiddenNode(const size_t _n)
{
	this->value = 0.f;
	this->valueDelta = 0.f;
	this->bias = 0.f;
	this->biasDelta = 0.f;
	this->biasDeltaSum = 0.f;
	this->tempInput.Init(_n, VectorType::Zero);
	this->weight.Init(_n, VectorType::Random);
	this->weightDelta.Init(_n, VectorType::Zero);
	this->weightDeltaSum.Init(_n, VectorType::Zero);
}

ostream & Nerual::operator<<(ostream & _outstream, HiddenNode & _node)
{
	_outstream << typeid(_node).name() << endl;
	_outstream << "	value: " << _node.value << endl;
	_outstream << "	delta: " << _node.valueDelta << endl;
	_outstream << "	bias: " << _node.bias << endl;
	_outstream << "	biasDelta: " << _node.biasDelta << endl;
	_outstream << "	tempInput: " << _node.tempInput;
	_outstream << "	weight: " << _node.weight;
	_outstream << "	weightDelta: " << _node.weightDelta;
	return _outstream;
}

/**********************************************************************************************************/
// Class : OutputNode
Nerual::OutputNode::OutputNode(const size_t _n)
{
	this->value = 0.f;
	this->valueDelta = 0.f;
	this->loss = 0.f;
	this->bias = 0.f;
	this->biasDelta = 0.f;
	this->biasDeltaSum = 0.f;
	this->expectation = 0.f;
	this->tempInput.Init(_n, VectorType::Zero);
	this->weight.Init(_n, VectorType::Random);
	this->weightDelta.Init(_n, VectorType::Zero);
	this->weightDeltaSum.Init(_n, VectorType::Zero);
}

ostream & Nerual::operator<<(ostream & _outstream, OutputNode & _node)
{
	_outstream << typeid(_node).name() << endl;
	_outstream << "	value: " << _node.value << endl;
	_outstream << "	valueDelta: " << _node.valueDelta << endl;
	_outstream << "	loss: " << _node.loss << endl;
	_outstream << "	bias: " << _node.bias << endl;
	_outstream << "	biasDelta: " << _node.biasDelta << endl;
	_outstream << "	expectation: " << _node.expectation << endl;
	_outstream << "	tempInput: " << _node.tempInput;
	_outstream << "	weight: " << _node.weight;
	_outstream << "	weightDelta: " << _node.weightDelta;
	return _outstream;
}