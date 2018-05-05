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
	_inputlayer->SetActivationFunction(_initor.InputLayerActivationFunction);
	_inputlayer->SetLossFunction(_initor.LossFunction);

	for (size_t i = 0; i < _initor.HiddenLayerNum; i++)
	{
		if (i==0)
		{
			HiddenLayer * tempLayer = new HiddenLayer(_initor.InputNodeNum, _initor.HiddenNodeNum);
			tempLayer->SetActivationFunction(_initor.HiddenLayerActivationFunction);
			tempLayer->SetLossFunction(_initor.LossFunction);
			_hiddenlayers.push_back(tempLayer);
		}
		else
		{
			HiddenLayer * tempLayer = new HiddenLayer(_initor.HiddenNodeNum, _initor.HiddenNodeNum);
			tempLayer->SetActivationFunction(_initor.HiddenLayerActivationFunction);
			tempLayer->SetLossFunction(_initor.LossFunction);
			_hiddenlayers.push_back(tempLayer);
		}
	}

	_outputlayer = new OutputLayer(_initor.HiddenNodeNum, _initor.OutputNodeNum);
	_outputlayer->SetActivationFunction(_initor.OutputLayerActivationFunction);
	_outputlayer->SetLossFunction(_initor.LossFunction);
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
	Vector<double> tempDelta1(_hiddenlayers.at(_hiddenlayers.size() - 1)->GetNodeNum());
	tempDelta1 = _outputlayer->BackwardPropagation(_vec);

	Vector<double> tempDelta2(_hiddenlayers.at(_hiddenlayers.size() - 1)->GetNodeNum());
	tempDelta2 = _hiddenlayers.at(_hiddenlayers.size() - 1)->BackwardPropagation(tempDelta1);
	for (size_t i = _hiddenlayers.size() - 1; i > 0; i--)
	{
		tempDelta2 = _hiddenlayers.at(i - 1)->BackwardPropagation(tempDelta2);
	}
}

void Nerual::BPNet::Update(void)
{
	_inputlayer->Update();
	for (size_t i = 0; i < _hiddenlayers.size(); i++)
		_hiddenlayers.at(i)->Update();
	_outputlayer->Update();
}

void Nerual::BPNet::BatchDeltaSumUpdate(const size_t _batchSize)
{
	_inputlayer->BatchDeltaSumUpdate(_batchSize);
	for (size_t i = 0; i < _hiddenlayers.size(); i++)
		_hiddenlayers.at(i)->BatchDeltaSumUpdate(_batchSize);
	_outputlayer->BatchDeltaSumUpdate(_batchSize);
}

void Nerual::BPNet::BatchDeltaSumClear(void)
{
	_inputlayer->BatchDeltaSumClear();
	for (size_t i = 0; i < _hiddenlayers.size(); i++)
		_hiddenlayers.at(i)->BatchDeltaSumClear();
	_outputlayer->BatchDeltaSumClear();
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

void Nerual::BPNet::SetTrainSet(NumericSet * _trainset)
{
	this->_trainSet = _trainset;
}

void Nerual::BPNet::SetTestSet(NumericSet * _testset)
{
	this->_testSet = _testset;
}



void Nerual::BPNet::Train()
{
	Timer<std::chrono::seconds> trainTimer;
	int iterCount = 0;
	double loss = 0;
	NumericSet::Sample sample;
	do
	{
		for (size_t i = 0; i < 4; i++)
		{
			sample = _trainSet->GetBatch();
			ForwardPropagation(sample.first);
			BackwardPropagation(sample.second);
			BatchDeltaSumUpdate(4);
			_outputlayer->LossSumUpdate();
		}
		iterCount++;

		Update();
		BatchDeltaSumClear();
		loss = _outputlayer->GetLoss();
		_outputlayer->LossSumClear();
		std::cout << "Iiteration :" << std::setw(4) << std::setfill('0') << iterCount << " | "
			<< "Time :" << std::fixed << std::setprecision(3) << trainTimer.GetTime() << " sec"<< " | "
			<< "Loss :" << std::fixed << std::setprecision(10) << loss << std::endl;
	} while (loss > 0.001);
}

void Nerual::BPNet::Test()
{
	NumericSet::Sample test;
	double avrError = 0;
	std::cout << "Testing: " << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		test = _testSet->GetSample(i);
		ForwardPropagation(test.first);
		std::cout << "Input :" << std::fixed << std::setprecision(3) << test.first(0) << "  " << test.first(1) << " | "
			<< "Expectation :" << std::fixed << std::setprecision(3) << test.second(0) << " | "
			<< "Output :" << std::fixed << std::setprecision(3) << _outputlayer->GetOutput()(0) << " | "
			<< "Error :" << std::fixed << std::setprecision(3) << _outputlayer->GetOutput()(0) - test.second(0) << std::endl;
		avrError += _outputlayer->GetOutput()(0) - test.second(0);
		avrError /= 5;
	}
	std::cout << std::endl << "Testing: " << std::endl;
	std::cout << std::fixed << std::setprecision(10) << "Average Error :" << avrError << std::endl
		<< std::fixed << std::setprecision(3) << "Error Rate :" << abs(avrError * 100) << "%" << std::endl;
}



