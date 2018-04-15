/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include "Layer.h"
#include "Node.h"
#include "..\Util\Port.h"
#include "..\MathLib\MathLib.h"
#include <vector>

using namespace Nerual;
using namespace std;

class Module
{
public:
	void PushLayer(LayerPointer * _newLayer)
	{
		layers.push_back(_newLayer);
	}
	void PushInputPort(PortPointer * _newLayer)
	{
		inputPorts.push_back(_newLayer);
	}
	void PushOutputPort(PortPointer * _newLayer)
	{
		outputPorts.push_back(_newLayer);
	}
	void Run(void)
	{

	}
private:
	vector<LayerPointer *>  layers;
	vector<PortPointer *> inputPorts;
	vector<PortPointer *> outputPorts;
};


class BPNet : public Module
{
public:

private:

};