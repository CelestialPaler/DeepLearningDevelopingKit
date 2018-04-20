/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Module     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <vector>
#include "..\MathLib\MathLib.h"
#include "Layer.h"
#include "Node.h"
#include "..\DataSet\DataSet.h"

// Namespaces
using namespace std;
using namespace MathLib;
using namespace Data;

/***************************************************************************************************/
// Namespace : Nerual
/// Provide Node for nerual network algorithms.
namespace Nerual
{
	class Module
	{

	};

	struct BPNetInitor
	{
		vector<size_t> Size;
	};

	class BPNet : public Module
	{
	public:
		BPNet(void);
		BPNet(const BPNetInitor & _initor);
	public:
		void PushLayer(InputLayer * _newLayer);
		void PushLayer(HiddenLayer * _newLayer);
		void PushLayer(OutputLayer * _newLayer);

	public:
		void SetExpection(const Vector<ElemType> & _vec);
		ElemType GetLoss(void);
		Vector<ElemType> GetOutput(void);

	public:
		void SetTrainSet(NumaricSet * _trainset);
		void SetTestSet(NumaricSet * _testset);

	public:
		void Train();
		void Test();

	private:
		void ForwardPropagation(const Vector<ElemType> & _vec);
		void BackwardPropagation(const Vector<ElemType> & _vec);
		void Update(void);

	private:
		InputLayer * _inputlayer;
		vector<HiddenLayer *> _hiddenlayers;
		OutputLayer * _outputlayer;

		NumaricSet * _trainSet;
		NumaricSet * _testSet;
	};
}