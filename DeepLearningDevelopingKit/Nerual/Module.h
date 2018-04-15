/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include "Layer.h"
#include "Node.h"
#include <vector>

using namespace Nerual;
using namespace std;

class Module
{
public:
	void Push(LayerPointer * _newLayer)
	{
		layers.push_back(_newLayer);
	}
private:
	vector<LayerPointer *>  layers;
};


class BPNet : public Module
{
public:

private:

};