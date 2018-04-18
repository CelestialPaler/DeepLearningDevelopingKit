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

void Nerual::InputNode::Calculate(void)
{
	this->value = tempInput;
}

ostream & Nerual::operator<<(ostream & _outstream, InputNode & _node)
{
	_outstream << typeid(_node).name() << endl;
	_outstream << "	Value: " << _node.value << endl;
	return _outstream;
}

/**********************************************************************************************************/
// Class : HiddenNode
Nerual::HiddenNode::HiddenNode(size_t _n)
{
	this->value = 0.f;
	this->delta = 0.f;
	this->tempInput = 0.f;
	this->bias = 0.f;
	this->biasDelta = 0.f;
	this->weight.Init(_n);
	this->weightDelta.Init(_n);
}

void Nerual::HiddenNode::Calculate(void)
{
	// this->value = tempInput * 
}

ostream & Nerual::operator<<(ostream & _outstream, HiddenNode & _node)
{
	_outstream << typeid(_node).name() << endl;
	_outstream << "	Value: " << _node.value << endl;
	return _outstream;
}


