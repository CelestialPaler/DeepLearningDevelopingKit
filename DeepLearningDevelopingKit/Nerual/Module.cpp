/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Module     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "Module.h"

void Nerual::BPNet::PushLayer(InputLayer * _newLayer)
{
	this->_inputlayer = _newLayer;
}

void Nerual::BPNet::PushLayer(HiddenLayer * _newLayer)
{
	this->_hiddenlayers.push_back(_newLayer);
}

void Nerual::BPNet::PushLayer(OutputLayer * _newLayer)
{
	this->_outputlayer = _newLayer;
}

void Nerual::BPNet::ForwardPropagation(const Vector<ElemType> & _vec)
{
	_inputlayer->SetInput(_vec);
	_inputlayer->ForwardPropagation();

	for (size_t i = 0; i < _hiddenlayers.size(); i++)
	{
		if (i==0)
		{
			_hiddenlayers.at(i)->SetInput(_inputlayer->GetOutput());
			_hiddenlayers.at(i)->ForwardPropagation();
		}
		else
		{
			_hiddenlayers.at(i)->SetInput(_hiddenlayers.at(i - 1)->GetOutput());
			_hiddenlayers.at(i)->ForwardPropagation();
		}
	}

	_outputlayer->SetInput(_hiddenlayers.at(_hiddenlayers.size() - 1)->GetOutput());
	_outputlayer->ForwardPropagation();
}

void Nerual::BPNet::BackwardPropagation(const Vector<ElemType>& _vec)
{
	_outputlayer->SetExpectation(_vec);

	cout << "Loss :" << _outputlayer->GetLoss() << endl;

	Vector<double> tempDelta(_hiddenlayers.at(_hiddenlayers.size() - 1)->GetNodeNum());
	tempDelta = _outputlayer->BackwardPropagation(_outputlayer->GetDelta());

	for (size_t i = _hiddenlayers.size() - 1; i > 0; i--)
	{
		Vector<double> tempDelta(_hiddenlayers.at(i)->GetNodeNum());
		tempDelta = _hiddenlayers.at(i)->BackwardPropagation(tempDelta);
	}
}

