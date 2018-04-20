/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Module     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <vector>
#include "Layer.h"
#include "Node.h"
#include "..\MathLib\MathLib.h"

// Namespaces
using namespace std;

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

	public:
		void Train();

	private:
		void ForwardPropagation(const Vector<ElemType> & _vec);
		void BackwardPropagation(const Vector<ElemType> & _vec);
		void Update(void);



	private:
		InputLayer * _inputlayer;
		vector<HiddenLayer *> _hiddenlayers;
		OutputLayer * _outputlayer;
	};
}