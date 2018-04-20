/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Module     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "Module.h"

Nerual::BPNet::BPNet(void)
{
}

Nerual::BPNet::BPNet(const BPNetInitor & _initor)
{
	_inputlayer = new InputLayer(_initor.InputNodeNum, _initor.InputNodeNum);

	for (size_t i = 0; i < _initor.HiddenLayerNum; i++)
	{
		if (i==0)
		{
			_hiddenlayers.push_back(new HiddenLayer(_initor.InputNodeNum, _initor.HiddenNodeNum));
		}
		else
		{
			_hiddenlayers.push_back(new HiddenLayer(_initor.HiddenNodeNum, _initor.HiddenNodeNum));
		}
	}

	_outputlayer = new OutputLayer(_initor.HiddenNodeNum, _initor.OutputNodeNum);
}

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

	Vector<double> tempDelta(_hiddenlayers.at(_hiddenlayers.size() - 1)->GetNodeNum());
	tempDelta = _outputlayer->BackwardPropagation(_outputlayer->GetDelta());

	for (size_t i = _hiddenlayers.size() - 1; i > 0; i--)
	{
		Vector<double> tempDelta(_hiddenlayers.at(i)->GetNodeNum());
		tempDelta = _hiddenlayers.at(i)->BackwardPropagation(tempDelta);
	}
}

void Nerual::BPNet::SetExpection(const Vector<ElemType>& _vec)
{
	_outputlayer->SetExpectation(_vec);
}

Nerual::ElemType Nerual::BPNet::GetLoss(void)
{
	return _outputlayer->GetLoss();
}

Vector<Nerual::ElemType> Nerual::BPNet::GetOutput(void)
{
	return _outputlayer->GetOutput();
}

void Nerual::BPNet::SetTrainSet(NumaricSet * _trainset)
{
	this->_trainSet = _trainset;
}

void Nerual::BPNet::SetTestSet(NumaricSet * _testset)
{
	this->_testSet = _testSet;
}

void Nerual::BPNet::Train()
{
	int count = 100;
	NumaricSet::Sample sample;
	do
	{
		if (count == 100)
		{
			sample = _trainSet->GetBatch();
			count = 0;
		}
		else
			count++;

		ForwardPropagation(sample.first);
		BackwardPropagation(sample.second);
		Update();
		cout << "Loss :" << _outputlayer->GetLoss() << endl;
		cout << sample.first(0) << sample.first(1) << endl;
	} while (GetLoss() > 0.00001);
}

void Nerual::BPNet::Test()
{
	for (size_t i = 0; i < 2; i++)
	{
		NumaricSet::Sample test = _testSet->GetBatch();
		ForwardPropagation(test.first);
		cout << this->GetOutput()(0);
	}
}

void Nerual::BPNet::Update(void)
{
	_inputlayer->Update();
	for (size_t i = 0; i < _hiddenlayers.size(); i++)
			_hiddenlayers.at(i)->Update();
	_outputlayer->Update();
}

