/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Module     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <vector>
#include <iomanip>

#include "..\..\MathLib\MathLib.h"
#include "..\..\DataManager\DataSet.h"
#include "..\..\Util\Timer\Timer.h"

#include "Layer.h"
#include "Node.h"

// Namespaces
using namespace MathLib;
using namespace Data;
using namespace Util;

/***************************************************************************************************/
// Namespace : Nerual
/// Provide Node for nerual network algorithms.
namespace Nerual
{
	class Module
	{

	};

	// BPNet Initor
	/// Used for initialization of a BPNet.
	struct BPNetInitor
	{
		size_t InputNodeNum;
		size_t HiddenLayerNum;
		size_t HiddenNodeNum;
		size_t OutputNodeNum;

		ActivationFunction InputLayerActivationFunction;
		ActivationFunction HiddenLayerActivationFunction;
		ActivationFunction OutputLayerActivationFunction;

		LossFunction LossFunction;
	};

	/***************************************************************************************************/
	// Class : BPNet
	/// BackPropagation Network.
	/// It will be a built-in Module.
	class BPNet : public Module
	{
	public: // Constructors

		// Default constructor
		BPNet(void);
		// Constructor (Using Initor)
		BPNet(const BPNetInitor & _initor);

	public:
		void SetExpection(const Vector<ElemType> & _vec);
		ElemType GetLoss(void);
		Vector<ElemType> GetOutput(void);

	public:
		void SetTrainSet(NumaricSet * _trainset);
		void SetTestSet(NumaricSet * _testset);

	public: // Train and Test
		
		// Training Function
		/// Train utill one of the limit reached.
		void Train();
		// Testing Funtion
		void Test();

	private:

		// ForwardPropagation Function
		/// Calculate the value of each node.
		void ForwardPropagation(const Vector<ElemType> & _vec);
		// BackwardPropagation Function
		/// Calculate the gradient(delta) of each node.
		void BackwardPropagation(const Vector<ElemType> & _vec);
		// Update Function
		/// Update the weight and bias of each node.
		void Update(void);
		// Sum up the delta of a batch.
		void BatchDeltaSumUpdate(const size_t _batchSize);
		// Clear the sum of sum of delta.
		void BatchDeltaSumClear(void);

	private: // AddingLayers

		// Adding a new InputLayer to the Layers.
		/// Since there should be only one inputlayer, it will always be the newest one.
		void PushLayer(InputLayer * _newLayer);
		// Adding a new HiddenLayer to the Layers.
		void PushLayer(HiddenLayer * _newLayer);
		// Adding a new OutputLayer to the Layers.
		/// Since there should be only one outputlayer, it will always be the newest one.
		void PushLayer(OutputLayer * _newLayer);

	private:

		InputLayer * _inputlayer;
		std::vector<HiddenLayer *> _hiddenlayers;
		OutputLayer * _outputlayer;

		NumaricSet * _trainSet;
		NumaricSet * _testSet;

	private:

		double learnRate = 0.5;
		double momentumRate = 0.2;
	};
}