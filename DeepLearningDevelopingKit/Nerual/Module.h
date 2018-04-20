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

	class BPNet : public Module
	{
	public:
		void PushLayer(InputLayer * _newLayer);
		void PushLayer(HiddenLayer * _newLayer);
		void PushLayer(OutputLayer * _newLayer);

		void ForwardPropagation(const Vector<ElemType> & _vec);
		void BackwardPropagation(const Vector<ElemType> & _vec);
		void SetExpection(const Vector<ElemType> & _vec);
		ElemType GetLoss(void);
		void Update(void);

	private:
		InputLayer * _inputlayer;
		vector<HiddenLayer *> _hiddenlayers;
		OutputLayer * _outputlayer;
	};
}